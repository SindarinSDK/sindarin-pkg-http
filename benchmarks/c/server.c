/*
 * HTTP JSON REST API Server - C Implementation
 * Uses raw sockets with pthreads for concurrent request handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <signal.h>

#define PORT 8081
#define BUFFER_SIZE 4096
#define MAX_ITEMS 10000

typedef struct {
    int id;
    char data[256];
    int active;
} Item;

static Item items[MAX_ITEMS];
static int next_id = 1;
static int item_count = 0;
static pthread_mutex_t items_mutex = PTHREAD_MUTEX_INITIALIZER;

// Find item by ID, returns index or -1
static int find_item(int id) {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (items[i].active && items[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Find free slot
static int find_free_slot() {
    for (int i = 0; i < MAX_ITEMS; i++) {
        if (!items[i].active) {
            return i;
        }
    }
    return -1;
}

// Send HTTP response
static void send_response(int client_fd, int status, const char* status_text,
                          const char* content_type, const char* body) {
    char header[512];
    int body_len = body ? strlen(body) : 0;

    int header_len = snprintf(header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n",
        status, status_text, content_type, body_len);

    send(client_fd, header, header_len, 0);
    if (body && body_len > 0) {
        send(client_fd, body, body_len, 0);
    }
}

// GET /items - list all items (simplified - just return count for perf)
static void handle_list_items(int client_fd) {
    char body[65536];
    int offset = 0;

    pthread_mutex_lock(&items_mutex);

    offset += snprintf(body + offset, sizeof(body) - offset, "[");
    int first = 1;
    int count = 0;
    for (int i = 0; i < MAX_ITEMS && count < 100; i++) {  // Limit to 100 items in response
        if (items[i].active) {
            if (!first) offset += snprintf(body + offset, sizeof(body) - offset, ",");
            offset += snprintf(body + offset, sizeof(body) - offset,
                "{\"id\":%d}", items[i].id);
            first = 0;
            count++;
        }
    }
    offset += snprintf(body + offset, sizeof(body) - offset, "]");

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", body);
}

// POST /items - create item
static void handle_create_item(int client_fd, const char* json_body) {
    char body[512];

    pthread_mutex_lock(&items_mutex);

    int slot = find_free_slot();
    if (slot < 0) {
        pthread_mutex_unlock(&items_mutex);
        send_response(client_fd, 500, "Internal Server Error", "application/json",
            "{\"error\":\"Storage full\"}");
        return;
    }

    items[slot].id = next_id++;
    items[slot].active = 1;
    items[slot].data[0] = '\0';
    item_count++;

    int id = items[slot].id;
    pthread_mutex_unlock(&items_mutex);

    snprintf(body, sizeof(body), "{\"id\":%d}", id);
    send_response(client_fd, 201, "Created", "application/json", body);
}

// GET /items/{id}
static void handle_get_item(int client_fd, int id) {
    char body[512];

    pthread_mutex_lock(&items_mutex);

    int idx = find_item(id);
    if (idx < 0) {
        pthread_mutex_unlock(&items_mutex);
        send_response(client_fd, 404, "Not Found", "application/json",
            "{\"error\":\"Item not found\"}");
        return;
    }

    snprintf(body, sizeof(body), "{\"id\":%d}", items[idx].id);

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", body);
}

// PUT /items/{id}
static void handle_update_item(int client_fd, int id, const char* json_body) {
    char body[512];

    pthread_mutex_lock(&items_mutex);

    int idx = find_item(id);
    if (idx < 0) {
        pthread_mutex_unlock(&items_mutex);
        send_response(client_fd, 404, "Not Found", "application/json",
            "{\"error\":\"Item not found\"}");
        return;
    }

    snprintf(body, sizeof(body), "{\"id\":%d}", items[idx].id);

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", body);
}

// DELETE /items/{id}
static void handle_delete_item(int client_fd, int id) {
    pthread_mutex_lock(&items_mutex);

    int idx = find_item(id);
    if (idx < 0) {
        pthread_mutex_unlock(&items_mutex);
        send_response(client_fd, 404, "Not Found", "application/json",
            "{\"error\":\"Item not found\"}");
        return;
    }

    items[idx].active = 0;
    item_count--;

    pthread_mutex_unlock(&items_mutex);

    send_response(client_fd, 200, "OK", "application/json", "{\"deleted\":true}");
}

// Parse request and route
static void handle_request(int client_fd) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes <= 0) {
        close(client_fd);
        return;
    }

    buffer[bytes] = '\0';

    // Parse method and path
    char method[16] = {0}, path[256] = {0};
    sscanf(buffer, "%15s %255s", method, path);

    // Find body (after \r\n\r\n)
    char* body = strstr(buffer, "\r\n\r\n");
    if (body) body += 4;

    // Route request
    if (strcmp(path, "/items") == 0) {
        if (strcmp(method, "GET") == 0) {
            handle_list_items(client_fd);
        } else if (strcmp(method, "POST") == 0) {
            handle_create_item(client_fd, body ? body : "{}");
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
            handle_update_item(client_fd, id, body ? body : "{}");
        } else if (strcmp(method, "DELETE") == 0) {
            handle_delete_item(client_fd, id);
        } else {
            send_response(client_fd, 405, "Method Not Allowed", "text/plain",
                "Method not allowed");
        }
    } else {
        send_response(client_fd, 404, "Not Found", "text/plain", "Not found");
    }

    close(client_fd);
}

// Thread worker
static void* client_thread(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);
    handle_request(client_fd);
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;

    // Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // Initialize items
    memset(items, 0, sizeof(items));

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        exit(1);
    }

    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // Listen
    if (listen(server_fd, 1024) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("C Server listening on port %d\n", PORT);
    fflush(stdout);

    // Accept loop
    while (1) {
        int* client_fd = malloc(sizeof(int));
        if (!client_fd) continue;

        *client_fd = accept(server_fd, NULL, NULL);

        if (*client_fd < 0) {
            free(client_fd);
            continue;
        }

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
