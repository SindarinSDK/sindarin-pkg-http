/*
 * HTTP JSON REST API Server - C Implementation
 * Uses raw sockets with pthreads for concurrent request handling
 * Supports HTTP keep-alive connections
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <signal.h>
#include <strings.h>

#define PORT 8081
#define BUFFER_SIZE 8192
#define INITIAL_CAPACITY 1024
#define MAX_ITEMS 1000
#define MAX_NAME_LEN 64

typedef struct {
    int id;
    int active;
    char name[MAX_NAME_LEN];
    int value;
} Item;

static Item *items = NULL;
static int items_capacity = 0;
static int items_count = 0;
static int next_id = 1;
static pthread_mutex_t items_mutex = PTHREAD_MUTEX_INITIALIZER;

// Find item by ID, returns index or -1
static int find_item(int id) {
    for (int i = 0; i < items_count; i++) {
        if (items[i].active && items[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Find free slot (reuse deleted entries)
static int find_free_slot(void) {
    for (int i = 0; i < items_count; i++) {
        if (!items[i].active) {
            return i;
        }
    }
    return -1;
}

// Send HTTP response (keep-alive)
static void send_response(int client_fd, int status, const char* status_text,
                          const char* content_type, const char* body) {
    char header[512];
    int body_len = body ? (int)strlen(body) : 0;

    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "\r\n",
        status, status_text, content_type, body_len);

    if (body && body_len > 0) {
        send(client_fd, header, header_len, MSG_MORE);
        send(client_fd, body, body_len, 0);
    } else {
        send(client_fd, header, header_len, 0);
    }
}

// GET /items - list all items
static void handle_list_items(int client_fd) {
    // 1000 items * ~80 bytes each = ~80KB max
    char *body = malloc(131072);
    if (!body) {
        send_response(client_fd, 500, "Internal Server Error", "application/json",
            "{\"error\":\"Out of memory\"}");
        return;
    }
    int offset = 0;
    int capacity = 131072;

    pthread_mutex_lock(&items_mutex);

    offset += snprintf(body + offset, capacity - offset, "[");
    int first = 1;
    for (int i = 0; i < items_count; i++) {
        if (items[i].active) {
            if (!first) offset += snprintf(body + offset, capacity - offset, ",");
            offset += snprintf(body + offset, capacity - offset,
                "{\"id\":%d,\"name\":\"%s\",\"value\":%d}",
                items[i].id, items[i].name, items[i].value);
            first = 0;
        }
    }
    offset += snprintf(body + offset, capacity - offset, "]");

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", body);
    free(body);
}

// POST /items - upsert item with cycling ID
static void handle_create_item(int client_fd) {
    char body[512];

    pthread_mutex_lock(&items_mutex);

    int id = (next_id % MAX_ITEMS) + 1;
    next_id++;

    // Find existing item with this ID and overwrite, or find a free slot
    int idx = find_item(id);
    if (idx >= 0) {
        // Overwrite existing
        snprintf(items[idx].name, MAX_NAME_LEN, "Item %d", id);
        items[idx].value = id;
    } else {
        // Find a free slot or grow
        int slot = find_free_slot();
        if (slot < 0) {
            if (items_count >= items_capacity) {
                int new_cap = items_capacity ? items_capacity * 2 : INITIAL_CAPACITY;
                Item *new_items = realloc(items, new_cap * sizeof(Item));
                if (!new_items) {
                    pthread_mutex_unlock(&items_mutex);
                    send_response(client_fd, 500, "Internal Server Error", "application/json",
                        "{\"error\":\"Out of memory\"}");
                    return;
                }
                items = new_items;
                items_capacity = new_cap;
            }
            slot = items_count++;
        }
        items[slot].id = id;
        items[slot].active = 1;
        snprintf(items[slot].name, MAX_NAME_LEN, "Item %d", id);
        items[slot].value = id;
    }

    pthread_mutex_unlock(&items_mutex);

    snprintf(body, sizeof(body), "{\"id\":%d,\"name\":\"Item %d\",\"value\":%d}", id, id, id);
    send_response(client_fd, 200, "OK", "application/json", body);
}

// GET /items/{id} - returns empty item if not found
static void handle_get_item(int client_fd, int id) {
    char body[512];

    pthread_mutex_lock(&items_mutex);

    int idx = find_item(id);
    if (idx < 0) {
        pthread_mutex_unlock(&items_mutex);
        snprintf(body, sizeof(body), "{\"id\":%d,\"name\":\"\",\"value\":0}", id);
        send_response(client_fd, 200, "OK", "application/json", body);
        return;
    }

    snprintf(body, sizeof(body), "{\"id\":%d,\"name\":\"%s\",\"value\":%d}",
        items[idx].id, items[idx].name, items[idx].value);

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", body);
}

// PUT /items/{id} - update or create
static void handle_update_item(int client_fd, int id) {
    char body[512];

    pthread_mutex_lock(&items_mutex);

    int idx = find_item(id);
    if (idx >= 0) {
        // Update existing
        snprintf(items[idx].name, MAX_NAME_LEN, "Item %d", id);
        items[idx].value = id;
    } else {
        // Create new
        int slot = find_free_slot();
        if (slot < 0) {
            if (items_count >= items_capacity) {
                int new_cap = items_capacity ? items_capacity * 2 : INITIAL_CAPACITY;
                Item *new_items = realloc(items, new_cap * sizeof(Item));
                if (!new_items) {
                    pthread_mutex_unlock(&items_mutex);
                    send_response(client_fd, 500, "Internal Server Error", "application/json",
                        "{\"error\":\"Out of memory\"}");
                    return;
                }
                items = new_items;
                items_capacity = new_cap;
            }
            slot = items_count++;
        }
        items[slot].id = id;
        items[slot].active = 1;
        snprintf(items[slot].name, MAX_NAME_LEN, "Item %d", id);
        items[slot].value = id;
    }

    pthread_mutex_unlock(&items_mutex);

    snprintf(body, sizeof(body), "{\"id\":%d,\"name\":\"Item %d\",\"value\":%d}", id, id, id);
    send_response(client_fd, 200, "OK", "application/json", body);
}

// DELETE /items/{id} - always returns 200
static void handle_delete_item(int client_fd, int id) {
    pthread_mutex_lock(&items_mutex);

    int idx = find_item(id);
    if (idx >= 0) {
        items[idx].active = 0;
    }

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", "{\"deleted\":true}");
}

// Route a parsed request
static void route_request(int client_fd, const char *method, const char *path) {
    if (strcmp(path, "/items") == 0) {
        if (strcmp(method, "GET") == 0) {
            handle_list_items(client_fd);
        } else if (strcmp(method, "POST") == 0) {
            handle_create_item(client_fd);
        } else {
            send_response(client_fd, 405, "Method Not Allowed", "text/plain",
                "Method not allowed");
        }
    } else if (strncmp(path, "/items/", 7) == 0) {
        int id = atoi(path + 7);
        if (id <= 0) {
            send_response(client_fd, 400, "Bad Request", "application/json",
                "{\"error\":\"Invalid ID\"}");
        } else if (strcmp(method, "GET") == 0) {
            handle_get_item(client_fd, id);
        } else if (strcmp(method, "PUT") == 0) {
            handle_update_item(client_fd, id);
        } else if (strcmp(method, "DELETE") == 0) {
            handle_delete_item(client_fd, id);
        } else {
            send_response(client_fd, 405, "Method Not Allowed", "text/plain",
                "Method not allowed");
        }
    } else {
        send_response(client_fd, 404, "Not Found", "text/plain", "Not found");
    }
}

// Thread worker - handles keep-alive connections
static void* client_thread(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);

    char buf[BUFFER_SIZE];
    int buf_len = 0;

    while (1) {
        ssize_t n = recv(client_fd, buf + buf_len, BUFFER_SIZE - buf_len - 1, 0);
        if (n <= 0) break;
        buf_len += n;
        buf[buf_len] = '\0';

        // Process all complete requests in the buffer
        while (1) {
            char *headers_end = strstr(buf, "\r\n\r\n");
            if (!headers_end) break;

            int headers_len = (int)(headers_end - buf) + 4;

            // Parse Content-Length for body
            int content_length = 0;
            for (char *p = buf; p < headers_end; p++) {
                if ((*p == 'C' || *p == 'c') &&
                    strncasecmp(p, "Content-Length:", 15) == 0) {
                    content_length = atoi(p + 15);
                    break;
                }
            }

            int total_len = headers_len + content_length;
            if (buf_len < total_len) break;

            // Parse method and path
            char method[16] = {0}, path[256] = {0};
            sscanf(buf, "%15s %255s", method, path);

            route_request(client_fd, method, path);

            // Shift remaining data in buffer
            int remaining = buf_len - total_len;
            if (remaining > 0) {
                memmove(buf, buf + total_len, remaining);
            }
            buf_len = remaining;
            buf[buf_len] = '\0';
        }

        // Buffer full with no complete request - bad connection
        if (buf_len >= BUFFER_SIZE - 1) break;
    }

    close(client_fd);
    return NULL;
}

int main(void) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    signal(SIGPIPE, SIG_IGN);

    // Pre-populate 1000 items
    items = malloc(INITIAL_CAPACITY * sizeof(Item));
    if (!items) {
        perror("malloc failed");
        exit(1);
    }
    items_capacity = INITIAL_CAPACITY;
    for (int i = 0; i < MAX_ITEMS; i++) {
        int id = i + 1;
        items[i].id = id;
        items[i].active = 1;
        snprintf(items[i].name, MAX_NAME_LEN, "Item %d", id);
        items[i].value = id;
    }
    items_count = MAX_ITEMS;
    next_id = 1;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    if (listen(server_fd, 1024) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("C Server listening on port %d\n", PORT);
    fflush(stdout);

    while (1) {
        int* client_fd = malloc(sizeof(int));
        if (!client_fd) continue;

        *client_fd = accept(server_fd, NULL, NULL);

        if (*client_fd < 0) {
            free(client_fd);
            continue;
        }

        // Set TCP_NODELAY on client socket for lower latency
        setsockopt(*client_fd, IPPROTO_TCP, TCP_NODELAY, &opt, sizeof(opt));

        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (pthread_create(&tid, &attr, client_thread, client_fd) != 0) {
            close(*client_fd);
            free(client_fd);
        }
        pthread_attr_destroy(&attr);
    }

    return 0;
}
