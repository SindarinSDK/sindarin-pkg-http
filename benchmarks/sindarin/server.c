#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include "sn_minimal.h"
#include <json-c/json.h>

/* Struct: TcpStream (native) */
typedef struct {
    long long socket_fd;
    unsigned char * remote_addr;
} __sn__TcpStream;

static inline __sn__TcpStream *__sn__TcpStream_alloc(void) {
    return calloc(1, sizeof(__sn__TcpStream));
}

static inline void __sn__TcpStream_release(__sn__TcpStream **p) {
    if (*p) {
        free((*p)->remote_addr);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_TcpStream __attribute__((cleanup(__sn__TcpStream_release)))
#define sn_auto_ref_TcpStream __attribute__((cleanup(__sn__TcpStream_release)))


/* Struct: TcpListener (native) */
typedef struct {
    long long socket_fd;
    long long bound_port;
} __sn__TcpListener;

static inline __sn__TcpListener *__sn__TcpListener_alloc(void) {
    return calloc(1, sizeof(__sn__TcpListener));
}

static inline void __sn__TcpListener_release(__sn__TcpListener **p) {
    if (*p) {
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_TcpListener __attribute__((cleanup(__sn__TcpListener_release)))
#define sn_auto_ref_TcpListener __attribute__((cleanup(__sn__TcpListener_release)))


/* Struct: Json (native) */
typedef struct {
    long long obj;
    long long handle;
    int32_t is_root;
} __sn__Json;

static inline __sn__Json *__sn__Json_alloc(void) {
    return calloc(1, sizeof(__sn__Json));
}

static inline void __sn__Json_release(__sn__Json **p) {
    if (*p) {
        sn_json_dispose(*p);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_Json __attribute__((cleanup(__sn__Json_release)))
#define sn_auto_ref_Json __attribute__((cleanup(__sn__Json_release)))


/* Struct: Header (as val) */
typedef struct {
    char * __sn__name;
    char * __sn__value;
} __sn__Header;
/* Value operations */
static inline __sn__Header __sn__Header_copy(const __sn__Header *src) {
    __sn__Header dst;
    dst.__sn__name = src->__sn__name ? strdup(src->__sn__name) : NULL;
    dst.__sn__value = src->__sn__value ? strdup(src->__sn__value) : NULL;
    return dst;
}

static inline void __sn__Header_cleanup(__sn__Header *p) {
    free(p->__sn__name);
    free(p->__sn__value);

}

#define sn_auto_Header __attribute__((cleanup(__sn__Header_cleanup)))

static inline void __sn__Header_cleanup_elem(void *p) { __sn__Header_cleanup((__sn__Header *)p); }
static inline void __sn__Header_copy_into(const void *src, void *dst) { *(__sn__Header *)dst = __sn__Header_copy((const __sn__Header *)src); }

/* Ref/pointer operations */
static inline __sn__Header *__sn__Header_alloc(void) {
    return calloc(1, sizeof(__sn__Header));
}

static inline void __sn__Header_release(__sn__Header **p) {
    if (*p) {
        free((*p)->__sn__name);
        free((*p)->__sn__value);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_Header __attribute__((cleanup(__sn__Header_release)))

static inline void __sn__Header_release_elem(void *p) { __sn__Header_release((__sn__Header **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__Header_to_string(const __sn__Header *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "Header { ");
    off += snprintf(buf + off, sizeof(buf) - off, "name: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__name ? p->__sn__name : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "value: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__value ? p->__sn__value : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: HttpRequest (as val) */
typedef struct {
    char * __sn__method;
    char * __sn__path;
    char * __sn__query;
    char * __sn__version;
    SnArray * __sn__headers;
    char * __sn__body;
    char * __sn__raw;
} __sn__HttpRequest;
/* Value operations */
static inline __sn__HttpRequest __sn__HttpRequest_copy(const __sn__HttpRequest *src) {
    __sn__HttpRequest dst;
    dst.__sn__method = src->__sn__method ? strdup(src->__sn__method) : NULL;
    dst.__sn__path = src->__sn__path ? strdup(src->__sn__path) : NULL;
    dst.__sn__query = src->__sn__query ? strdup(src->__sn__query) : NULL;
    dst.__sn__version = src->__sn__version ? strdup(src->__sn__version) : NULL;
    dst.__sn__headers = sn_array_copy(src->__sn__headers);
    dst.__sn__body = src->__sn__body ? strdup(src->__sn__body) : NULL;
    dst.__sn__raw = src->__sn__raw ? strdup(src->__sn__raw) : NULL;
    return dst;
}

static inline void __sn__HttpRequest_cleanup(__sn__HttpRequest *p) {
    free(p->__sn__method);
    free(p->__sn__path);
    free(p->__sn__query);
    free(p->__sn__version);
    sn_cleanup_array(&p->__sn__headers);
    free(p->__sn__body);
    free(p->__sn__raw);

}

#define sn_auto_HttpRequest __attribute__((cleanup(__sn__HttpRequest_cleanup)))

static inline void __sn__HttpRequest_cleanup_elem(void *p) { __sn__HttpRequest_cleanup((__sn__HttpRequest *)p); }
static inline void __sn__HttpRequest_copy_into(const void *src, void *dst) { *(__sn__HttpRequest *)dst = __sn__HttpRequest_copy((const __sn__HttpRequest *)src); }

/* Ref/pointer operations */
static inline __sn__HttpRequest *__sn__HttpRequest_alloc(void) {
    return calloc(1, sizeof(__sn__HttpRequest));
}

static inline void __sn__HttpRequest_release(__sn__HttpRequest **p) {
    if (*p) {
        free((*p)->__sn__method);
        free((*p)->__sn__path);
        free((*p)->__sn__query);
        free((*p)->__sn__version);
        sn_cleanup_array(&(*p)->__sn__headers);
        free((*p)->__sn__body);
        free((*p)->__sn__raw);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_HttpRequest __attribute__((cleanup(__sn__HttpRequest_release)))

static inline void __sn__HttpRequest_release_elem(void *p) { __sn__HttpRequest_release((__sn__HttpRequest **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__HttpRequest_to_string(const __sn__HttpRequest *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "HttpRequest { ");
    off += snprintf(buf + off, sizeof(buf) - off, "method: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__method ? p->__sn__method : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "path: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__path ? p->__sn__path : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "query: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__query ? p->__sn__query : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "version: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__version ? p->__sn__version : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "headers: ");
    { char *__fs__ = sn_array_to_string(p->__sn__headers); off += snprintf(buf + off, sizeof(buf) - off, "%s", __fs__); free(__fs__); }
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "body: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__body ? p->__sn__body : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "raw: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__raw ? p->__sn__raw : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: HttpStatus (as val) */
typedef struct {
} __sn__HttpStatus;
/* Value operations */
static inline __sn__HttpStatus __sn__HttpStatus_copy(const __sn__HttpStatus *src) {
    __sn__HttpStatus dst;
    return dst;
}

static inline void __sn__HttpStatus_cleanup(__sn__HttpStatus *p) {

}

#define sn_auto_HttpStatus __attribute__((cleanup(__sn__HttpStatus_cleanup)))

static inline void __sn__HttpStatus_cleanup_elem(void *p) { __sn__HttpStatus_cleanup((__sn__HttpStatus *)p); }
static inline void __sn__HttpStatus_copy_into(const void *src, void *dst) { *(__sn__HttpStatus *)dst = __sn__HttpStatus_copy((const __sn__HttpStatus *)src); }

/* Ref/pointer operations */
static inline __sn__HttpStatus *__sn__HttpStatus_alloc(void) {
    return calloc(1, sizeof(__sn__HttpStatus));
}

static inline void __sn__HttpStatus_release(__sn__HttpStatus **p) {
    if (*p) {
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_HttpStatus __attribute__((cleanup(__sn__HttpStatus_release)))

static inline void __sn__HttpStatus_release_elem(void *p) { __sn__HttpStatus_release((__sn__HttpStatus **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__HttpStatus_to_string(const __sn__HttpStatus *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "HttpStatus { ");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: ResponseHeader (as val) */
typedef struct {
    char * __sn__name;
    char * __sn__value;
} __sn__ResponseHeader;
/* Value operations */
static inline __sn__ResponseHeader __sn__ResponseHeader_copy(const __sn__ResponseHeader *src) {
    __sn__ResponseHeader dst;
    dst.__sn__name = src->__sn__name ? strdup(src->__sn__name) : NULL;
    dst.__sn__value = src->__sn__value ? strdup(src->__sn__value) : NULL;
    return dst;
}

static inline void __sn__ResponseHeader_cleanup(__sn__ResponseHeader *p) {
    free(p->__sn__name);
    free(p->__sn__value);

}

#define sn_auto_ResponseHeader __attribute__((cleanup(__sn__ResponseHeader_cleanup)))

static inline void __sn__ResponseHeader_cleanup_elem(void *p) { __sn__ResponseHeader_cleanup((__sn__ResponseHeader *)p); }
static inline void __sn__ResponseHeader_copy_into(const void *src, void *dst) { *(__sn__ResponseHeader *)dst = __sn__ResponseHeader_copy((const __sn__ResponseHeader *)src); }

/* Ref/pointer operations */
static inline __sn__ResponseHeader *__sn__ResponseHeader_alloc(void) {
    return calloc(1, sizeof(__sn__ResponseHeader));
}

static inline void __sn__ResponseHeader_release(__sn__ResponseHeader **p) {
    if (*p) {
        free((*p)->__sn__name);
        free((*p)->__sn__value);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_ResponseHeader __attribute__((cleanup(__sn__ResponseHeader_release)))

static inline void __sn__ResponseHeader_release_elem(void *p) { __sn__ResponseHeader_release((__sn__ResponseHeader **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__ResponseHeader_to_string(const __sn__ResponseHeader *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "ResponseHeader { ");
    off += snprintf(buf + off, sizeof(buf) - off, "name: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__name ? p->__sn__name : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "value: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__value ? p->__sn__value : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: HttpResponse (as val) */
typedef struct {
    long long __sn__statusCode;
    char * __sn__statusText;
    char * __sn__version;
    SnArray * __sn__headers;
    char * __sn__body;
} __sn__HttpResponse;
/* Value operations */
static inline __sn__HttpResponse __sn__HttpResponse_copy(const __sn__HttpResponse *src) {
    __sn__HttpResponse dst;
    dst.__sn__statusCode = src->__sn__statusCode;
    dst.__sn__statusText = src->__sn__statusText ? strdup(src->__sn__statusText) : NULL;
    dst.__sn__version = src->__sn__version ? strdup(src->__sn__version) : NULL;
    dst.__sn__headers = sn_array_copy(src->__sn__headers);
    dst.__sn__body = src->__sn__body ? strdup(src->__sn__body) : NULL;
    return dst;
}

static inline void __sn__HttpResponse_cleanup(__sn__HttpResponse *p) {
    free(p->__sn__statusText);
    free(p->__sn__version);
    sn_cleanup_array(&p->__sn__headers);
    free(p->__sn__body);

}

#define sn_auto_HttpResponse __attribute__((cleanup(__sn__HttpResponse_cleanup)))

static inline void __sn__HttpResponse_cleanup_elem(void *p) { __sn__HttpResponse_cleanup((__sn__HttpResponse *)p); }
static inline void __sn__HttpResponse_copy_into(const void *src, void *dst) { *(__sn__HttpResponse *)dst = __sn__HttpResponse_copy((const __sn__HttpResponse *)src); }

/* Ref/pointer operations */
static inline __sn__HttpResponse *__sn__HttpResponse_alloc(void) {
    return calloc(1, sizeof(__sn__HttpResponse));
}

static inline void __sn__HttpResponse_release(__sn__HttpResponse **p) {
    if (*p) {
        free((*p)->__sn__statusText);
        free((*p)->__sn__version);
        sn_cleanup_array(&(*p)->__sn__headers);
        free((*p)->__sn__body);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_HttpResponse __attribute__((cleanup(__sn__HttpResponse_release)))

static inline void __sn__HttpResponse_release_elem(void *p) { __sn__HttpResponse_release((__sn__HttpResponse **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__HttpResponse_to_string(const __sn__HttpResponse *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "HttpResponse { ");
    off += snprintf(buf + off, sizeof(buf) - off, "statusCode: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__statusCode);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "statusText: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__statusText ? p->__sn__statusText : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "version: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__version ? p->__sn__version : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "headers: ");
    { char *__fs__ = sn_array_to_string(p->__sn__headers); off += snprintf(buf + off, sizeof(buf) - off, "%s", __fs__); free(__fs__); }
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "body: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__body ? p->__sn__body : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: Route (as val) */
typedef struct {
    char * __sn__method;
    char * __sn__pattern;
    void * __sn__handler;
} __sn__Route;
/* Value operations */
static inline __sn__Route __sn__Route_copy(const __sn__Route *src) {
    __sn__Route dst;
    dst.__sn__method = src->__sn__method ? strdup(src->__sn__method) : NULL;
    dst.__sn__pattern = src->__sn__pattern ? strdup(src->__sn__pattern) : NULL;
    if (src->__sn__handler) { __Closure__ *__src_cl__ = (__Closure__ *)src->__sn__handler; dst.__sn__handler = malloc(__src_cl__->size); memcpy(dst.__sn__handler, __src_cl__, __src_cl__->size); } else { dst.__sn__handler = NULL; }
    return dst;
}

static inline void __sn__Route_cleanup(__sn__Route *p) {
    free(p->__sn__method);
    free(p->__sn__pattern);
    free(p->__sn__handler);

}

#define sn_auto_Route __attribute__((cleanup(__sn__Route_cleanup)))

static inline void __sn__Route_cleanup_elem(void *p) { __sn__Route_cleanup((__sn__Route *)p); }
static inline void __sn__Route_copy_into(const void *src, void *dst) { *(__sn__Route *)dst = __sn__Route_copy((const __sn__Route *)src); }

/* Ref/pointer operations */
static inline __sn__Route *__sn__Route_alloc(void) {
    return calloc(1, sizeof(__sn__Route));
}

static inline void __sn__Route_release(__sn__Route **p) {
    if (*p) {
        free((*p)->__sn__method);
        free((*p)->__sn__pattern);
        free((*p)->__sn__handler);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_Route __attribute__((cleanup(__sn__Route_release)))

static inline void __sn__Route_release_elem(void *p) { __sn__Route_release((__sn__Route **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__Route_to_string(const __sn__Route *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "Route { ");
    off += snprintf(buf + off, sizeof(buf) - off, "method: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__method ? p->__sn__method : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "pattern: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__pattern ? p->__sn__pattern : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "handler: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__handler);
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: Router (as val) */
typedef struct {
    SnArray * __sn__routes;
    void * __sn__notFoundHandler;
    void * __sn__methodNotAllowedHandler;
} __sn__Router;
/* Value operations */
static inline __sn__Router __sn__Router_copy(const __sn__Router *src) {
    __sn__Router dst;
    dst.__sn__routes = sn_array_copy(src->__sn__routes);
    if (src->__sn__notFoundHandler) { __Closure__ *__src_cl__ = (__Closure__ *)src->__sn__notFoundHandler; dst.__sn__notFoundHandler = malloc(__src_cl__->size); memcpy(dst.__sn__notFoundHandler, __src_cl__, __src_cl__->size); } else { dst.__sn__notFoundHandler = NULL; }
    if (src->__sn__methodNotAllowedHandler) { __Closure__ *__src_cl__ = (__Closure__ *)src->__sn__methodNotAllowedHandler; dst.__sn__methodNotAllowedHandler = malloc(__src_cl__->size); memcpy(dst.__sn__methodNotAllowedHandler, __src_cl__, __src_cl__->size); } else { dst.__sn__methodNotAllowedHandler = NULL; }
    return dst;
}

static inline void __sn__Router_cleanup(__sn__Router *p) {
    sn_cleanup_array(&p->__sn__routes);
    free(p->__sn__notFoundHandler);
    free(p->__sn__methodNotAllowedHandler);

}

#define sn_auto_Router __attribute__((cleanup(__sn__Router_cleanup)))

static inline void __sn__Router_cleanup_elem(void *p) { __sn__Router_cleanup((__sn__Router *)p); }
static inline void __sn__Router_copy_into(const void *src, void *dst) { *(__sn__Router *)dst = __sn__Router_copy((const __sn__Router *)src); }

/* Ref/pointer operations */
static inline __sn__Router *__sn__Router_alloc(void) {
    return calloc(1, sizeof(__sn__Router));
}

static inline void __sn__Router_release(__sn__Router **p) {
    if (*p) {
        sn_cleanup_array(&(*p)->__sn__routes);
        free((*p)->__sn__notFoundHandler);
        free((*p)->__sn__methodNotAllowedHandler);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_Router __attribute__((cleanup(__sn__Router_release)))

static inline void __sn__Router_release_elem(void *p) { __sn__Router_release((__sn__Router **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__Router_to_string(const __sn__Router *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "Router { ");
    off += snprintf(buf + off, sizeof(buf) - off, "routes: ");
    { char *__fs__ = sn_array_to_string(p->__sn__routes); off += snprintf(buf + off, sizeof(buf) - off, "%s", __fs__); free(__fs__); }
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "notFoundHandler: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__notFoundHandler);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "methodNotAllowedHandler: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__methodNotAllowedHandler);
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: ServerStats (as val) */
typedef struct {
    long long __sn__totalRequests;
    long long __sn__activeConnections;
    long long __sn__totalErrors;
} __sn__ServerStats;
/* Value operations */
static inline __sn__ServerStats __sn__ServerStats_copy(const __sn__ServerStats *src) {
    __sn__ServerStats dst;
    dst.__sn__totalRequests = src->__sn__totalRequests;
    dst.__sn__activeConnections = src->__sn__activeConnections;
    dst.__sn__totalErrors = src->__sn__totalErrors;
    return dst;
}

static inline void __sn__ServerStats_cleanup(__sn__ServerStats *p) {

}

#define sn_auto_ServerStats __attribute__((cleanup(__sn__ServerStats_cleanup)))

static inline void __sn__ServerStats_cleanup_elem(void *p) { __sn__ServerStats_cleanup((__sn__ServerStats *)p); }
static inline void __sn__ServerStats_copy_into(const void *src, void *dst) { *(__sn__ServerStats *)dst = __sn__ServerStats_copy((const __sn__ServerStats *)src); }

/* Ref/pointer operations */
static inline __sn__ServerStats *__sn__ServerStats_alloc(void) {
    return calloc(1, sizeof(__sn__ServerStats));
}

static inline void __sn__ServerStats_release(__sn__ServerStats **p) {
    if (*p) {
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_ServerStats __attribute__((cleanup(__sn__ServerStats_release)))

static inline void __sn__ServerStats_release_elem(void *p) { __sn__ServerStats_release((__sn__ServerStats **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__ServerStats_to_string(const __sn__ServerStats *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "ServerStats { ");
    off += snprintf(buf + off, sizeof(buf) - off, "totalRequests: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__totalRequests);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "activeConnections: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__activeConnections);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "totalErrors: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__totalErrors);
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: HttpServer (as val) */
typedef struct {
    __sn__Router __sn__router;
    char * __sn__host;
    long long __sn__port;
    long long __sn__maxRequestSize;
    bool __sn__running;
} __sn__HttpServer;
/* Value operations */
static inline __sn__HttpServer __sn__HttpServer_copy(const __sn__HttpServer *src) {
    __sn__HttpServer dst;
    dst.__sn__router = __sn__Router_copy(&src->__sn__router);
    dst.__sn__host = src->__sn__host ? strdup(src->__sn__host) : NULL;
    dst.__sn__port = src->__sn__port;
    dst.__sn__maxRequestSize = src->__sn__maxRequestSize;
    dst.__sn__running = src->__sn__running;
    return dst;
}

static inline void __sn__HttpServer_cleanup(__sn__HttpServer *p) {
    __sn__Router_cleanup(&p->__sn__router);
    free(p->__sn__host);

}

#define sn_auto_HttpServer __attribute__((cleanup(__sn__HttpServer_cleanup)))

static inline void __sn__HttpServer_cleanup_elem(void *p) { __sn__HttpServer_cleanup((__sn__HttpServer *)p); }
static inline void __sn__HttpServer_copy_into(const void *src, void *dst) { *(__sn__HttpServer *)dst = __sn__HttpServer_copy((const __sn__HttpServer *)src); }

/* Ref/pointer operations */
static inline __sn__HttpServer *__sn__HttpServer_alloc(void) {
    return calloc(1, sizeof(__sn__HttpServer));
}

static inline void __sn__HttpServer_release(__sn__HttpServer **p) {
    if (*p) {
        __sn__Router_cleanup(&(*p)->__sn__router);
        free((*p)->__sn__host);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_HttpServer __attribute__((cleanup(__sn__HttpServer_release)))

static inline void __sn__HttpServer_release_elem(void *p) { __sn__HttpServer_release((__sn__HttpServer **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__HttpServer_to_string(const __sn__HttpServer *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "HttpServer { ");
    off += snprintf(buf + off, sizeof(buf) - off, "router: ");
    { char *__fs__ = __sn__Router_to_string(&p->__sn__router); off += snprintf(buf + off, sizeof(buf) - off, "%s", __fs__); free(__fs__); }
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "host: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__host ? p->__sn__host : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "port: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__port);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "maxRequestSize: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__maxRequestSize);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "running: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%s", p->__sn__running ? "true" : "false");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: FastJson (as val) */
typedef struct {
} __sn__FastJson;
/* Value operations */
static inline __sn__FastJson __sn__FastJson_copy(const __sn__FastJson *src) {
    __sn__FastJson dst;
    return dst;
}

static inline void __sn__FastJson_cleanup(__sn__FastJson *p) {

}

#define sn_auto_FastJson __attribute__((cleanup(__sn__FastJson_cleanup)))

static inline void __sn__FastJson_cleanup_elem(void *p) { __sn__FastJson_cleanup((__sn__FastJson *)p); }
static inline void __sn__FastJson_copy_into(const void *src, void *dst) { *(__sn__FastJson *)dst = __sn__FastJson_copy((const __sn__FastJson *)src); }

/* Ref/pointer operations */
static inline __sn__FastJson *__sn__FastJson_alloc(void) {
    return calloc(1, sizeof(__sn__FastJson));
}

static inline void __sn__FastJson_release(__sn__FastJson **p) {
    if (*p) {
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_FastJson __attribute__((cleanup(__sn__FastJson_release)))

static inline void __sn__FastJson_release_elem(void *p) { __sn__FastJson_release((__sn__FastJson **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__FastJson_to_string(const __sn__FastJson *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "FastJson { ");
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}



/* Struct: Item (as val) */
typedef struct {
    long long __sn__id;
    char * __sn__name;
    long long __sn__value;
} __sn__Item;
/* Value operations */
static inline __sn__Item __sn__Item_copy(const __sn__Item *src) {
    __sn__Item dst;
    dst.__sn__id = src->__sn__id;
    dst.__sn__name = src->__sn__name ? strdup(src->__sn__name) : NULL;
    dst.__sn__value = src->__sn__value;
    return dst;
}

static inline void __sn__Item_cleanup(__sn__Item *p) {
    free(p->__sn__name);

}

#define sn_auto_Item __attribute__((cleanup(__sn__Item_cleanup)))

static inline void __sn__Item_cleanup_elem(void *p) { __sn__Item_cleanup((__sn__Item *)p); }
static inline void __sn__Item_copy_into(const void *src, void *dst) { *(__sn__Item *)dst = __sn__Item_copy((const __sn__Item *)src); }

/* Ref/pointer operations */
static inline __sn__Item *__sn__Item_alloc(void) {
    return calloc(1, sizeof(__sn__Item));
}

static inline void __sn__Item_release(__sn__Item **p) {
    if (*p) {
        free((*p)->__sn__name);
        free(*p);
    }
    *p = NULL;
}

#define sn_auto_ref_Item __attribute__((cleanup(__sn__Item_release)))

static inline void __sn__Item_release_elem(void *p) { __sn__Item_release((__sn__Item **)p); }

/* Auto-toString for string interpolation */
static inline char *__sn__Item_to_string(const __sn__Item *p) {
    char buf[1024];
    int off = 0;
    off += snprintf(buf + off, sizeof(buf) - off, "Item { ");
    off += snprintf(buf + off, sizeof(buf) - off, "id: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__id);
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "name: ");
    off += snprintf(buf + off, sizeof(buf) - off, "\"%s\"", p->__sn__name ? p->__sn__name : "nil");
    off += snprintf(buf + off, sizeof(buf) - off, ", ");
    off += snprintf(buf + off, sizeof(buf) - off, "value: ");
    off += snprintf(buf + off, sizeof(buf) - off, "%lld", (long long)p->__sn__value);
    off += snprintf(buf + off, sizeof(buf) - off, " }");
    return strdup(buf);
}

/* @serializable: encode */
static inline void __sn__Item_encode(__sn__Item *__sn__self, __sn__Encoder *__sn__e) {
    __sn__Encoder_writeInt(__sn__e, "id", __sn__self->__sn__id);
    __sn__Encoder_writeStr(__sn__e, "name", __sn__self->__sn__name);
    __sn__Encoder_writeInt(__sn__e, "value", __sn__self->__sn__value);

}

/* @serializable: decode */
static inline __sn__Item __sn__Item_decode(__sn__Decoder *__sn__d) {
    __sn__Item __r__;
    memset(&__r__, 0, sizeof(__r__));
    __r__.__sn__id = __sn__Decoder_readInt(__sn__d, "id");
    __r__.__sn__name = __sn__Decoder_readStr(__sn__d, "name");
    __r__.__sn__value = __sn__Decoder_readInt(__sn__d, "value");
    return __r__;
}



long long __sn__STATUS_CONTINUE = 100LL;

long long __sn__STATUS_SWITCHING_PROTOCOLS = 101LL;

long long __sn__STATUS_OK = 200LL;

long long __sn__STATUS_CREATED = 201LL;

long long __sn__STATUS_ACCEPTED = 202LL;

long long __sn__STATUS_NO_CONTENT = 204LL;

long long __sn__STATUS_RESET_CONTENT = 205LL;

long long __sn__STATUS_PARTIAL_CONTENT = 206LL;

long long __sn__STATUS_MOVED_PERMANENTLY = 301LL;

long long __sn__STATUS_FOUND = 302LL;

long long __sn__STATUS_SEE_OTHER = 303LL;

long long __sn__STATUS_NOT_MODIFIED = 304LL;

long long __sn__STATUS_TEMPORARY_REDIRECT = 307LL;

long long __sn__STATUS_PERMANENT_REDIRECT = 308LL;

long long __sn__STATUS_BAD_REQUEST = 400LL;

long long __sn__STATUS_UNAUTHORIZED = 401LL;

long long __sn__STATUS_FORBIDDEN = 403LL;

long long __sn__STATUS_NOT_FOUND = 404LL;

long long __sn__STATUS_METHOD_NOT_ALLOWED = 405LL;

long long __sn__STATUS_NOT_ACCEPTABLE = 406LL;

long long __sn__STATUS_REQUEST_TIMEOUT = 408LL;

long long __sn__STATUS_CONFLICT = 409LL;

long long __sn__STATUS_GONE = 410LL;

long long __sn__STATUS_LENGTH_REQUIRED = 411LL;

long long __sn__STATUS_PAYLOAD_TOO_LARGE = 413LL;

long long __sn__STATUS_URI_TOO_LONG = 414LL;

long long __sn__STATUS_UNSUPPORTED_MEDIA_TYPE = 415LL;

long long __sn__STATUS_UNPROCESSABLE_ENTITY = 422LL;

long long __sn__STATUS_TOO_MANY_REQUESTS = 429LL;

long long __sn__STATUS_INTERNAL_SERVER_ERROR = 500LL;

long long __sn__STATUS_NOT_IMPLEMENTED = 501LL;

long long __sn__STATUS_BAD_GATEWAY = 502LL;

long long __sn__STATUS_SERVICE_UNAVAILABLE = 503LL;

long long __sn__STATUS_GATEWAY_TIMEOUT = 504LL;

long long __sn__STATUS_HTTP_VERSION_NOT_SUPPORTED = 505LL;

long long __sn__totalRequests = 0LL;
pthread_mutex_t __sn__totalRequests_mutex = PTHREAD_MUTEX_INITIALIZER;

long long __sn__activeConnections = 0LL;
pthread_mutex_t __sn__activeConnections_mutex = PTHREAD_MUTEX_INITIALIZER;

long long __sn__totalErrors = 0LL;
pthread_mutex_t __sn__totalErrors_mutex = PTHREAD_MUTEX_INITIALIZER;

SnArray * __sn__items = NULL;

long long __sn__itemsLock = 0LL;
pthread_mutex_t __sn__itemsLock_mutex = PTHREAD_MUTEX_INITIALIZER;

long long __sn__nextId = 1LL;

long long __sn__maxItems = 1000LL;

__sn__HttpResponse __sn__defaultNotFoundHandler(__sn__HttpRequest *);
__sn__HttpResponse __sn__defaultMethodNotAllowedHandler(__sn__HttpRequest *);
bool __sn__matchPath(char *, char *);
char * __sn__normalizePath(char *);
long long __sn__parseContentLength(char *);
long long __sn__extractId(char *);
char * __sn__encodeItem(__sn__Item *);
__sn__HttpResponse __sn__listItems(__sn__HttpRequest *);
__sn__HttpResponse __sn__createItem(__sn__HttpRequest *);
__sn__HttpResponse __sn__getItem(__sn__HttpRequest *);
__sn__HttpResponse __sn__updateItem(__sn__HttpRequest *);
__sn__HttpResponse __sn__deleteItem(__sn__HttpRequest *);
__sn__HttpResponse __sn__handleItems(__sn__HttpRequest *);
__sn__HttpResponse __sn__handleItem(__sn__HttpRequest *);
__sn__TcpStream * __sn__TcpStream_connect(char *);
SnArray * __sn__TcpStream_read(__sn__TcpStream *, long long);
SnArray * __sn__TcpStream_readAll(__sn__TcpStream *);
char * __sn__TcpStream_readLine(__sn__TcpStream *);
long long sn_tcp_stream_write(__sn__TcpStream *, SnArray *);
void sn_tcp_stream_write_line(__sn__TcpStream *, char *);
char * __sn__TcpStream_remoteAddress(__sn__TcpStream *);
void sn_tcp_stream_set_timeout(__sn__TcpStream *, long long);
void __sn__TcpStream_dispose(__sn__TcpStream *);
__sn__TcpListener * __sn__TcpListener_bind(char *);
__sn__TcpStream * __sn__TcpListener_accept(__sn__TcpListener *);
long long sn_tcp_listener_get_port(__sn__TcpListener *);
void __sn__TcpListener_dispose(__sn__TcpListener *);
__sn__Json * __sn__Json_parse(char *);
__sn__Json * __sn__Json_parseFile(char *);
__sn__Json * __sn__Json_object();
__sn__Json * __sn__Json_array();
__sn__Json * __sn__Json_ofNull();
__sn__Json * __sn__Json_ofBool(bool);
__sn__Json * __sn__Json_ofInt(long long);
__sn__Json * __sn__Json_ofFloat(double);
__sn__Json * __sn__Json_ofString(char *);
bool sn_json_is_object(__sn__Json *);
bool sn_json_is_array(__sn__Json *);
bool sn_json_is_string(__sn__Json *);
bool sn_json_is_number(__sn__Json *);
bool sn_json_is_int(__sn__Json *);
bool sn_json_is_float(__sn__Json *);
bool sn_json_is_bool(__sn__Json *);
bool sn_json_is_null(__sn__Json *);
char * __sn__Json_asString(__sn__Json *);
long long sn_json_as_int(__sn__Json *);
long long sn_json_as_long(__sn__Json *);
double sn_json_as_float(__sn__Json *);
bool sn_json_as_bool(__sn__Json *);
__sn__Json * __sn__Json_get(__sn__Json *, char *);
bool sn_json_has(__sn__Json *, char *);
SnArray * __sn__Json_keys(__sn__Json *);
__sn__Json * __sn__Json_getAt(__sn__Json *, long long);
__sn__Json * __sn__Json_first(__sn__Json *);
__sn__Json * __sn__Json_last(__sn__Json *);
long long sn_json_length(__sn__Json *);
bool __sn__Json_isEmpty(__sn__Json *);
void sn_json_set(__sn__Json *, char *, __sn__Json *);
void sn_json_remove(__sn__Json *, char *);
void sn_json_append(__sn__Json *, __sn__Json *);
void sn_json_prepend(__sn__Json *, __sn__Json *);
void sn_json_insert(__sn__Json *, long long, __sn__Json *);
void sn_json_remove_at(__sn__Json *, long long);
char * __sn__Json_toString(__sn__Json *);
char * __sn__Json_toPrettyString(__sn__Json *);
void sn_json_write_file(__sn__Json *, char *);
void sn_json_write_file_pretty(__sn__Json *, char *);
__sn__Json * __sn__Json_copy(__sn__Json *);
char * __sn__Json_typeName(__sn__Json *);
void sn_json_dispose(__sn__Json *);
__sn__HttpRequest __sn__HttpRequest_parse(char *);
char * __sn__HttpRequest_getHeader(__sn__HttpRequest *, char *);
bool __sn__HttpRequest_hasHeader(__sn__HttpRequest *, char *);
char * __sn__HttpRequest_queryParam(__sn__HttpRequest *, char *);
bool __sn__HttpRequest_hasQueryParam(__sn__HttpRequest *, char *);
char * __sn__HttpRequest_contentType(__sn__HttpRequest *);
long long __sn__HttpRequest_contentLength(__sn__HttpRequest *);
bool __sn__HttpRequest_hasBody(__sn__HttpRequest *);
bool __sn__HttpRequest_isJson(__sn__HttpRequest *);
__sn__Json * __sn__HttpRequest_json(__sn__HttpRequest *);
bool __sn__HttpRequest_isGet(__sn__HttpRequest *);
bool __sn__HttpRequest_isPost(__sn__HttpRequest *);
bool __sn__HttpRequest_isPut(__sn__HttpRequest *);
bool __sn__HttpRequest_isDelete(__sn__HttpRequest *);
bool __sn__HttpRequest_isPatch(__sn__HttpRequest *);
bool __sn__HttpRequest_isHead(__sn__HttpRequest *);
bool __sn__HttpRequest_isOptions(__sn__HttpRequest *);
char * __sn__HttpStatus_text(long long);
bool __sn__HttpStatus_isInformational(long long);
bool __sn__HttpStatus_isSuccess(long long);
bool __sn__HttpStatus_isRedirect(long long);
bool __sn__HttpStatus_isClientError(long long);
bool __sn__HttpStatus_isServerError(long long);
bool __sn__HttpStatus_isError(long long);
__sn__HttpResponse __sn__HttpResponse_new(long long);
__sn__HttpResponse __sn__HttpResponse_ok();
__sn__HttpResponse __sn__HttpResponse_created();
__sn__HttpResponse __sn__HttpResponse_noContent();
__sn__HttpResponse __sn__HttpResponse_badRequest();
__sn__HttpResponse __sn__HttpResponse_unauthorized();
__sn__HttpResponse __sn__HttpResponse_forbidden();
__sn__HttpResponse __sn__HttpResponse_notFound();
__sn__HttpResponse __sn__HttpResponse_methodNotAllowed();
__sn__HttpResponse __sn__HttpResponse_internalServerError();
__sn__HttpResponse __sn__HttpResponse_setHeader(__sn__HttpResponse *, char *, char *);
__sn__HttpResponse __sn__HttpResponse_addHeader(__sn__HttpResponse *, char *, char *);
__sn__HttpResponse __sn__HttpResponse_setBody(__sn__HttpResponse *, char *);
__sn__HttpResponse __sn__HttpResponse_html(__sn__HttpResponse *, char *);
__sn__HttpResponse __sn__HttpResponse_text(__sn__HttpResponse *, char *);
__sn__HttpResponse __sn__HttpResponse_json(__sn__HttpResponse *, char *);
__sn__HttpResponse __sn__HttpResponse_jsonData(__sn__HttpResponse *, __sn__Json *);
__sn__HttpResponse __sn__HttpResponse_jsonPretty(__sn__HttpResponse *, __sn__Json *);
__sn__HttpResponse __sn__HttpResponse_redirect(char *);
char * __sn__HttpResponse_getHeader(__sn__HttpResponse *, char *);
bool __sn__HttpResponse_hasHeader(__sn__HttpResponse *, char *);
char * __sn__HttpResponse_toString(__sn__HttpResponse *);
SnArray * __sn__HttpResponse_toBytes(__sn__HttpResponse *);
__sn__Router __sn__Router_new();
__sn__Router __sn__Router_route(__sn__Router *, char *, char *, void *);
__sn__Router __sn__Router_get(__sn__Router *, char *, void *);
__sn__Router __sn__Router_post(__sn__Router *, char *, void *);
__sn__Router __sn__Router_put(__sn__Router *, char *, void *);
__sn__Router __sn__Router_delete(__sn__Router *, char *, void *);
__sn__Router __sn__Router_patch(__sn__Router *, char *, void *);
__sn__Router __sn__Router_head(__sn__Router *, char *, void *);
__sn__Router __sn__Router_options(__sn__Router *, char *, void *);
__sn__Router __sn__Router_all(__sn__Router *, char *, void *);
__sn__Router __sn__Router_setNotFoundHandler(__sn__Router *, void *);
__sn__Router __sn__Router_setMethodNotAllowedHandler(__sn__Router *, void *);
__sn__HttpResponse __sn__Router_handle(__sn__Router *, __sn__HttpRequest *);
SnArray * __sn__Router_allowedMethods(__sn__Router *, char *);
__sn__HttpServer __sn__HttpServer_new(__sn__Router *);
__sn__HttpServer __sn__HttpServer_onPort(__sn__Router *, long long);
__sn__ServerStats __sn__HttpServer_stats();
void __sn__HttpServer_serve(long long, void *);
void __sn__HttpServer_serveRouter(long long, __sn__Router *);
__sn__HttpServer __sn__HttpServer_setHost(__sn__HttpServer *, char *);
__sn__HttpServer __sn__HttpServer_setPort(__sn__HttpServer *, long long);
__sn__HttpServer __sn__HttpServer_setMaxRequestSize(__sn__HttpServer *, long long);
void __sn__HttpServer_listen(__sn__HttpServer *, long long);
void __sn__HttpServer_start(__sn__HttpServer *);
void __sn__HttpServer_stop(__sn__HttpServer *);
void __sn__HttpServer_handleClient(__sn__HttpServer *, __sn__TcpStream *);
char * __sn__HttpServer_readRequest(__sn__HttpServer *, __sn__TcpStream *);
__sn__Encoder * __sn__FastJson_encoder();
__sn__Decoder * __sn__FastJson_decoder(char *);
#include "tcp.sn.c"
#include "json.sn.c"
#include "fast_json.sn.c"

typedef struct {
    __sn__HttpServer * self_arg;
    __sn__TcpStream * arg0;
    int _padding;
} __ThreadArgs_0__;

static void *__thread_wrapper_0__(void *arg) {
    SnThread *__th__ = (SnThread *)arg;
    __ThreadArgs_0__ *args = (__ThreadArgs_0__ *)__th__->result;
    __ThreadArgs_0__ __args_copy__ = *args;
    args = &__args_copy__;

    __sn__HttpServer_handleClient(args->self_arg, args->arg0);
    free(__th__->result); __th__->result = NULL;
    free(__th__);
    return NULL;
}
typedef struct __Closure__ {
    void *fn;
    size_t size;
    void (*__cleanup__)(void *);
} __Closure__;

static __sn__HttpResponse __fn_wrap_0__(void *__closure__, __sn__HttpRequest __p0__) {
    (void)__closure__;
    __sn__HttpResponse __ret__ = __sn__defaultNotFoundHandler(&__p0__);
    __sn__HttpRequest_cleanup(&__p0__); 
    return __ret__;
 }

static __sn__HttpResponse __fn_wrap_1__(void *__closure__, __sn__HttpRequest __p0__) {
    (void)__closure__;
    __sn__HttpResponse __ret__ = __sn__defaultMethodNotAllowedHandler(&__p0__);
    __sn__HttpRequest_cleanup(&__p0__); 
    return __ret__;
 }

static __sn__HttpResponse __fn_wrap_2__(void *__closure__, __sn__HttpRequest __p0__) {
    (void)__closure__;
    __sn__HttpResponse __ret__ = __sn__handleItems(&__p0__);
    __sn__HttpRequest_cleanup(&__p0__); 
    return __ret__;
 }

static __sn__HttpResponse __fn_wrap_3__(void *__closure__, __sn__HttpRequest __p0__) {
    (void)__closure__;
    __sn__HttpResponse __ret__ = __sn__handleItem(&__p0__);
    __sn__HttpRequest_cleanup(&__p0__); 
    return __ret__;
 }


__sn__HttpResponse __sn__defaultNotFoundHandler(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    sn_auto_HttpResponse __sn__HttpResponse __sn__res = __sn__HttpResponse_notFound();

    sn_auto_str char * __sn____chain_tmp_0 = ({
            char __is_buf__[1024];
            int __is_off__ = 0;
            __is_buf__[0] = '\0';
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "404 Not Found: ");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__req.__sn__path);
            strdup(__is_buf__);
        });

    return __sn__HttpResponse_text(&__sn__res, __sn____chain_tmp_0);}


__sn__HttpResponse __sn__defaultMethodNotAllowedHandler(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    sn_auto_HttpResponse __sn__HttpResponse __sn__res = __sn__HttpResponse_methodNotAllowed();

    sn_auto_str char * __sn____chain_tmp_1 = ({
            char __is_buf__[1024];
            int __is_off__ = 0;
            __is_buf__[0] = '\0';
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "405 Method Not Allowed: ");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__req.__sn__method);
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", " ");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__req.__sn__path);
            strdup(__is_buf__);
        });

    return __sn__HttpResponse_text(&__sn__res, __sn____chain_tmp_1);}


bool __sn__matchPath(char * __sn__pattern, char * __sn__path) {

    sn_auto_str char * __sn__p = __sn__normalizePath(__sn__pattern);

    sn_auto_str char * __sn__r = __sn__normalizePath(__sn__path);

    if ((strcmp(__sn__p, __sn__r) == 0)) {
        return true;}

    if (__sn___endsWith(&__sn__p, "/**")) {
        sn_auto_str char * __sn__prefix = __sn___substring(&__sn__p, 0LL, sn_sub_long(sn_str_length(__sn__p), 3LL));
        return __sn___startsWith(&__sn__r, __sn__prefix);}

    if (__sn___endsWith(&__sn__p, "/*")) {
        sn_auto_str char * __sn__prefix = __sn___substring(&__sn__p, 0LL, sn_sub_long(sn_str_length(__sn__p), 2LL));
        if ((!__sn___startsWith(&__sn__r, __sn__prefix))) {
            return false;}
        sn_auto_str char * __sn__suffix = __sn___substring(&__sn__r, sn_str_length(__sn__prefix), sn_str_length(__sn__r));
        if (((strcmp(__sn__suffix, "/") == 0) || (strcmp(__sn__suffix, "") == 0))) {
            return true;}
        if (__sn___startsWith(&__sn__suffix, "/")) {
            ({
                char *__sn_tmp__ = __sn___substring(&__sn__suffix, 1LL, sn_str_length(__sn__suffix));
                free(__sn__suffix);
                __sn__suffix = __sn_tmp__;
                __sn__suffix;
            });
            
        }
        return (!__sn___contains(&__sn__suffix, "/"));}

    sn_auto_arr SnArray * __sn__patternParts = __sn___split(&__sn__p, "/");

    sn_auto_arr SnArray * __sn__pathParts = __sn___split(&__sn__r, "/");

    if ((sn_array_length(__sn__patternParts) != sn_array_length(__sn__pathParts))) {
        return false;}

    {
        for (long long __sn__i = 0LL; sn_lt_long(__sn__i, sn_array_length(__sn__patternParts)); __sn__i++) {
            sn_auto_str char * __sn__pp = strdup((((char * *)__sn__patternParts->data)[({ long long __ai__ = __sn__i; __ai__ < 0 ? __ai__ + __sn__patternParts->len : __ai__; })]));
            sn_auto_str char * __sn__rp = strdup((((char * *)__sn__pathParts->data)[({ long long __ai__ = __sn__i; __ai__ < 0 ? __ai__ + __sn__pathParts->len : __ai__; })]));
            if ((strcmp(__sn__pp, "*") == 0)) {
                continue;
            }
            if ((strcmp(__sn__pp, __sn__rp) != 0)) {
                return false;}
        }
    }

    return true;}


char * __sn__normalizePath(char * __sn__path) {

    sn_auto_str char * __sn__p = strdup(__sn__path);

    if ((!__sn___startsWith(&__sn__p, "/"))) {
        ({
            char *__sn_tmp__ = sn_str_concat("/", __sn__p);
            free(__sn__p);
            __sn__p = __sn_tmp__;
            __sn__p;
        });
        
    }

    if ((sn_gt_long(sn_str_length(__sn__p), 1LL) && __sn___endsWith(&__sn__p, "/"))) {
        ({
            char *__sn_tmp__ = __sn___substring(&__sn__p, 0LL, sn_sub_long(sn_str_length(__sn__p), 1LL));
            free(__sn__p);
            __sn__p = __sn_tmp__;
            __sn__p;
        });
        
    }

    {
        char * __ret__ = __sn__p;
        __sn__p = NULL;
        return __ret__;
    }}


long long __sn__parseContentLength(char * __sn__data) {

    sn_auto_arr SnArray * __sn__lines = __sn___split(&__sn__data, "\r\n");

    {
        SnArray *__arr_0__ = __sn__lines;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            char * __sn__line = ((char * *)__arr_0__->data)[__idx_0__];
            {
                sn_auto_str char * __sn__lowerLine = __sn___toLower(&__sn__line);
                if (__sn___startsWith(&__sn__lowerLine, "content-length:")) {
                    sn_auto_str char * __sn____chain_tmp_2 = __sn___substring(&__sn__line, 15LL, sn_str_length(__sn__line));
                    sn_auto_str char * __sn__valueStr = __sn___trim(&__sn____chain_tmp_2);
                    return __sn__str_toInt(&__sn__valueStr);}
            }
        }
    }

    return 0LL;}


long long __sn__extractId(char * __sn__path) {

    sn_auto_arr SnArray * __sn__parts = __sn___split(&__sn__path, "/");

    if ((sn_array_length(__sn__parts) >= 3LL)) {
        return __sn__str_toInt(&(((char * *)__sn__parts->data)[({ long long __ai__ = 2LL; __ai__ < 0 ? __ai__ + __sn__parts->len : __ai__; })]));}

    return (-1LL);}


char * __sn__encodeItem(__sn__Item *__bp__item) {
    __sn__Item __sn__item = *__bp__item;

    sn_auto_Encoder __sn__Encoder * __sn__enc = __sn__FastJson_encoder();

    __sn__Item_encode(&__sn__item, __sn__enc);
    

    return __sn__Encoder_result(__sn__enc);}


__sn__HttpResponse __sn__listItems(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    sn_auto_str char * __sn__body = NULL;

    pthread_mutex_lock(&__sn__itemsLock_mutex);
    {
        sn_auto_arr SnArray * __sn__parts = ({
                SnArray *__al__ = sn_array_new(sizeof(char *), 0);
                __al__->elem_tag = SN_TAG_STRING;
        
                __al__->elem_release = (void (*)(void *))sn_cleanup_str;
        
                __al__->elem_copy = sn_copy_str;
                __al__;
            });
        {
            sn_auto_arr SnArray *__arr_0__ = sn_array_range(0LL, sn_array_length(__sn__items));
            long long __len_0__ = __arr_0__->len;
            for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
                long long __sn__i = ((long long *)__arr_0__->data)[__idx_0__];
                {
                    if (sn_gt_long(sn_str_length((((__sn__Item *)__sn__items->data)[({ long long __ai__ = __sn__i; __ai__ < 0 ? __ai__ + __sn__items->len : __ai__; })]).__sn__name), 0LL)) {
                        sn_auto_str char * __sn____chain_tmp_3 = __sn__encodeItem(&(((__sn__Item *)__sn__items->data)[({ long long __ai__ = __sn__i; __ai__ < 0 ? __ai__ + __sn__items->len : __ai__; })]));
                        __sn__arr_push(&__sn__parts, strdup(__sn____chain_tmp_3));
                        
                    }
                }
            }
        }
        ({
            char *__sn_tmp__ = ({
            sn_auto_str char *__sct_1__ = __sn__arr_join(&__sn__parts, ",");
            sn_str_concat_multi(3, "[", __sct_1__, "]");
        });
            free(__sn__body);
            __sn__body = __sn_tmp__;
            __sn__body;
        });
        
    }
    pthread_mutex_unlock(&__sn__itemsLock_mutex);

    sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_4 = __sn__HttpResponse_ok();

    return __sn__HttpResponse_json(&__sn____chain_tmp_4, __sn__body);}


__sn__HttpResponse __sn__createItem(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    if ((!__sn__HttpRequest_isJson(&__sn__req))) {
        sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_5 = __sn__HttpResponse_badRequest();
        return __sn__HttpResponse_json(&__sn____chain_tmp_5, "{\"error\": \"Content-Type must be application/json\"}");}

    sn_auto_Item __sn__Item __sn__incoming = __sn__Item_decode(__sn__FastJson_decoder(__sn__req.__sn__body));

    sn_auto_str char * __sn__itemJson = NULL;

    pthread_mutex_lock(&__sn__itemsLock_mutex);
    {
        long long __sn__id = sn_add_long(sn_mod_long(__sn__nextId, __sn__maxItems), 1LL);
        (__sn__nextId = sn_add_long(__sn__nextId, 1LL));
        
        (__sn__incoming.__sn__id = __sn__id);
        
        ({
            char *__sn_tmp__ = __sn__encodeItem(&__sn__incoming);
            free(__sn__itemJson);
            __sn__itemJson = __sn_tmp__;
            __sn__itemJson;
        });
        
        ({
            long long __ai__ = sn_sub_long(__sn__id, 1LL); if (__ai__ < 0) __ai__ += __sn__items->len;
            __sn__Item_cleanup(&((__sn__Item *)__sn__items->data)[__ai__]);
            __sn__Item_copy_into(&(__sn__incoming), &((__sn__Item *)__sn__items->data)[__ai__]);
        });
        
    }
    pthread_mutex_unlock(&__sn__itemsLock_mutex);

    sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_6 = __sn__HttpResponse_ok();

    return __sn__HttpResponse_json(&__sn____chain_tmp_6, __sn__itemJson);}


__sn__HttpResponse __sn__getItem(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    long long __sn__id = __sn__extractId(__sn__req.__sn__path);

    sn_auto_str char * __sn__itemJson = NULL;

    pthread_mutex_lock(&__sn__itemsLock_mutex);
    {
        if (((__sn__id >= 1LL) && (__sn__id <= __sn__maxItems))) {
            ({
                char *__sn_tmp__ = __sn__encodeItem(&(((__sn__Item *)__sn__items->data)[({ long long __ai__ = sn_sub_long(__sn__id, 1LL); __ai__ < 0 ? __ai__ + __sn__items->len : __ai__; })]));
                free(__sn__itemJson);
                __sn__itemJson = __sn_tmp__;
                __sn__itemJson;
            });
            
        } else {
            ({
                char *__sn_tmp__ = strdup("");
                free(__sn__itemJson);
                __sn__itemJson = __sn_tmp__;
                __sn__itemJson;
            });
            
        }
    }
    pthread_mutex_unlock(&__sn__itemsLock_mutex);

    if ((sn_str_length(__sn__itemJson) == 0LL)) {
        sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_7 = __sn__HttpResponse_ok();
        sn_auto_str char * __sn____chain_tmp_8 = __sn__encodeItem(({ __sn__Item __borrow_tmp__ = (__sn__Item){ .__sn__id = __sn__id, .__sn__name = strdup(""), .__sn__value = 0LL }; &__borrow_tmp__; }));
        return __sn__HttpResponse_json(&__sn____chain_tmp_7, __sn____chain_tmp_8);}

    sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_9 = __sn__HttpResponse_ok();

    return __sn__HttpResponse_json(&__sn____chain_tmp_9, __sn__itemJson);}


__sn__HttpResponse __sn__updateItem(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    if ((!__sn__HttpRequest_isJson(&__sn__req))) {
        sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_10 = __sn__HttpResponse_badRequest();
        return __sn__HttpResponse_json(&__sn____chain_tmp_10, "{\"error\": \"Content-Type must be application/json\"}");}

    long long __sn__id = __sn__extractId(__sn__req.__sn__path);

    sn_auto_Item __sn__Item __sn__incoming = __sn__Item_decode(__sn__FastJson_decoder(__sn__req.__sn__body));

    (__sn__incoming.__sn__id = __sn__id);
    

    pthread_mutex_lock(&__sn__itemsLock_mutex);
    {
        if (((__sn__id >= 1LL) && (__sn__id <= __sn__maxItems))) {
            ({
                long long __ai__ = sn_sub_long(__sn__id, 1LL); if (__ai__ < 0) __ai__ += __sn__items->len;
                __sn__Item_cleanup(&((__sn__Item *)__sn__items->data)[__ai__]);
                __sn__Item_copy_into(&(__sn__incoming), &((__sn__Item *)__sn__items->data)[__ai__]);
            });
            
        }
    }
    pthread_mutex_unlock(&__sn__itemsLock_mutex);

    sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_11 = __sn__HttpResponse_ok();

    sn_auto_str char * __sn____chain_tmp_12 = __sn__encodeItem(&__sn__incoming);

    return __sn__HttpResponse_json(&__sn____chain_tmp_11, __sn____chain_tmp_12);}


__sn__HttpResponse __sn__deleteItem(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    long long __sn__id = __sn__extractId(__sn__req.__sn__path);

    pthread_mutex_lock(&__sn__itemsLock_mutex);
    {
        if (((__sn__id >= 1LL) && (__sn__id <= __sn__maxItems))) {
            ({
                long long __ai__ = sn_sub_long(__sn__id, 1LL); if (__ai__ < 0) __ai__ += __sn__items->len;
                __sn__Item_cleanup(&((__sn__Item *)__sn__items->data)[__ai__]);
                ((__sn__Item *)__sn__items->data)[__ai__] = (__sn__Item){ .__sn__id = 0LL, .__sn__name = strdup(""), .__sn__value = 0LL };
            });
            
        }
    }
    pthread_mutex_unlock(&__sn__itemsLock_mutex);

    sn_auto_HttpResponse __sn__HttpResponse __sn____chain_tmp_13 = __sn__HttpResponse_ok();

    return __sn__HttpResponse_json(&__sn____chain_tmp_13, "{\"deleted\": true}");}


__sn__HttpResponse __sn__handleItems(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    return ({
             __sn__HttpResponse __match_result__;
             char * __match_subject__ = __sn__req.__sn__method;
             if (strcmp(__match_subject__, "GET") == 0) {
                 __match_result__ = __sn__listItems(&__sn__req);
             } else if (strcmp(__match_subject__, "POST") == 0) {
                 __match_result__ = __sn__createItem(&__sn__req);
             } else {
                 __match_result__ = __sn__HttpResponse_text(({ __sn__HttpResponse __mc_tmp__ = __sn__HttpResponse_new(405LL); &__mc_tmp__; }), "Method not allowed");
             }
             __match_result__;
         });}


__sn__HttpResponse __sn__handleItem(__sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    return ({
             __sn__HttpResponse __match_result__;
             char * __match_subject__ = __sn__req.__sn__method;
             if (strcmp(__match_subject__, "GET") == 0) {
                 __match_result__ = __sn__getItem(&__sn__req);
             } else if (strcmp(__match_subject__, "PUT") == 0) {
                 __match_result__ = __sn__updateItem(&__sn__req);
             } else if (strcmp(__match_subject__, "DELETE") == 0) {
                 __match_result__ = __sn__deleteItem(&__sn__req);
             } else {
                 __match_result__ = __sn__HttpResponse_text(({ __sn__HttpResponse __mc_tmp__ = __sn__HttpResponse_new(405LL); &__mc_tmp__; }), "Method not allowed");
             }
             __match_result__;
         });}


__sn__TcpStream * __sn__TcpStream_connect(char * __sn__address) {

    return sn_tcp_stream_connect(__sn__address);}

SnArray * __sn__TcpStream_read(__sn__TcpStream *__sn__self, long long __sn__maxBytes) {

    return sn_tcp_stream_read(__sn__self, __sn__maxBytes);}

SnArray * __sn__TcpStream_readAll(__sn__TcpStream *__sn__self) {

    return sn_tcp_stream_read_all(__sn__self);}

char * __sn__TcpStream_readLine(__sn__TcpStream *__sn__self) {

    return sn_tcp_stream_read_line(__sn__self);}

char * __sn__TcpStream_remoteAddress(__sn__TcpStream *__sn__self) {

    return sn_tcp_stream_get_remote_address(__sn__self);}

void __sn__TcpStream_dispose(__sn__TcpStream *__sn__self) {

    sn_tcp_stream_dispose(__sn__self);
    
}


__sn__TcpListener * __sn__TcpListener_bind(char * __sn__address) {

    return sn_tcp_listener_bind(__sn__address);}

__sn__TcpStream * __sn__TcpListener_accept(__sn__TcpListener *__sn__self) {

    return sn_tcp_listener_accept(__sn__self);}

void __sn__TcpListener_dispose(__sn__TcpListener *__sn__self) {

    sn_tcp_listener_dispose(__sn__self);
    
}


__sn__Json * __sn__Json_parse(char * __sn__text) {

    return sn_json_parse(__sn__text);}

__sn__Json * __sn__Json_parseFile(char * __sn__path) {

    return sn_json_parse_file(__sn__path);}

__sn__Json * __sn__Json_object() {

    return sn_json_new_object();}

__sn__Json * __sn__Json_array() {

    return sn_json_new_array();}

__sn__Json * __sn__Json_ofNull() {

    return sn_json_new_null();}

__sn__Json * __sn__Json_ofBool(bool __sn__value) {

    return sn_json_new_bool(__sn__value);}

__sn__Json * __sn__Json_ofInt(long long __sn__value) {

    return sn_json_new_int(__sn__value);}

__sn__Json * __sn__Json_ofFloat(double __sn__value) {

    return sn_json_new_float(__sn__value);}

__sn__Json * __sn__Json_ofString(char * __sn__value) {

    return sn_json_new_string(__sn__value);}

char * __sn__Json_asString(__sn__Json *__sn__self) {

    return sn_json_as_string(__sn__self);}

__sn__Json * __sn__Json_get(__sn__Json *__sn__self, char * __sn__key) {

    return sn_json_get(__sn__self, __sn__key);}

SnArray * __sn__Json_keys(__sn__Json *__sn__self) {

    return sn_json_keys(__sn__self);}

__sn__Json * __sn__Json_getAt(__sn__Json *__sn__self, long long __sn__index) {

    return sn_json_get_at(__sn__self, __sn__index);}

__sn__Json * __sn__Json_first(__sn__Json *__sn__self) {

    return sn_json_first(__sn__self);}

__sn__Json * __sn__Json_last(__sn__Json *__sn__self) {

    return sn_json_last(__sn__self);}

bool __sn__Json_isEmpty(__sn__Json *__sn__self) {

    return (sn_json_length(__sn__self) == 0LL);}

char * __sn__Json_toString(__sn__Json *__sn__self) {

    return sn_json_to_string(__sn__self);}

char * __sn__Json_toPrettyString(__sn__Json *__sn__self) {

    return sn_json_to_pretty_string(__sn__self);}

__sn__Json * __sn__Json_copy(__sn__Json *__sn__self) {

    return sn_json_copy(__sn__self);}

char * __sn__Json_typeName(__sn__Json *__sn__self) {

    return sn_json_type_name(__sn__self);}



__sn__HttpRequest __sn__HttpRequest_parse(char * __sn__data) {

    __sn__HttpRequest __sn__req = (__sn__HttpRequest){ .__sn__method = strdup(""), .__sn__path = strdup(""), .__sn__query = strdup(""), .__sn__version = strdup(""), .__sn__headers = ({
            SnArray *__al__ = sn_array_new(sizeof(__sn__Header), 0);
            __al__->elem_tag = SN_TAG_STRUCT;
    
            __al__->elem_release = __sn__Header_cleanup_elem;
    
            __al__->elem_copy = __sn__Header_copy_into;
            __al__;
        }), .__sn__body = strdup(""), .__sn__raw = strdup(__sn__data) };

    sn_auto_str char * __sn__normalized = __sn___replace(&__sn__data, "\r\n", "\n");

    sn_auto_arr SnArray * __sn__lines = __sn___split(&__sn__normalized, "\n");

    if ((sn_array_length(__sn__lines) == 0LL)) {
        {
            __sn__HttpRequest __ret__ = __sn__req;
            memset(&__sn__req, 0, sizeof(__sn__req));
            return __ret__;
        }}

    sn_auto_str char * __sn__requestLine = strdup((((char * *)__sn__lines->data)[({ long long __ai__ = 0LL; __ai__ < 0 ? __ai__ + __sn__lines->len : __ai__; })]));

    sn_auto_arr SnArray * __sn__parts = __sn___split(&__sn__requestLine, " ");

    if ((sn_array_length(__sn__parts) >= 1LL)) {
        ({
            free(__sn__req.__sn__method);
            __sn__req.__sn__method = strdup((((char * *)__sn__parts->data)[({ long long __ai__ = 0LL; __ai__ < 0 ? __ai__ + __sn__parts->len : __ai__; })]));
            __sn__req.__sn__method;
        });
        
    }

    if ((sn_array_length(__sn__parts) >= 2LL)) {
        sn_auto_str char * __sn__fullPath = strdup((((char * *)__sn__parts->data)[({ long long __ai__ = 1LL; __ai__ < 0 ? __ai__ + __sn__parts->len : __ai__; })]));
        long long __sn__qIndex = __sn___indexOf(&__sn__fullPath, "?");
        if ((__sn__qIndex >= 0LL)) {
            ({
                free(__sn__req.__sn__path);
                __sn__req.__sn__path = __sn___substring(&__sn__fullPath, 0LL, __sn__qIndex);
                __sn__req.__sn__path;
            });
            
            ({
                free(__sn__req.__sn__query);
                __sn__req.__sn__query = __sn___substring(&__sn__fullPath, sn_add_long(__sn__qIndex, 1LL), sn_str_length(__sn__fullPath));
                __sn__req.__sn__query;
            });
            
        } else {
            ({
                free(__sn__req.__sn__path);
                __sn__req.__sn__path = strdup(__sn__fullPath);
                __sn__req.__sn__path;
            });
            
        }
    }

    if ((sn_array_length(__sn__parts) >= 3LL)) {
        ({
            free(__sn__req.__sn__version);
            __sn__req.__sn__version = strdup((((char * *)__sn__parts->data)[({ long long __ai__ = 2LL; __ai__ < 0 ? __ai__ + __sn__parts->len : __ai__; })]));
            __sn__req.__sn__version;
        });
        
    }

    bool __sn__headersDone = false;

    long long __sn__bodyStartIndex = 1LL;

    {
        for (long long __sn__i = 1LL; sn_lt_long(__sn__i, sn_array_length(__sn__lines)); __sn__i++) {
            sn_auto_str char * __sn__line = strdup((((char * *)__sn__lines->data)[({ long long __ai__ = __sn__i; __ai__ < 0 ? __ai__ + __sn__lines->len : __ai__; })]));
            if (({char *__sct0__=__sn___trim(&__sn__line);bool __scr__=(strcmp(__sct0__,"")==0);free(__sct0__);__scr__;})) {
                (__sn__headersDone = true);
                
                (__sn__bodyStartIndex = sn_add_long(__sn__i, 1LL));
                
                break;
            }
            long long __sn__colonIndex = __sn___indexOf(&__sn__line, ":");
            if (sn_gt_long(__sn__colonIndex, 0LL)) {
                sn_auto_str char * __sn____chain_tmp_14 = __sn___substring(&__sn__line, 0LL, __sn__colonIndex);
                sn_auto_str char * __sn__name = __sn___trim(&__sn____chain_tmp_14);
                sn_auto_str char * __sn____chain_tmp_15 = __sn___substring(&__sn__line, sn_add_long(__sn__colonIndex, 1LL), sn_str_length(__sn__line));
                sn_auto_str char * __sn__value = __sn___trim(&__sn____chain_tmp_15);
                __sn__arr_push(&__sn__req.__sn__headers, (__sn__Header){ .__sn__name = strdup(__sn__name), .__sn__value = strdup(__sn__value) });
                
            }
        }
    }

    if ((__sn__headersDone && sn_lt_long(__sn__bodyStartIndex, sn_array_length(__sn__lines)))) {
        sn_auto_arr SnArray * __sn__bodyLines = ({
                SnArray *__al__ = sn_array_new(sizeof(char *), 0);
                __al__->elem_tag = SN_TAG_STRING;
        
                __al__->elem_release = (void (*)(void *))sn_cleanup_str;
        
                __al__->elem_copy = sn_copy_str;
                __al__;
            });
        {
            for (long long __sn__i = __sn__bodyStartIndex; sn_lt_long(__sn__i, sn_array_length(__sn__lines)); __sn__i++) {
                __sn__arr_push(&__sn__bodyLines, strdup((((char * *)__sn__lines->data)[({ long long __ai__ = __sn__i; __ai__ < 0 ? __ai__ + __sn__lines->len : __ai__; })])));
                
            }
        }
        ({
            free(__sn__req.__sn__body);
            __sn__req.__sn__body = __sn__arr_join(&__sn__bodyLines, "\n");
            __sn__req.__sn__body;
        });
        
    }

    {
        __sn__HttpRequest __ret__ = __sn__req;
        memset(&__sn__req, 0, sizeof(__sn__req));
        return __ret__;
    }}

char * __sn__HttpRequest_getHeader(__sn__HttpRequest *__sn__self, char * __sn__name) {

    sn_auto_str char * __sn__lowerName = __sn___toLower(&__sn__name);

    {
        SnArray *__arr_0__ = __sn__self->__sn__headers;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__Header __sn__h = ((__sn__Header *)__arr_0__->data)[__idx_0__];
            {
                if (({char *__sct0__=__sn___toLower(&__sn__h.__sn__name);bool __scr__=(strcmp(__sct0__,__sn__lowerName)==0);free(__sct0__);__scr__;})) {
                    return strdup(__sn__h.__sn__value);}
            }
        }
    }

    return strdup("");}

bool __sn__HttpRequest_hasHeader(__sn__HttpRequest *__sn__self, char * __sn__name) {

    sn_auto_str char * __sn__lowerName = __sn___toLower(&__sn__name);

    {
        SnArray *__arr_0__ = __sn__self->__sn__headers;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__Header __sn__h = ((__sn__Header *)__arr_0__->data)[__idx_0__];
            {
                if (({char *__sct0__=__sn___toLower(&__sn__h.__sn__name);bool __scr__=(strcmp(__sct0__,__sn__lowerName)==0);free(__sct0__);__scr__;})) {
                    return true;}
            }
        }
    }

    return false;}

char * __sn__HttpRequest_queryParam(__sn__HttpRequest *__sn__self, char * __sn__name) {

    if ((strcmp(__sn__self->__sn__query, "") == 0)) {
        return strdup("");}

    sn_auto_arr SnArray * __sn__pairs = __sn___split(&__sn__self->__sn__query, "&");

    {
        SnArray *__arr_0__ = __sn__pairs;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            char * __sn__pair = ((char * *)__arr_0__->data)[__idx_0__];
            {
                long long __sn__eqIndex = __sn___indexOf(&__sn__pair, "=");
                if (sn_gt_long(__sn__eqIndex, 0LL)) {
                    sn_auto_str char * __sn__key = __sn___substring(&__sn__pair, 0LL, __sn__eqIndex);
                    if ((strcmp(__sn__key, __sn__name) == 0)) {
                        return __sn___substring(&__sn__pair, sn_add_long(__sn__eqIndex, 1LL), sn_str_length(__sn__pair));}
                } else {
                    if ((strcmp(__sn__pair, __sn__name) == 0)) {
                        return strdup("");}
                }
            }
        }
    }

    return strdup("");}

bool __sn__HttpRequest_hasQueryParam(__sn__HttpRequest *__sn__self, char * __sn__name) {

    if ((strcmp(__sn__self->__sn__query, "") == 0)) {
        return false;}

    sn_auto_arr SnArray * __sn__pairs = __sn___split(&__sn__self->__sn__query, "&");

    {
        SnArray *__arr_0__ = __sn__pairs;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            char * __sn__pair = ((char * *)__arr_0__->data)[__idx_0__];
            {
                long long __sn__eqIndex = __sn___indexOf(&__sn__pair, "=");
                if (sn_gt_long(__sn__eqIndex, 0LL)) {
                    sn_auto_str char * __sn__key = __sn___substring(&__sn__pair, 0LL, __sn__eqIndex);
                    if ((strcmp(__sn__key, __sn__name) == 0)) {
                        return true;}
                } else {
                    if ((strcmp(__sn__pair, __sn__name) == 0)) {
                        return true;}
                }
            }
        }
    }

    return false;}

char * __sn__HttpRequest_contentType(__sn__HttpRequest *__sn__self) {

    return __sn__HttpRequest_getHeader(__sn__self, "Content-Type");}

long long __sn__HttpRequest_contentLength(__sn__HttpRequest *__sn__self) {

    sn_auto_str char * __sn__lenStr = __sn__HttpRequest_getHeader(__sn__self, "Content-Length");

    if ((strcmp(__sn__lenStr, "") == 0)) {
        return 0LL;}

    return __sn__str_toInt(&__sn__lenStr);}

bool __sn__HttpRequest_hasBody(__sn__HttpRequest *__sn__self) {

    return sn_gt_long(sn_str_length(__sn__self->__sn__body), 0LL);}

bool __sn__HttpRequest_isJson(__sn__HttpRequest *__sn__self) {

    sn_auto_str char * __sn____chain_tmp_16 = __sn__HttpRequest_contentType(__sn__self);

    sn_auto_str char * __sn__ct = __sn___toLower(&__sn____chain_tmp_16);

    return __sn___startsWith(&__sn__ct, "application/json");}

__sn__Json * __sn__HttpRequest_json(__sn__HttpRequest *__sn__self) {

    if ((sn_str_length(__sn__self->__sn__body) == 0LL)) {
        return __sn__Json_object();}

    return __sn__Json_parse(__sn__self->__sn__body);}

bool __sn__HttpRequest_isGet(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "GET") == 0);}

bool __sn__HttpRequest_isPost(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "POST") == 0);}

bool __sn__HttpRequest_isPut(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "PUT") == 0);}

bool __sn__HttpRequest_isDelete(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "DELETE") == 0);}

bool __sn__HttpRequest_isPatch(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "PATCH") == 0);}

bool __sn__HttpRequest_isHead(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "HEAD") == 0);}

bool __sn__HttpRequest_isOptions(__sn__HttpRequest *__sn__self) {

    return (strcmp(__sn__self->__sn__method, "OPTIONS") == 0);}


char * __sn__HttpStatus_text(long long __sn__code) {

    sn_auto_str char * __sn__result = ({
            char * __match_result__;
            long long __match_subject__ = __sn__code;
            if (__match_subject__ == 100LL) {
                __match_result__ = strdup("Continue");
            } else if (__match_subject__ == 101LL) {
                __match_result__ = strdup("Switching Protocols");
            } else if (__match_subject__ == 200LL) {
                __match_result__ = strdup("OK");
            } else if (__match_subject__ == 201LL) {
                __match_result__ = strdup("Created");
            } else if (__match_subject__ == 202LL) {
                __match_result__ = strdup("Accepted");
            } else if (__match_subject__ == 204LL) {
                __match_result__ = strdup("No Content");
            } else if (__match_subject__ == 205LL) {
                __match_result__ = strdup("Reset Content");
            } else if (__match_subject__ == 206LL) {
                __match_result__ = strdup("Partial Content");
            } else if (__match_subject__ == 301LL) {
                __match_result__ = strdup("Moved Permanently");
            } else if (__match_subject__ == 302LL) {
                __match_result__ = strdup("Found");
            } else if (__match_subject__ == 303LL) {
                __match_result__ = strdup("See Other");
            } else if (__match_subject__ == 304LL) {
                __match_result__ = strdup("Not Modified");
            } else if (__match_subject__ == 307LL) {
                __match_result__ = strdup("Temporary Redirect");
            } else if (__match_subject__ == 308LL) {
                __match_result__ = strdup("Permanent Redirect");
            } else if (__match_subject__ == 400LL) {
                __match_result__ = strdup("Bad Request");
            } else if (__match_subject__ == 401LL) {
                __match_result__ = strdup("Unauthorized");
            } else if (__match_subject__ == 403LL) {
                __match_result__ = strdup("Forbidden");
            } else if (__match_subject__ == 404LL) {
                __match_result__ = strdup("Not Found");
            } else if (__match_subject__ == 405LL) {
                __match_result__ = strdup("Method Not Allowed");
            } else if (__match_subject__ == 406LL) {
                __match_result__ = strdup("Not Acceptable");
            } else if (__match_subject__ == 408LL) {
                __match_result__ = strdup("Request Timeout");
            } else if (__match_subject__ == 409LL) {
                __match_result__ = strdup("Conflict");
            } else if (__match_subject__ == 410LL) {
                __match_result__ = strdup("Gone");
            } else if (__match_subject__ == 411LL) {
                __match_result__ = strdup("Length Required");
            } else if (__match_subject__ == 413LL) {
                __match_result__ = strdup("Payload Too Large");
            } else if (__match_subject__ == 414LL) {
                __match_result__ = strdup("URI Too Long");
            } else if (__match_subject__ == 415LL) {
                __match_result__ = strdup("Unsupported Media Type");
            } else if (__match_subject__ == 422LL) {
                __match_result__ = strdup("Unprocessable Entity");
            } else if (__match_subject__ == 429LL) {
                __match_result__ = strdup("Too Many Requests");
            } else if (__match_subject__ == 500LL) {
                __match_result__ = strdup("Internal Server Error");
            } else if (__match_subject__ == 501LL) {
                __match_result__ = strdup("Not Implemented");
            } else if (__match_subject__ == 502LL) {
                __match_result__ = strdup("Bad Gateway");
            } else if (__match_subject__ == 503LL) {
                __match_result__ = strdup("Service Unavailable");
            } else if (__match_subject__ == 504LL) {
                __match_result__ = strdup("Gateway Timeout");
            } else if (__match_subject__ == 505LL) {
                __match_result__ = strdup("HTTP Version Not Supported");
            } else {
                __match_result__ = strdup("Unknown");
            }
            __match_result__;
        });

    {
        char * __ret__ = __sn__result;
        __sn__result = NULL;
        return __ret__;
    }}

bool __sn__HttpStatus_isInformational(long long __sn__code) {

    return ((__sn__code >= 100LL) && sn_lt_long(__sn__code, 200LL));}

bool __sn__HttpStatus_isSuccess(long long __sn__code) {

    return ((__sn__code >= 200LL) && sn_lt_long(__sn__code, 300LL));}

bool __sn__HttpStatus_isRedirect(long long __sn__code) {

    return ((__sn__code >= 300LL) && sn_lt_long(__sn__code, 400LL));}

bool __sn__HttpStatus_isClientError(long long __sn__code) {

    return ((__sn__code >= 400LL) && sn_lt_long(__sn__code, 500LL));}

bool __sn__HttpStatus_isServerError(long long __sn__code) {

    return ((__sn__code >= 500LL) && sn_lt_long(__sn__code, 600LL));}

bool __sn__HttpStatus_isError(long long __sn__code) {

    return (__sn__code >= 400LL);}



__sn__HttpResponse __sn__HttpResponse_new(long long __sn__code) {

    __sn__HttpResponse __sn__res = (__sn__HttpResponse){ .__sn__statusCode = __sn__code, .__sn__statusText = __sn__HttpStatus_text(__sn__code), .__sn__version = strdup("HTTP/1.1"), .__sn__headers = ({
            SnArray *__al__ = sn_array_new(sizeof(__sn__ResponseHeader), 0);
            __al__->elem_tag = SN_TAG_STRUCT;
    
            __al__->elem_release = __sn__ResponseHeader_cleanup_elem;
    
            __al__->elem_copy = __sn__ResponseHeader_copy_into;
            __al__;
        }), .__sn__body = strdup("") };

    {
        __sn__HttpResponse __ret__ = __sn__res;
        memset(&__sn__res, 0, sizeof(__sn__res));
        return __ret__;
    }}

__sn__HttpResponse __sn__HttpResponse_ok() {

    return __sn__HttpResponse_new(200LL);}

__sn__HttpResponse __sn__HttpResponse_created() {

    return __sn__HttpResponse_new(201LL);}

__sn__HttpResponse __sn__HttpResponse_noContent() {

    return __sn__HttpResponse_new(204LL);}

__sn__HttpResponse __sn__HttpResponse_badRequest() {

    return __sn__HttpResponse_new(400LL);}

__sn__HttpResponse __sn__HttpResponse_unauthorized() {

    return __sn__HttpResponse_new(401LL);}

__sn__HttpResponse __sn__HttpResponse_forbidden() {

    return __sn__HttpResponse_new(403LL);}

__sn__HttpResponse __sn__HttpResponse_notFound() {

    return __sn__HttpResponse_new(404LL);}

__sn__HttpResponse __sn__HttpResponse_methodNotAllowed() {

    return __sn__HttpResponse_new(405LL);}

__sn__HttpResponse __sn__HttpResponse_internalServerError() {

    return __sn__HttpResponse_new(500LL);}

__sn__HttpResponse __sn__HttpResponse_setHeader(__sn__HttpResponse *__sn__self, char * __sn__name, char * __sn__value) {

    sn_auto_str char * __sn__lowerName = __sn___toLower(&__sn__name);

    sn_auto_arr SnArray * __sn__newHeaders = ({
            SnArray *__al__ = sn_array_new(sizeof(__sn__ResponseHeader), 0);
            __al__->elem_tag = SN_TAG_STRUCT;
    
            __al__->elem_release = __sn__ResponseHeader_cleanup_elem;
    
            __al__->elem_copy = __sn__ResponseHeader_copy_into;
            __al__;
        });

    {
        SnArray *__arr_0__ = __sn__self->__sn__headers;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__ResponseHeader __sn__h = ((__sn__ResponseHeader *)__arr_0__->data)[__idx_0__];
            {
                if (({char *__sct0__=__sn___toLower(&__sn__h.__sn__name);bool __scr__=(strcmp(__sct0__,__sn__lowerName)!=0);free(__sct0__);__scr__;})) {
                    __sn__arr_push(&__sn__newHeaders, (__sn__ResponseHeader){ .__sn__name = strdup(__sn__h.__sn__name), .__sn__value = strdup(__sn__h.__sn__value) });
                    
                }
            }
        }
    }

    __sn__arr_push(&__sn__newHeaders, (__sn__ResponseHeader){ .__sn__name = strdup(__sn__name), .__sn__value = strdup(__sn__value) });
    

    ({
        sn_cleanup_array(&__sn__self->__sn__headers);
        __sn__self->__sn__headers = sn_array_copy(__sn__newHeaders);
        __sn__self->__sn__headers;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_addHeader(__sn__HttpResponse *__sn__self, char * __sn__name, char * __sn__value) {

    __sn__arr_push(&__sn__self->__sn__headers, (__sn__ResponseHeader){ .__sn__name = strdup(__sn__name), .__sn__value = strdup(__sn__value) });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_setBody(__sn__HttpResponse *__sn__self, char * __sn__content) {

    ({
        free(__sn__self->__sn__body);
        __sn__self->__sn__body = strdup(__sn__content);
        __sn__self->__sn__body;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_html(__sn__HttpResponse *__sn__self, char * __sn__content) {

    { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(__sn__self, "Content-Type", "text/html; charset=utf-8"); __sn__HttpResponse_cleanup(&__discard__); }
    

    ({
        free(__sn__self->__sn__body);
        __sn__self->__sn__body = strdup(__sn__content);
        __sn__self->__sn__body;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_text(__sn__HttpResponse *__sn__self, char * __sn__content) {

    { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(__sn__self, "Content-Type", "text/plain; charset=utf-8"); __sn__HttpResponse_cleanup(&__discard__); }
    

    ({
        free(__sn__self->__sn__body);
        __sn__self->__sn__body = strdup(__sn__content);
        __sn__self->__sn__body;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_json(__sn__HttpResponse *__sn__self, char * __sn__content) {

    { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(__sn__self, "Content-Type", "application/json; charset=utf-8"); __sn__HttpResponse_cleanup(&__discard__); }
    

    ({
        free(__sn__self->__sn__body);
        __sn__self->__sn__body = strdup(__sn__content);
        __sn__self->__sn__body;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_jsonData(__sn__HttpResponse *__sn__self, __sn__Json * __sn__data) {

    { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(__sn__self, "Content-Type", "application/json; charset=utf-8"); __sn__HttpResponse_cleanup(&__discard__); }
    

    ({
        free(__sn__self->__sn__body);
        __sn__self->__sn__body = __sn__Json_toString(__sn__data);
        __sn__self->__sn__body;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_jsonPretty(__sn__HttpResponse *__sn__self, __sn__Json * __sn__data) {

    { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(__sn__self, "Content-Type", "application/json; charset=utf-8"); __sn__HttpResponse_cleanup(&__discard__); }
    

    ({
        free(__sn__self->__sn__body);
        __sn__self->__sn__body = __sn__Json_toPrettyString(__sn__data);
        __sn__self->__sn__body;
    });
    

    return __sn__HttpResponse_copy(__sn__self);}

__sn__HttpResponse __sn__HttpResponse_redirect(char * __sn__location) {

    __sn__HttpResponse __sn__res = __sn__HttpResponse_new(302LL);

    { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(&__sn__res, "Location", __sn__location); __sn__HttpResponse_cleanup(&__discard__); }
    

    {
        __sn__HttpResponse __ret__ = __sn__res;
        memset(&__sn__res, 0, sizeof(__sn__res));
        return __ret__;
    }}

char * __sn__HttpResponse_getHeader(__sn__HttpResponse *__sn__self, char * __sn__name) {

    sn_auto_str char * __sn__lowerName = __sn___toLower(&__sn__name);

    {
        SnArray *__arr_0__ = __sn__self->__sn__headers;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__ResponseHeader __sn__h = ((__sn__ResponseHeader *)__arr_0__->data)[__idx_0__];
            {
                if (({char *__sct0__=__sn___toLower(&__sn__h.__sn__name);bool __scr__=(strcmp(__sct0__,__sn__lowerName)==0);free(__sct0__);__scr__;})) {
                    return strdup(__sn__h.__sn__value);}
            }
        }
    }

    return strdup("");}

bool __sn__HttpResponse_hasHeader(__sn__HttpResponse *__sn__self, char * __sn__name) {

    sn_auto_str char * __sn__lowerName = __sn___toLower(&__sn__name);

    {
        SnArray *__arr_0__ = __sn__self->__sn__headers;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__ResponseHeader __sn__h = ((__sn__ResponseHeader *)__arr_0__->data)[__idx_0__];
            {
                if (({char *__sct0__=__sn___toLower(&__sn__h.__sn__name);bool __scr__=(strcmp(__sct0__,__sn__lowerName)==0);free(__sct0__);__scr__;})) {
                    return true;}
            }
        }
    }

    return false;}

char * __sn__HttpResponse_toString(__sn__HttpResponse *__sn__self) {

    sn_auto_str char * __sn__result = strdup("");

    ({
        char *__sn_tmp__ = ({
            char __is_buf__[1024];
            int __is_off__ = 0;
            __is_buf__[0] = '\0';
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__self->__sn__version);
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", " ");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%lld", (long long)(__sn__self->__sn__statusCode));
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", " ");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__self->__sn__statusText);
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "\r\n");
            strdup(__is_buf__);
        });
        free(__sn__result);
        __sn__result = __sn_tmp__;
        __sn__result;
    });
    

    if ((sn_gt_long(sn_str_length(__sn__self->__sn__body), 0LL) && (!__sn__HttpResponse_hasHeader(__sn__self, "Content-Length")))) {
        ({
            char *__sn_tmp__ = ({char *__sct__=({
                char __is_buf__[1024];
                int __is_off__ = 0;
                __is_buf__[0] = '\0';
                __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "Content-Length: ");
                __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%lld", (long long)(sn_str_length(__sn__self->__sn__body)));
                __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "\r\n");
                strdup(__is_buf__);
            });char *__scr__=sn_str_concat(__sn__result,__sct__);free(__sct__);__scr__;});
            free(__sn__result);
            __sn__result = __sn_tmp__;
            __sn__result;
        });
        
    }

    {
        SnArray *__arr_0__ = __sn__self->__sn__headers;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__ResponseHeader __sn__h = ((__sn__ResponseHeader *)__arr_0__->data)[__idx_0__];
            {
                ({
                    char *__sn_tmp__ = ({char *__sct__=({
                        char __is_buf__[1024];
                        int __is_off__ = 0;
                        __is_buf__[0] = '\0';
                        __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__h.__sn__name);
                        __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", ": ");
                        __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__h.__sn__value);
                        __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "\r\n");
                        strdup(__is_buf__);
                    });char *__scr__=sn_str_concat(__sn__result,__sct__);free(__sct__);__scr__;});
                    free(__sn__result);
                    __sn__result = __sn_tmp__;
                    __sn__result;
                });
                
            }
        }
    }

    ({
        char *__sn_tmp__ = sn_str_concat(__sn__result, "\r\n");
        free(__sn__result);
        __sn__result = __sn_tmp__;
        __sn__result;
    });
    

    ({
        char *__sn_tmp__ = sn_str_concat(__sn__result, __sn__self->__sn__body);
        free(__sn__result);
        __sn__result = __sn_tmp__;
        __sn__result;
    });
    

    {
        char * __ret__ = __sn__result;
        __sn__result = NULL;
        return __ret__;
    }}

SnArray * __sn__HttpResponse_toBytes(__sn__HttpResponse *__sn__self) {

    sn_auto_str char * __sn____chain_tmp_17 = __sn__HttpResponse_toString(__sn__self);

    return __sn___toBytes(&__sn____chain_tmp_17);}



__sn__Router __sn__Router_new() {

    return (__sn__Router){ .__sn__routes = ({
             SnArray *__al__ = sn_array_new(sizeof(__sn__Route), 0);
             __al__->elem_tag = SN_TAG_STRUCT;
     
             __al__->elem_release = __sn__Route_cleanup_elem;
     
             __al__->elem_copy = __sn__Route_copy_into;
             __al__;
         }), .__sn__notFoundHandler = ({ __Closure__ *__cl__ = malloc(sizeof(__Closure__)); __cl__->fn = (void *)__fn_wrap_0__; __cl__->size = sizeof(__Closure__); __cl__->__cleanup__ = NULL; __cl__; }), .__sn__methodNotAllowedHandler = ({ __Closure__ *__cl__ = malloc(sizeof(__Closure__)); __cl__->fn = (void *)__fn_wrap_1__; __cl__->size = sizeof(__Closure__); __cl__->__cleanup__ = NULL; __cl__; }) };}

__sn__Router __sn__Router_route(__sn__Router *__sn__self, char * __sn__method, char * __sn__path, void * __sn__handler) {

    __sn__arr_push(&__sn__self->__sn__routes, (__sn__Route){ .__sn__method = __sn___toUpper(&__sn__method), .__sn__pattern = strdup(__sn__path), .__sn__handler = __sn__handler });
    

    return __sn__Router_copy(__sn__self);}

__sn__Router __sn__Router_get(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "GET", __sn__path, __sn__handler);}

__sn__Router __sn__Router_post(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "POST", __sn__path, __sn__handler);}

__sn__Router __sn__Router_put(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "PUT", __sn__path, __sn__handler);}

__sn__Router __sn__Router_delete(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "DELETE", __sn__path, __sn__handler);}

__sn__Router __sn__Router_patch(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "PATCH", __sn__path, __sn__handler);}

__sn__Router __sn__Router_head(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "HEAD", __sn__path, __sn__handler);}

__sn__Router __sn__Router_options(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "OPTIONS", __sn__path, __sn__handler);}

__sn__Router __sn__Router_all(__sn__Router *__sn__self, char * __sn__path, void * __sn__handler) {

    return __sn__Router_route(__sn__self, "*", __sn__path, __sn__handler);}

__sn__Router __sn__Router_setNotFoundHandler(__sn__Router *__sn__self, void * __sn__handler) {

    ({
        free(__sn__self->__sn__notFoundHandler);
        __sn__self->__sn__notFoundHandler = __sn__handler;
        __sn__self->__sn__notFoundHandler;
    });
    

    return __sn__Router_copy(__sn__self);}

__sn__Router __sn__Router_setMethodNotAllowedHandler(__sn__Router *__sn__self, void * __sn__handler) {

    ({
        free(__sn__self->__sn__methodNotAllowedHandler);
        __sn__self->__sn__methodNotAllowedHandler = __sn__handler;
        __sn__self->__sn__methodNotAllowedHandler;
    });
    

    return __sn__Router_copy(__sn__self);}

__sn__HttpResponse __sn__Router_handle(__sn__Router *__sn__self, __sn__HttpRequest *__bp__req) {
    __sn__HttpRequest __sn__req = *__bp__req;

    bool __sn__pathMatches = false;

    {
        SnArray *__arr_0__ = __sn__self->__sn__routes;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__Route __sn__route = ((__sn__Route *)__arr_0__->data)[__idx_0__];
            {
                if (__sn__matchPath(__sn__route.__sn__pattern, __sn__req.__sn__path)) {
                    (__sn__pathMatches = true);
                    
                    if (((strcmp(__sn__route.__sn__method, "*") == 0) || (strcmp(__sn__route.__sn__method, __sn__req.__sn__method) == 0))) {
                        return ((__sn__HttpResponse (*)(void *, __sn__HttpRequest))((__Closure__ *)(__sn__route.__sn__handler))->fn)(__sn__route.__sn__handler, __sn__HttpRequest_copy(&(__sn__req)));}
                }
            }
        }
    }

    if (__sn__pathMatches) {
        return ((__sn__HttpResponse (*)(void *, __sn__HttpRequest))((__Closure__ *)(__sn__self->__sn__methodNotAllowedHandler))->fn)(__sn__self->__sn__methodNotAllowedHandler, __sn__HttpRequest_copy(&(__sn__req)));}

    return ((__sn__HttpResponse (*)(void *, __sn__HttpRequest))((__Closure__ *)(__sn__self->__sn__notFoundHandler))->fn)(__sn__self->__sn__notFoundHandler, __sn__HttpRequest_copy(&(__sn__req)));}

SnArray * __sn__Router_allowedMethods(__sn__Router *__sn__self, char * __sn__path) {

    sn_auto_arr SnArray * __sn__methods = ({
            SnArray *__al__ = sn_array_new(sizeof(char *), 0);
            __al__->elem_tag = SN_TAG_STRING;
    
            __al__->elem_release = (void (*)(void *))sn_cleanup_str;
    
            __al__->elem_copy = sn_copy_str;
            __al__;
        });

    {
        SnArray *__arr_0__ = __sn__self->__sn__routes;
        long long __len_0__ = __arr_0__->len;
        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__Route __sn__route = ((__sn__Route *)__arr_0__->data)[__idx_0__];
            {
                if (__sn__matchPath(__sn__route.__sn__pattern, __sn__path)) {
                    if ((strcmp(__sn__route.__sn__method, "*") == 0)) {
                        return ({
                                 SnArray *__al__ = sn_array_new(sizeof(char *), 7);
                                 __al__->elem_tag = SN_TAG_STRING;
                         
                                 __al__->elem_release = (void (*)(void *))sn_cleanup_str;
                         
                                 __al__->elem_copy = sn_copy_str;
                         
                                 sn_array_push(__al__, &(char *){ strdup("GET") });
                         
                                 sn_array_push(__al__, &(char *){ strdup("POST") });
                         
                                 sn_array_push(__al__, &(char *){ strdup("PUT") });
                         
                                 sn_array_push(__al__, &(char *){ strdup("DELETE") });
                         
                                 sn_array_push(__al__, &(char *){ strdup("PATCH") });
                         
                                 sn_array_push(__al__, &(char *){ strdup("HEAD") });
                         
                                 sn_array_push(__al__, &(char *){ strdup("OPTIONS") });
                                 __al__;
                             });}
                    bool __sn__found = false;
                    {
                        SnArray *__arr_0__ = __sn__methods;
                        long long __len_0__ = __arr_0__->len;
                        for (long long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
                            char * __sn__m = ((char * *)__arr_0__->data)[__idx_0__];
                            {
                                if ((strcmp(__sn__m, __sn__route.__sn__method) == 0)) {
                                    (__sn__found = true);
                                    
                                    break;
                                }
                            }
                        }
                    }
                    if ((!__sn__found)) {
                        __sn__arr_push(&__sn__methods, strdup(__sn__route.__sn__method));
                        
                    }
                }
            }
        }
    }

    {
        SnArray * __ret__ = __sn__methods;
        __sn__methods = NULL;
        return __ret__;
    }}



__sn__HttpServer __sn__HttpServer_new(__sn__Router *__bp__router) {
    __sn__Router __sn__router = *__bp__router;

    __sn__HttpServer __sn__server = (__sn__HttpServer){ .__sn__router = __sn__Router_copy(&(__sn__router)), .__sn__host = strdup("0.0.0.0"), .__sn__port = 8080LL, .__sn__maxRequestSize = 1048576LL, .__sn__running = false };

    {
        __sn__HttpServer __ret__ = __sn__server;
        memset(&__sn__server, 0, sizeof(__sn__server));
        return __ret__;
    }}

__sn__HttpServer __sn__HttpServer_onPort(__sn__Router *__bp__router, long long __sn__port) {
    __sn__Router __sn__router = *__bp__router;

    __sn__HttpServer __sn__server = __sn__HttpServer_new(&__sn__router);

    (__sn__server.__sn__port = __sn__port);
    

    {
        __sn__HttpServer __ret__ = __sn__server;
        memset(&__sn__server, 0, sizeof(__sn__server));
        return __ret__;
    }}

__sn__ServerStats __sn__HttpServer_stats() {

    __sn__ServerStats __sn__stats = (__sn__ServerStats){ .__sn__totalRequests = __sn__totalRequests, .__sn__activeConnections = __sn__activeConnections, .__sn__totalErrors = __sn__totalErrors };

    return __sn__stats;}

void __sn__HttpServer_serve(long long __sn__port, void * __sn__handler) {

    sn_auto_Router __sn__Router __sn__router = __sn__Router_new();

    { __sn__Router __discard__ = __sn__Router_all(&__sn__router, "/**", __sn__handler); __sn__Router_cleanup(&__discard__); }
    

    __sn__HttpServer __sn__server = __sn__HttpServer_new(&__sn__router);

    __sn__HttpServer_listen(&__sn__server, __sn__port);
    
}

void __sn__HttpServer_serveRouter(long long __sn__port, __sn__Router *__bp__router) {
    __sn__Router __sn__router = *__bp__router;

    __sn__HttpServer __sn__server = __sn__HttpServer_new(&__sn__router);

    __sn__HttpServer_listen(&__sn__server, __sn__port);
    
}

__sn__HttpServer __sn__HttpServer_setHost(__sn__HttpServer *__sn__self, char * __sn__host) {

    ({
        free(__sn__self->__sn__host);
        __sn__self->__sn__host = strdup(__sn__host);
        __sn__self->__sn__host;
    });
    

    return __sn__HttpServer_copy(__sn__self);}

__sn__HttpServer __sn__HttpServer_setPort(__sn__HttpServer *__sn__self, long long __sn__port) {

    (__sn__self->__sn__port = __sn__port);
    

    return __sn__HttpServer_copy(__sn__self);}

__sn__HttpServer __sn__HttpServer_setMaxRequestSize(__sn__HttpServer *__sn__self, long long __sn__size) {

    (__sn__self->__sn__maxRequestSize = __sn__size);
    

    return __sn__HttpServer_copy(__sn__self);}

void __sn__HttpServer_listen(__sn__HttpServer *__sn__self, long long __sn__port) {

    (__sn__self->__sn__port = __sn__port);
    

    (__sn__self->__sn__running = true);
    

    sn_auto_str char * __sn__address = ({
            char __is_buf__[1024];
            int __is_off__ = 0;
            __is_buf__[0] = '\0';
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__self->__sn__host);
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", ":");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%lld", (long long)(__sn__self->__sn__port));
            strdup(__is_buf__);
        });

    sn_auto_TcpListener __sn__TcpListener * __sn__listener = __sn__TcpListener_bind(__sn__address);

    { sn_auto_str char *__ps__ = ({
            char __is_buf__[1024];
            int __is_off__ = 0;
            __is_buf__[0] = '\0';
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "HTTP server listening on http://");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", __sn__self->__sn__host);
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", ":");
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%lld", (long long)(sn_tcp_listener_get_port(__sn__listener)));
            __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "\n");
            strdup(__is_buf__);
        }); sn_print(__ps__); };
    

    while (__sn__self->__sn__running) {
        sn_auto_TcpStream __sn__TcpStream * __sn__client = __sn__TcpListener_accept(__sn__listener);
        __sn__activeConnections++;
        
        { SnThread *__ff__ = ({
            SnThread *__th__ = sn_thread_create();
            __ThreadArgs_0__ *__args__ = malloc(sizeof(__ThreadArgs_0__));
            __args__->self_arg = __sn__self;
            __args__->arg0 = __sn__client;
            __sn__client = NULL;
            __th__->result = __args__;
            __th__->result_size = sizeof(void);
            pthread_create(&__th__->thread, NULL, __thread_wrapper_0__, __th__);
            __th__;
        }); pthread_detach(__ff__->thread); }
        
    }

    __sn__TcpListener_dispose(__sn__listener);
    
}

void __sn__HttpServer_start(__sn__HttpServer *__sn__self) {

    __sn__HttpServer_listen(__sn__self, __sn__self->__sn__port);
    
}

void __sn__HttpServer_stop(__sn__HttpServer *__sn__self) {

    (__sn__self->__sn__running = false);
    
}

void __sn__HttpServer_handleClient(__sn__HttpServer *__sn__self, __sn__TcpStream * __sn__client) {

    sn_tcp_stream_set_timeout(__sn__client, 5000LL);
    

    bool __sn__keepAlive = true;

    while (__sn__keepAlive) {
        sn_auto_str char * __sn__requestData = __sn__HttpServer_readRequest(__sn__self, __sn__client);
        if ((sn_str_length(__sn__requestData) == 0LL)) {
            break;
        }
        sn_auto_HttpRequest __sn__HttpRequest __sn__request = __sn__HttpRequest_parse(__sn__requestData);
        __sn__totalRequests++;
        
        sn_auto_HttpResponse __sn__HttpResponse __sn__response = __sn__Router_handle(&__sn__self->__sn__router, &__sn__request);
        sn_auto_str char * __sn____chain_tmp_18 = __sn__HttpRequest_getHeader(&__sn__request, "Connection");
        sn_auto_str char * __sn__connHeader = __sn___toLower(&__sn____chain_tmp_18);
        if ((strcmp(__sn__connHeader, "close") == 0)) {
            (__sn__keepAlive = false);
            
        } else {
            if (((strcmp(__sn__request.__sn__version, "HTTP/1.0") == 0) && (strcmp(__sn__connHeader, "keep-alive") != 0))) {
                (__sn__keepAlive = false);
                
            }
        }
        if (__sn__keepAlive) {
            { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(&__sn__response, "Connection", "keep-alive"); __sn__HttpResponse_cleanup(&__discard__); }
            
        } else {
            { __sn__HttpResponse __discard__ = __sn__HttpResponse_setHeader(&__sn__response, "Connection", "close"); __sn__HttpResponse_cleanup(&__discard__); }
            
        }
        sn_auto_arr SnArray * __sn__responseBytes = __sn__HttpResponse_toBytes(&__sn__response);
        sn_tcp_stream_write(__sn__client, __sn__responseBytes);
        
    }

    __sn__TcpStream_dispose(__sn__client);
    

    __sn__activeConnections--;
    
}

char * __sn__HttpServer_readRequest(__sn__HttpServer *__sn__self, __sn__TcpStream * __sn__client) {

    sn_auto_str char * __sn__buffer = strdup("");

    bool __sn__headersComplete = false;

    long long __sn__contentLength = 0LL;

    long long __sn__bodyBytesRead = 0LL;

    while ((!__sn__headersComplete)) {
        sn_auto_arr SnArray * __sn__chunk = __sn__TcpStream_read(__sn__client, 4096LL);
        if ((sn_array_length(__sn__chunk) == 0LL)) {
            break;
        }
        ({
            char *__sn_tmp__ = ({char *__sct__=__sn__arr_toString(&__sn__chunk);char *__scr__=sn_str_concat(__sn__buffer,__sct__);free(__sct__);__scr__;});
            free(__sn__buffer);
            __sn__buffer = __sn_tmp__;
            __sn__buffer;
        });
        
        if (__sn___contains(&__sn__buffer, "\r\n\r\n")) {
            (__sn__headersComplete = true);
            
            (__sn__contentLength = __sn__parseContentLength(__sn__buffer));
            
            long long __sn__headerEnd = sn_add_long(__sn___indexOf(&__sn__buffer, "\r\n\r\n"), 4LL);
            (__sn__bodyBytesRead = sn_sub_long(sn_str_length(__sn__buffer), __sn__headerEnd));
            
        }
        if (sn_gt_long(sn_str_length(__sn__buffer), __sn__self->__sn__maxRequestSize)) {
            __sn__totalErrors++;
            
            return strdup("");}
    }

    if (sn_gt_long(__sn__contentLength, 0LL)) {
        while (sn_lt_long(__sn__bodyBytesRead, __sn__contentLength)) {
            long long __sn__remaining = sn_sub_long(__sn__contentLength, __sn__bodyBytesRead);
            long long __sn__toRead = 4096LL;
            if (sn_lt_long(__sn__remaining, __sn__toRead)) {
                (__sn__toRead = __sn__remaining);
                
            }
            sn_auto_arr SnArray * __sn__chunk = __sn__TcpStream_read(__sn__client, __sn__toRead);
            if ((sn_array_length(__sn__chunk) == 0LL)) {
                break;
            }
            ({
                char *__sn_tmp__ = ({char *__sct__=__sn__arr_toString(&__sn__chunk);char *__scr__=sn_str_concat(__sn__buffer,__sct__);free(__sct__);__scr__;});
                free(__sn__buffer);
                __sn__buffer = __sn_tmp__;
                __sn__buffer;
            });
            
            (__sn__bodyBytesRead = sn_add_long(__sn__bodyBytesRead, sn_array_length(__sn__chunk)));
            
            if (sn_gt_long(sn_str_length(__sn__buffer), __sn__self->__sn__maxRequestSize)) {
                __sn__totalErrors++;
                
                return strdup("");}
        }
    }

    {
        char * __ret__ = __sn__buffer;
        __sn__buffer = NULL;
        return __ret__;
    }}


__sn__Encoder * __sn__FastJson_encoder() {

    return sn_fast_json_encoder();}

__sn__Decoder * __sn__FastJson_decoder(char * __sn__input) {

    return sn_fast_json_decoder(__sn__input);}


int main() {
    ({
        SnArray *__sn_tmp__ = ({
            SnArray *__al__ = sn_array_new(sizeof(long long), 0);
    
            __al__;
        });
        sn_cleanup_array(&__sn__items);
        __sn__items = __sn_tmp__;
        __sn__items;
    });
    
    long long __sn__i = 1LL;
    while ((__sn__i <= __sn__maxItems)) {
        __sn__arr_push(&__sn__items, (__sn__Item){ .__sn__id = __sn__i, .__sn__name = ({
                char __is_buf__[1024];
                int __is_off__ = 0;
                __is_buf__[0] = '\0';
                __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%s", "Item ");
                __is_off__ += snprintf(__is_buf__ + __is_off__, sizeof(__is_buf__) - __is_off__, "%lld", (long long)(__sn__i));
                strdup(__is_buf__);
            }), .__sn__value = __sn__i });
        
        (__sn__i = sn_add_long(__sn__i, 1LL));
        
    }
    sn_auto_Router __sn__Router __sn__router = __sn__Router_new();
    { __sn__Router __discard__ = __sn__Router_all(&__sn__router, "/items", ({ __Closure__ *__cl__ = malloc(sizeof(__Closure__)); __cl__->fn = (void *)__fn_wrap_2__; __cl__->size = sizeof(__Closure__); __cl__->__cleanup__ = NULL; __cl__; })); __sn__Router_cleanup(&__discard__); }
    
    { __sn__Router __discard__ = __sn__Router_all(&__sn__router, "/items/*", ({ __Closure__ *__cl__ = malloc(sizeof(__Closure__)); __cl__->fn = (void *)__fn_wrap_3__; __cl__->size = sizeof(__Closure__); __cl__->__cleanup__ = NULL; __cl__; })); __sn__Router_cleanup(&__discard__); }
    
    sn_auto_HttpServer __sn__HttpServer __sn__server = __sn__HttpServer_new(&__sn__router);
    __sn__HttpServer_listen(&__sn__server, 8081LL);
    
    sn_cleanup_array(&__sn__items);
    fflush(stdout);
    return 0;
}
