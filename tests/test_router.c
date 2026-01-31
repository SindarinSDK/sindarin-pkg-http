#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <setjmp.h>
#include "runtime.h"
#ifdef _WIN32
#undef min
#undef max
#endif


/* Closure type for lambdas */
typedef struct __Closure__ { void *fn; RtArena *arena; size_t size; } __Closure__;

/* Struct type definitions */
typedef struct {
    RtHandle __sn__name;
    RtHandle __sn__value;
} __sn__Header;
typedef struct {
    RtHandle __sn__method;
    RtHandle __sn__path;
    RtHandle __sn__query;
    RtHandle __sn__version;
    RtHandle __sn__headers;
    RtHandle __sn__body;
    RtHandle __sn__raw;
} __sn__HttpRequest;
typedef struct {
    RtHandle __sn__name;
    RtHandle __sn__value;
} __sn__ResponseHeader;
typedef struct {
    long long __sn__statusCode;
    RtHandle __sn__statusText;
    RtHandle __sn__version;
    RtHandle __sn__headers;
    RtHandle __sn__body;
} __sn__HttpResponse;
typedef struct {
    RtHandle __sn__method;
    RtHandle __sn__pattern;
    __Closure__ * __sn__handler;
} __sn__Route;
typedef struct {
    RtHandle __sn__routes;
    __Closure__ * __sn__notFoundHandler;
    __Closure__ * __sn__methodNotAllowedHandler;
} __sn__Router;

/* Struct method forward declarations */
__sn__HttpRequest __sn__HttpRequest_parse(RtManagedArena *__caller_arena__, RtHandle __sn__data);
RtHandle __sn__HttpRequest_getHeader(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name);
bool __sn__HttpRequest_hasHeader(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name);
RtHandle __sn__HttpRequest_queryParam(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name);
bool __sn__HttpRequest_hasQueryParam(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name);
RtHandle __sn__HttpRequest_contentType(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
long long __sn__HttpRequest_contentLength(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_hasBody(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isGet(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isPost(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isPut(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isDelete(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isPatch(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isHead(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
bool __sn__HttpRequest_isOptions(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self);
__sn__HttpResponse __sn__HttpResponse_new(RtManagedArena *__caller_arena__, long long __sn__code);
__sn__HttpResponse __sn__HttpResponse_ok(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_created(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_noContent(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_badRequest(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_unauthorized(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_forbidden(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_notFound(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_methodNotAllowed(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_internalServerError(RtManagedArena *__caller_arena__);
__sn__HttpResponse __sn__HttpResponse_setHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name, RtHandle __sn__value);
__sn__HttpResponse __sn__HttpResponse_addHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name, RtHandle __sn__value);
__sn__HttpResponse __sn__HttpResponse_setBody(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content);
__sn__HttpResponse __sn__HttpResponse_html(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content);
__sn__HttpResponse __sn__HttpResponse_text(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content);
__sn__HttpResponse __sn__HttpResponse_json(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content);
__sn__HttpResponse __sn__HttpResponse_redirect(RtManagedArena *__caller_arena__, RtHandle __sn__location);
RtHandle __sn__HttpResponse_getHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name);
bool __sn__HttpResponse_hasHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name);
RtHandle __sn__HttpResponse_toString(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self);
RtHandle __sn__HttpResponse_toBytes(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self);
__sn__Router __sn__Router_new(RtManagedArena *__caller_arena__);
__sn__Router __sn__Router_route(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__method, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_get(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_post(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_put(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_delete(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_patch(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_head(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_options(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_all(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler);
__sn__Router __sn__Router_setNotFoundHandler(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, __Closure__ * __sn__handler);
__sn__Router __sn__Router_setMethodNotAllowedHandler(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, __Closure__ * __sn__handler);
__sn__HttpResponse __sn__Router_handle(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, __sn__HttpRequest __sn__req);
RtHandle __sn__Router_allowedMethods(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path);

/* Forward declarations */
static RtManagedArena *__main_arena__ = NULL;

RtHandle __sn__statusText(RtManagedArena *, long long);
bool __sn__isInformational(RtManagedArena *, long long);
bool __sn__isSuccess(RtManagedArena *, long long);
bool __sn__isRedirect(RtManagedArena *, long long);
bool __sn__isClientError(RtManagedArena *, long long);
bool __sn__isServerError(RtManagedArena *, long long);
bool __sn__isError(RtManagedArena *, long long);
bool __sn__matchPath(RtManagedArena *, RtHandle, RtHandle);
RtHandle __sn__normalizePath(RtManagedArena *, RtHandle);
__sn__HttpResponse __sn__defaultNotFoundHandler(RtManagedArena *, __sn__HttpRequest);
__sn__HttpResponse __sn__defaultMethodNotAllowedHandler(RtManagedArena *, __sn__HttpRequest);
void __sn__check(RtManagedArena *, bool, RtHandle);
__sn__HttpResponse __sn__homeHandler(RtManagedArena *, __sn__HttpRequest);
__sn__HttpResponse __sn__userHandler(RtManagedArena *, __sn__HttpRequest);
__sn__HttpResponse __sn__apiHandler(RtManagedArena *, __sn__HttpRequest);
__sn__HttpResponse __sn__catchAllHandler(RtManagedArena *, __sn__HttpRequest);
void __sn__testRouteRegistration(RtManagedArena *);
void __sn__testBasicRouting(RtManagedArena *);
void __sn__testPathMatching(RtManagedArena *);
void __sn__testMethodMatching(RtManagedArena *);
void __sn__testWildcards(RtManagedArena *);

/* Interceptor thunk forward declarations */
static RtAny __thunk_0(void);
static RtAny __thunk_1(void);
static RtAny __thunk_2(void);
static RtAny __thunk_3(void);
static RtAny __thunk_4(void);
static RtAny __thunk_5(void);
static RtAny __thunk_6(void);
static RtAny __thunk_7(void);
static RtAny __thunk_8(void);
static RtAny __thunk_9(void);
static RtAny __thunk_10(void);
static RtAny __thunk_11(void);
static RtAny __thunk_12(void);
static RtAny __thunk_13(void);
static RtAny __thunk_14(void);
static RtAny __thunk_15(void);
static RtAny __thunk_16(void);
static RtAny __thunk_17(void);
static RtAny __thunk_18(void);
static RtAny __thunk_19(void);
static RtAny __thunk_20(void);
static RtAny __thunk_21(void);
static RtAny __thunk_22(void);
static RtAny __thunk_23(void);
static RtAny __thunk_24(void);
static RtAny __thunk_25(void);
static RtAny __thunk_26(void);
static RtAny __thunk_27(void);
static RtAny __thunk_28(void);
static RtAny __thunk_29(void);
static RtAny __thunk_30(void);
static RtAny __thunk_31(void);
static RtAny __thunk_32(void);
static RtAny __thunk_33(void);
static RtAny __thunk_34(void);
static RtAny __thunk_35(void);

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
RtHandle __sn__statusText(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    RtHandle _return_value = RT_HANDLE_NULL;
    if (rt_eq_long(__sn__code, 100LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Continue");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 101LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Switching Protocols");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 200LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "OK");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 201LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Created");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 202LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Accepted");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 204LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "No Content");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 205LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Reset Content");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 206LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Partial Content");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 301LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Moved Permanently");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 302LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Found");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 303LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "See Other");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 304LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Not Modified");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 307LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Temporary Redirect");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 308LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Permanent Redirect");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 400LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Bad Request");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 401LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Unauthorized");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 403LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Forbidden");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 404LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Not Found");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 405LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Method Not Allowed");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 406LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Not Acceptable");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 408LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Request Timeout");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 409LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Conflict");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 410LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Gone");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 411LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Length Required");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 413LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Payload Too Large");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 414LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "URI Too Long");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 415LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Unsupported Media Type");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 422LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Unprocessable Entity");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 429LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Too Many Requests");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 500LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Internal Server Error");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 501LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Not Implemented");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 502LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Bad Gateway");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 503LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Service Unavailable");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 504LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Gateway Timeout");
        goto __sn__statusText_return;
    }
    if (rt_eq_long(__sn__code, 505LL)) {
        _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "HTTP Version Not Supported");
        goto __sn__statusText_return;
    }
    _return_value = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Unknown");
    goto __sn__statusText_return;
__sn__statusText_return:
    _return_value = rt_managed_promote(__caller_arena__, __local_arena__, _return_value);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__isInformational(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    bool _return_value = 0;
    _return_value = ((rt_ge_long(__sn__code, 100LL) != 0 && rt_lt_long(__sn__code, 200LL) != 0) ? 1L : 0L);
    goto __sn__isInformational_return;
__sn__isInformational_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__isSuccess(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    bool _return_value = 0;
    _return_value = ((rt_ge_long(__sn__code, 200LL) != 0 && rt_lt_long(__sn__code, 300LL) != 0) ? 1L : 0L);
    goto __sn__isSuccess_return;
__sn__isSuccess_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__isRedirect(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    bool _return_value = 0;
    _return_value = ((rt_ge_long(__sn__code, 300LL) != 0 && rt_lt_long(__sn__code, 400LL) != 0) ? 1L : 0L);
    goto __sn__isRedirect_return;
__sn__isRedirect_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__isClientError(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    bool _return_value = 0;
    _return_value = ((rt_ge_long(__sn__code, 400LL) != 0 && rt_lt_long(__sn__code, 500LL) != 0) ? 1L : 0L);
    goto __sn__isClientError_return;
__sn__isClientError_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__isServerError(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    bool _return_value = 0;
    _return_value = ((rt_ge_long(__sn__code, 500LL) != 0 && rt_lt_long(__sn__code, 600LL) != 0) ? 1L : 0L);
    goto __sn__isServerError_return;
__sn__isServerError_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__isError(RtManagedArena *__caller_arena__, long long __sn__code) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    bool _return_value = 0;
    _return_value = rt_ge_long(__sn__code, 400LL);
    goto __sn__isError_return;
__sn__isError_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

bool __sn__matchPath(RtManagedArena *__caller_arena__, RtHandle __sn__pattern, RtHandle __sn__path) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__pattern = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__pattern);
    __sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__path);
    bool _return_value = 0;
    RtThreadHandle *__p_pending__ = NULL;
    RtHandle __sn__p = ({
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, __sn__pattern));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("normalizePath", __args, 1, __thunk_0);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
    } else {
        __intercept_result = __sn__normalizePath(__local_arena__, __sn__pattern);
    }
    __intercept_result;
});
    RtThreadHandle *__r_pending__ = NULL;
    RtHandle __sn__r = ({
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, __sn__path));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("normalizePath", __args, 1, __thunk_1);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
    } else {
        __intercept_result = __sn__normalizePath(__local_arena__, __sn__path);
    }
    __intercept_result;
});
    if (rt_eq_string((char *)rt_managed_pin(__local_arena__, __sn__p), (char *)rt_managed_pin(__local_arena__, __sn__r))) {
        {
            _return_value = 1L;
            goto __sn__matchPath_return;
        }
    }
    if (rt_str_endsWith((char *)rt_managed_pin(__local_arena__, __sn__p), "/**")) {
        {
            RtThreadHandle *__prefix_pending__ = NULL;
            RtHandle __sn__prefix = rt_str_substring_h(__local_arena__, (char *)rt_managed_pin(__local_arena__, __sn__p), 0LL, rt_sub_long(rt_str_length((char *)rt_managed_pin(__local_arena__, __sn__p)), 3LL));
            _return_value = rt_str_startsWith((char *)rt_managed_pin(__local_arena__, __sn__r), (char *)rt_managed_pin(__local_arena__, __sn__prefix));
            goto __sn__matchPath_return;
        }
    }
    if (rt_str_endsWith((char *)rt_managed_pin(__local_arena__, __sn__p), "/*")) {
        {
            RtThreadHandle *__prefix_pending__ = NULL;
            RtHandle __sn__prefix = rt_str_substring_h(__local_arena__, (char *)rt_managed_pin(__local_arena__, __sn__p), 0LL, rt_sub_long(rt_str_length((char *)rt_managed_pin(__local_arena__, __sn__p)), 2LL));
            if (rt_not_bool(rt_str_startsWith((char *)rt_managed_pin(__local_arena__, __sn__r), (char *)rt_managed_pin(__local_arena__, __sn__prefix)))) {
                {
                    _return_value = 0L;
                    goto __sn__matchPath_return;
                }
            }
            RtThreadHandle *__suffix_pending__ = NULL;
            RtHandle __sn__suffix = rt_str_substring_h(__local_arena__, (char *)rt_managed_pin(__local_arena__, __sn__r), rt_str_length((char *)rt_managed_pin(__local_arena__, __sn__prefix)), rt_str_length((char *)rt_managed_pin(__local_arena__, __sn__r)));
            if (((rt_eq_string((char *)rt_managed_pin(__local_arena__, __sn__suffix), "/") != 0 || rt_eq_string((char *)rt_managed_pin(__local_arena__, __sn__suffix), "") != 0) ? 1L : 0L)) {
                {
                    _return_value = 1L;
                    goto __sn__matchPath_return;
                }
            }
            _return_value = rt_not_bool(rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__suffix), "/"));
            goto __sn__matchPath_return;
        }
    }
    RtThreadHandle *__patternParts_pending__ = NULL;
    RtHandle __sn__patternParts = rt_str_split_h(__local_arena__, (char *)rt_managed_pin(__local_arena__, __sn__p), "/");
    RtThreadHandle *__pathParts_pending__ = NULL;
    RtHandle __sn__pathParts = rt_str_split_h(__local_arena__, (char *)rt_managed_pin(__local_arena__, __sn__r), "/");
    if (rt_ne_long(rt_array_length(((RtHandle *)rt_managed_pin_array(__local_arena__, __sn__patternParts))), rt_array_length(((RtHandle *)rt_managed_pin_array(__local_arena__, __sn__pathParts))))) {
        {
            _return_value = 0L;
            goto __sn__matchPath_return;
        }
    }
    {
        RtThreadHandle *__i_pending__ = NULL;
        long long __sn__i = 0LL;
        while (rt_lt_long(__sn__i, rt_array_length(((RtHandle *)rt_managed_pin_array(__local_arena__, __sn__patternParts))))) {
            {
                RtThreadHandle *__pp_pending__ = NULL;
                RtHandle __sn__pp = ((RtHandle *)rt_managed_pin_array(__local_arena__, __sn__patternParts))[__sn__i];
                RtThreadHandle *__rp_pending__ = NULL;
                RtHandle __sn__rp = ((RtHandle *)rt_managed_pin_array(__local_arena__, __sn__pathParts))[__sn__i];
                if (rt_eq_string((char *)rt_managed_pin(__local_arena__, __sn__pp), "*")) {
                    {
                        goto __for_continue_0__;
                    }
                }
                if (rt_ne_string((char *)rt_managed_pin(__local_arena__, __sn__pp), (char *)rt_managed_pin(__local_arena__, __sn__rp))) {
                    {
                        _return_value = 0L;
                        goto __sn__matchPath_return;
                    }
                }
            }
        __for_continue_0__:;
            rt_post_inc_long(&__sn__i);
        }
    }
    _return_value = 1L;
    goto __sn__matchPath_return;
__sn__matchPath_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

RtHandle __sn__normalizePath(RtManagedArena *__caller_arena__, RtHandle __sn__path) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__path);
    RtHandle _return_value = RT_HANDLE_NULL;
    RtThreadHandle *__p_pending__ = NULL;
    RtHandle __sn__p = __sn__path;
    if (rt_not_bool(rt_str_startsWith((char *)rt_managed_pin(__local_arena__, __sn__p), "/"))) {
        {
            (__sn__p = rt_str_concat_h(__local_arena__, RT_HANDLE_NULL, "/", (char *)rt_managed_pin(__local_arena__, __sn__p)));
        }
    }
    if (((rt_gt_long(rt_str_length((char *)rt_managed_pin(__local_arena__, __sn__p)), 1LL) != 0 && rt_str_endsWith((char *)rt_managed_pin(__local_arena__, __sn__p), "/") != 0) ? 1L : 0L)) {
        {
            (__sn__p = rt_str_substring_h(__local_arena__, (char *)rt_managed_pin(__local_arena__, __sn__p), 0LL, rt_sub_long(rt_str_length((char *)rt_managed_pin(__local_arena__, __sn__p)), 1LL)));
        }
    }
    _return_value = __sn__p;
    goto __sn__normalizePath_return;
__sn__normalizePath_return:
    _return_value = rt_managed_promote(__caller_arena__, __local_arena__, _return_value);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

__sn__HttpResponse __sn__defaultNotFoundHandler(RtManagedArena *__caller_arena__, __sn__HttpRequest __sn__req) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__req.__sn__method = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__method);
    __sn__req.__sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__path);
    __sn__req.__sn__query = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__query);
    __sn__req.__sn__version = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__version);
    __sn__req.__sn__body = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__body);
    __sn__req.__sn__raw = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__raw);
    __sn__HttpResponse _return_value = {0};
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = __sn__HttpResponse_notFound(__local_arena__);
    _return_value = __sn__HttpResponse_text(__local_arena__, &__sn__res, rt_str_concat_h(__local_arena__, RT_HANDLE_NULL, "404 Not Found: ", ((char *)rt_managed_pin(__local_arena__, __sn__req.__sn__path))));
    goto __sn__defaultNotFoundHandler_return;
__sn__defaultNotFoundHandler_return:
    _return_value.__sn__statusText = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__statusText);
    _return_value.__sn__version = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__version);
    _return_value.__sn__headers = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__headers);
    _return_value.__sn__body = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__body);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

__sn__HttpResponse __sn__defaultMethodNotAllowedHandler(RtManagedArena *__caller_arena__, __sn__HttpRequest __sn__req) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__req.__sn__method = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__method);
    __sn__req.__sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__path);
    __sn__req.__sn__query = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__query);
    __sn__req.__sn__version = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__version);
    __sn__req.__sn__body = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__body);
    __sn__req.__sn__raw = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__raw);
    __sn__HttpResponse _return_value = {0};
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = __sn__HttpResponse_methodNotAllowed(__local_arena__);
    _return_value = __sn__HttpResponse_text(__local_arena__, &__sn__res, ({
        char *_r = rt_str_concat(__local_arena__, "405 Method Not Allowed: ", ((char *)rt_managed_pin(__local_arena__, __sn__req.__sn__method)));
        _r = rt_str_concat(__local_arena__, _r, " ");
        _r = rt_str_concat(__local_arena__, _r, ((char *)rt_managed_pin(__local_arena__, __sn__req.__sn__path)));
        rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, _r);
    }));
    goto __sn__defaultMethodNotAllowedHandler_return;
__sn__defaultMethodNotAllowedHandler_return:
    _return_value.__sn__statusText = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__statusText);
    _return_value.__sn__version = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__version);
    _return_value.__sn__headers = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__headers);
    _return_value.__sn__body = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__body);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

long long __sn__testsPassed = 0LL;
long long __sn__testsFailed = 0LL;
void __sn__check(RtManagedArena *__caller_arena__, bool __sn__condition, RtHandle __sn__message) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__message = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__message);
    if (rt_not_bool(__sn__condition)) {
        {
            ({
        char *_str_arg0 = ({
        char *_r = rt_str_concat(__local_arena__, "  FAIL: ", (char *)rt_managed_pin(__local_arena__, __sn__message));
        _r = rt_str_concat(__local_arena__, _r, "\n");
        _r;
    });
        rt_print_string(_str_arg0);
    });
            rt_post_inc_long(&__sn__testsFailed);
        }
    }
    else {
        {
            rt_post_inc_long(&__sn__testsPassed);
        }
    }
    goto __sn__check_return;
__sn__check_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

__sn__HttpResponse __sn__homeHandler(RtManagedArena *__caller_arena__, __sn__HttpRequest __sn__req) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__req.__sn__method = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__method);
    __sn__req.__sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__path);
    __sn__req.__sn__query = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__query);
    __sn__req.__sn__version = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__version);
    __sn__req.__sn__body = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__body);
    __sn__req.__sn__raw = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__raw);
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse _chain_tmp_0 = __sn__HttpResponse_ok(__local_arena__);
    _return_value = __sn__HttpResponse_text(__local_arena__, &_chain_tmp_0, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Home"));
    goto __sn__homeHandler_return;
__sn__homeHandler_return:
    _return_value.__sn__statusText = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__statusText);
    _return_value.__sn__version = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__version);
    _return_value.__sn__headers = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__headers);
    _return_value.__sn__body = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__body);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

__sn__HttpResponse __sn__userHandler(RtManagedArena *__caller_arena__, __sn__HttpRequest __sn__req) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__req.__sn__method = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__method);
    __sn__req.__sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__path);
    __sn__req.__sn__query = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__query);
    __sn__req.__sn__version = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__version);
    __sn__req.__sn__body = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__body);
    __sn__req.__sn__raw = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__raw);
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse _chain_tmp_1 = __sn__HttpResponse_ok(__local_arena__);
    _return_value = __sn__HttpResponse_text(__local_arena__, &_chain_tmp_1, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "User"));
    goto __sn__userHandler_return;
__sn__userHandler_return:
    _return_value.__sn__statusText = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__statusText);
    _return_value.__sn__version = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__version);
    _return_value.__sn__headers = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__headers);
    _return_value.__sn__body = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__body);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

__sn__HttpResponse __sn__apiHandler(RtManagedArena *__caller_arena__, __sn__HttpRequest __sn__req) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__req.__sn__method = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__method);
    __sn__req.__sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__path);
    __sn__req.__sn__query = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__query);
    __sn__req.__sn__version = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__version);
    __sn__req.__sn__body = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__body);
    __sn__req.__sn__raw = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__raw);
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse _chain_tmp_2 = __sn__HttpResponse_ok(__local_arena__);
    _return_value = __sn__HttpResponse_json(__local_arena__, &_chain_tmp_2, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "{\"api\": true}"));
    goto __sn__apiHandler_return;
__sn__apiHandler_return:
    _return_value.__sn__statusText = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__statusText);
    _return_value.__sn__version = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__version);
    _return_value.__sn__headers = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__headers);
    _return_value.__sn__body = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__body);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

__sn__HttpResponse __sn__catchAllHandler(RtManagedArena *__caller_arena__, __sn__HttpRequest __sn__req) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__req.__sn__method = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__method);
    __sn__req.__sn__path = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__path);
    __sn__req.__sn__query = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__query);
    __sn__req.__sn__version = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__version);
    __sn__req.__sn__body = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__body);
    __sn__req.__sn__raw = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__req.__sn__raw);
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse _chain_tmp_3 = __sn__HttpResponse_ok(__local_arena__);
    _return_value = __sn__HttpResponse_text(__local_arena__, &_chain_tmp_3, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Catch All"));
    goto __sn__catchAllHandler_return;
__sn__catchAllHandler_return:
    _return_value.__sn__statusText = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__statusText);
    _return_value.__sn__version = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__version);
    _return_value.__sn__headers = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__headers);
    _return_value.__sn__body = rt_managed_promote(__caller_arena__, __local_arena__, _return_value.__sn__body);
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

int main() {
    RtManagedArena *__local_arena__ = rt_managed_arena_create();
    __main_arena__ = __local_arena__;
    int _return_value = 0;
    rt_print_string("Testing HTTP Router\n");
    rt_print_string("===================\n\n");
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testRouteRegistration", __args, 0, __thunk_2);
    } else {
        __sn__testRouteRegistration(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testBasicRouting", __args, 0, __thunk_3);
    } else {
        __sn__testBasicRouting(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testPathMatching", __args, 0, __thunk_4);
    } else {
        __sn__testPathMatching(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testMethodMatching", __args, 0, __thunk_5);
    } else {
        __sn__testMethodMatching(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testWildcards", __args, 0, __thunk_6);
    } else {
        __sn__testWildcards(__local_arena__);
    }
    (void)0;
});
    ({
        char *_str_arg0 = ({
        char *_p0 = rt_to_string_long(__local_arena__, __sn__testsPassed);
        char *_p1 = rt_to_string_long(__local_arena__, __sn__testsFailed);
        char *_r = rt_str_concat(__local_arena__, "\nTests passed: ", _p0);
        _r = rt_str_concat(__local_arena__, _r, ", failed: ");
        _r = rt_str_concat(__local_arena__, _r, _p1);
        _r = rt_str_concat(__local_arena__, _r, "\n");
        _r;
    });
        rt_print_string(_str_arg0);
    });
    if (rt_eq_long(__sn__testsFailed, 0LL)) {
        {
            rt_print_string("All router tests passed!\n");
        }
    }
    else {
        {
            rt_print_string("Some tests failed!\n");
        }
    }
    goto main_return;
main_return:
    rt_managed_arena_destroy(__local_arena__);
    return _return_value;
}

void __sn__testRouteRegistration(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing route registration...\n");
    RtThreadHandle *__router_pending__ = NULL;
    __sn__Router __sn__router = __sn__Router_new(__local_arena__);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/"), __sn__homeHandler);
    __sn__Router_post(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), __sn__userHandler);
    __sn__Router_put(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), __sn__userHandler);
    __sn__Router_delete(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), __sn__userHandler);
    __sn__Router_patch(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), __sn__userHandler);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(rt_array_length(((__sn__Route *)rt_managed_pin_array(__local_arena__, __sn__router.__sn__routes))), 5LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Should have 5 routes registered")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_7);
    } else {
        __sn__check(__local_arena__, rt_eq_long(rt_array_length(((__sn__Route *)rt_managed_pin_array(__local_arena__, __sn__router.__sn__routes))), 5LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Should have 5 routes registered"));
    }
    (void)0;
});
    rt_print_string("  Route registration OK\n");
    goto __sn__testRouteRegistration_return;
__sn__testRouteRegistration_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testBasicRouting(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing basic routing...\n");
    RtThreadHandle *__router_pending__ = NULL;
    __sn__Router __sn__router = __sn__Router_new(__local_arena__);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/"), __sn__homeHandler);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), __sn__userHandler);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/api"), __sn__apiHandler);
    RtThreadHandle *__homeReq_pending__ = NULL;
    __sn__HttpRequest __sn__homeReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET / HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__homeRes_pending__ = NULL;
    __sn__HttpResponse __sn__homeRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__homeReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__homeRes.__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Home route should return 200")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_8);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__homeRes.__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Home route should return 200"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__homeRes.__sn__body)), "Home"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Home route should return 'Home'")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_9);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__homeRes.__sn__body)), "Home"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Home route should return 'Home'"));
    }
    (void)0;
});
    RtThreadHandle *__userReq_pending__ = NULL;
    __sn__HttpRequest __sn__userReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET /users HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__userRes_pending__ = NULL;
    __sn__HttpResponse __sn__userRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__userReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__userRes.__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "User route should return 200")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_10);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__userRes.__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "User route should return 200"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__userRes.__sn__body)), "User"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "User route should return 'User'")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_11);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__userRes.__sn__body)), "User"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "User route should return 'User'"));
    }
    (void)0;
});
    RtThreadHandle *__apiReq_pending__ = NULL;
    __sn__HttpRequest __sn__apiReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET /api HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__apiRes_pending__ = NULL;
    __sn__HttpResponse __sn__apiRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__apiReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__apiRes.__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "API route should return 200")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_12);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__apiRes.__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "API route should return 200"));
    }
    (void)0;
});
    rt_print_string("  Basic routing OK\n");
    goto __sn__testBasicRouting_return;
__sn__testBasicRouting_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testPathMatching(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing path matching...\n");
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_13);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"));
    }
    __intercept_result;
})) == (1L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Exact match should work")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_14);
    } else {
        __sn__check(__local_arena__, ((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_13);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"));
    }
    __intercept_result;
})) == (1L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Exact match should work"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_15);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/"));
    }
    __intercept_result;
})) == (1L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Trailing slash should match")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_16);
    } else {
        __sn__check(__local_arena__, ((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_15);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/"));
    }
    __intercept_result;
})) == (1L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Trailing slash should match"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_17);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"));
    }
    __intercept_result;
})) == (1L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Pattern trailing slash should match")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_18);
    } else {
        __sn__check(__local_arena__, ((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_17);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"));
    }
    __intercept_result;
})) == (1L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Pattern trailing slash should match"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/posts")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_19);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/posts"));
    }
    __intercept_result;
})) == (0L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Different paths should not match")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_20);
    } else {
        __sn__check(__local_arena__, ((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/posts")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_19);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/posts"));
    }
    __intercept_result;
})) == (0L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Different paths should not match"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/123")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_21);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/123"));
    }
    __intercept_result;
})) == (0L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Longer path should not match exact")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_22);
    } else {
        __sn__check(__local_arena__, ((({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users")));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/123")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_21);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/123"));
    }
    __intercept_result;
})) == (0L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Longer path should not match exact"));
    }
    (void)0;
});
    rt_print_string("  Path matching OK\n");
    goto __sn__testPathMatching_return;
__sn__testPathMatching_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testMethodMatching(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing method matching...\n");
    RtThreadHandle *__router_pending__ = NULL;
    __sn__Router __sn__router = __sn__Router_new(__local_arena__);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/resource"), __sn__homeHandler);
    __sn__Router_post(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/resource"), __sn__userHandler);
    RtThreadHandle *__getReq_pending__ = NULL;
    __sn__HttpRequest __sn__getReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET /resource HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__getRes_pending__ = NULL;
    __sn__HttpResponse __sn__getRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__getReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__getRes.__sn__body)), "Home"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET should route to homeHandler")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_23);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__getRes.__sn__body)), "Home"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET should route to homeHandler"));
    }
    (void)0;
});
    RtThreadHandle *__postReq_pending__ = NULL;
    __sn__HttpRequest __sn__postReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "POST /resource HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__postRes_pending__ = NULL;
    __sn__HttpResponse __sn__postRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__postReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__postRes.__sn__body)), "User"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "POST should route to userHandler")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_24);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__postRes.__sn__body)), "User"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "POST should route to userHandler"));
    }
    (void)0;
});
    RtThreadHandle *__putReq_pending__ = NULL;
    __sn__HttpRequest __sn__putReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "PUT /resource HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__putRes_pending__ = NULL;
    __sn__HttpResponse __sn__putRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__putReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__putRes.__sn__statusCode, 405LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "PUT should return 405 Method Not Allowed")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_25);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__putRes.__sn__statusCode, 405LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "PUT should return 405 Method Not Allowed"));
    }
    (void)0;
});
    rt_print_string("  Method matching OK\n");
    goto __sn__testMethodMatching_return;
__sn__testMethodMatching_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testWildcards(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing wildcard routes...\n");
    RtThreadHandle *__router_pending__ = NULL;
    __sn__Router __sn__router = __sn__Router_new(__local_arena__);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/users/*"), __sn__userHandler);
    __sn__Router_get(__local_arena__, &__sn__router, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "/api/**"), __sn__apiHandler);
    RtThreadHandle *__singleReq_pending__ = NULL;
    __sn__HttpRequest __sn__singleReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET /users/123 HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__singleRes_pending__ = NULL;
    __sn__HttpResponse __sn__singleRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__singleReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__singleRes.__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Single wildcard should match /users/123")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_26);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__singleRes.__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Single wildcard should match /users/123"));
    }
    (void)0;
});
    RtThreadHandle *__doubleReq_pending__ = NULL;
    __sn__HttpRequest __sn__doubleReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET /api/v1/users/123 HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__doubleRes_pending__ = NULL;
    __sn__HttpResponse __sn__doubleRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__doubleReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__doubleRes.__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Double wildcard should match deep paths")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_27);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__doubleRes.__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Double wildcard should match deep paths"));
    }
    (void)0;
});
    RtThreadHandle *__notFoundReq_pending__ = NULL;
    __sn__HttpRequest __sn__notFoundReq = __sn__HttpRequest_parse(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "GET /unknown HTTP/1.1\r\n\r\n"));
    RtThreadHandle *__notFoundRes_pending__ = NULL;
    __sn__HttpResponse __sn__notFoundRes = __sn__Router_handle(__local_arena__, &__sn__router, __sn__notFoundReq);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__notFoundRes.__sn__statusCode, 404LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Unknown path should return 404")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_28);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__notFoundRes.__sn__statusCode, 404LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Unknown path should return 404"));
    }
    (void)0;
});
    rt_print_string("  Wildcard routes OK\n");
    goto __sn__testWildcards_return;
__sn__testWildcards_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

__sn__HttpRequest __sn__HttpRequest_parse(RtManagedArena *__caller_arena__, RtHandle __sn__data) {
    __sn__HttpRequest _return_value = {0};
    RtThreadHandle *__req_pending__ = NULL;
    __sn__HttpRequest __sn__req = (__sn__HttpRequest){ .__sn__method = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, ""), .__sn__path = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, ""), .__sn__query = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, ""), .__sn__version = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, ""), .__sn__headers = RT_HANDLE_NULL, .__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, ""), .__sn__raw = __sn__data };
    RtThreadHandle *__normalized_pending__ = NULL;
    RtHandle __sn__normalized = rt_str_replace_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__data), "\r\n", "\n");
    RtThreadHandle *__lines_pending__ = NULL;
    RtHandle __sn__lines = rt_str_split_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__normalized), "\n");
    if (rt_eq_long(rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines))), 0LL)) {
        {
            _return_value = __sn__req;
            goto __sn__HttpRequest_parse_return;
        }
    }
    RtThreadHandle *__requestLine_pending__ = NULL;
    RtHandle __sn__requestLine = ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines))[0LL];
    RtThreadHandle *__parts_pending__ = NULL;
    RtHandle __sn__parts = rt_str_split_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__requestLine), " ");
    if (rt_ge_long(rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__parts))), 1LL)) {
        {
            __sn__req.__sn__method = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__parts))[0LL]));
        }
    }
    if (rt_ge_long(rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__parts))), 2LL)) {
        {
            RtThreadHandle *__fullPath_pending__ = NULL;
            RtHandle __sn__fullPath = ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__parts))[1LL];
            RtThreadHandle *__qIndex_pending__ = NULL;
            long long __sn__qIndex = rt_str_indexOf((char *)rt_managed_pin(__caller_arena__, __sn__fullPath), "?");
            if (rt_ge_long(__sn__qIndex, 0LL)) {
                {
                    __sn__req.__sn__path = rt_str_substring_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__fullPath), 0LL, __sn__qIndex);
                    __sn__req.__sn__query = rt_str_substring_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__fullPath), rt_add_long(__sn__qIndex, 1LL), rt_str_length((char *)rt_managed_pin(__caller_arena__, __sn__fullPath)));
                }
            }
            else {
                {
                    __sn__req.__sn__path = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__fullPath));
                }
            }
        }
    }
    if (rt_ge_long(rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__parts))), 3LL)) {
        {
            __sn__req.__sn__version = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__parts))[2LL]));
        }
    }
    RtThreadHandle *__headersDone_pending__ = NULL;
    bool __sn__headersDone = 0L;
    RtThreadHandle *__bodyStartIndex_pending__ = NULL;
    long long __sn__bodyStartIndex = 1LL;
    {
        RtThreadHandle *__i_pending__ = NULL;
        long long __sn__i = 1LL;
        while (rt_lt_long(__sn__i, rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines))))) {
            {
                RtThreadHandle *__line_pending__ = NULL;
                RtHandle __sn__line = ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines))[__sn__i];
                if (rt_eq_string(rt_str_trim(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__line)), "")) {
                    {
                        (__sn__headersDone = 1L);
                        (__sn__bodyStartIndex = rt_add_long(__sn__i, 1LL));
                        break;
                    }
                }
                RtThreadHandle *__colonIndex_pending__ = NULL;
                long long __sn__colonIndex = rt_str_indexOf((char *)rt_managed_pin(__caller_arena__, __sn__line), ":");
                if (rt_gt_long(__sn__colonIndex, 0LL)) {
                    {
                        RtThreadHandle *__name_pending__ = NULL;
                        RtHandle __sn__name = rt_str_trim_h(__caller_arena__, rt_str_substring(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__line), 0LL, __sn__colonIndex));
                        RtThreadHandle *__value_pending__ = NULL;
                        RtHandle __sn__value = rt_str_trim_h(__caller_arena__, rt_str_substring(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__line), rt_add_long(__sn__colonIndex, 1LL), rt_str_length((char *)rt_managed_pin(__caller_arena__, __sn__line))));
                        (__sn__req.__sn__headers = rt_array_push_struct_h(__caller_arena__, __sn__req.__sn__headers, &(__sn__Header){ .__sn__name = __sn__name, .__sn__value = __sn__value }, sizeof(__sn__Header)));
                    }
                }
            }
        __for_continue_1__:;
            rt_post_inc_long(&__sn__i);
        }
    }
    if (((__sn__headersDone != 0 && rt_lt_long(__sn__bodyStartIndex, rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines)))) != 0) ? 1L : 0L)) {
        {
            RtThreadHandle *__bodyLines_pending__ = NULL;
            RtHandle __sn__bodyLines = rt_array_create_string_h(__caller_arena__, 0, (char *[]){});
            {
                RtThreadHandle *__i_pending__ = NULL;
                long long __sn__i = __sn__bodyStartIndex;
                while (rt_lt_long(__sn__i, rt_array_length(((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines))))) {
                    {
                        (__sn__bodyLines = rt_array_push_string_h(__caller_arena__, __sn__bodyLines, ((char *)rt_managed_pin(__caller_arena__, ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__lines))[__sn__i]))));
                    }
                __for_continue_2__:;
                    rt_post_inc_long(&__sn__i);
                }
            }
            __sn__req.__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, rt_array_join_string_h(__caller_arena__, ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__bodyLines)), "\n"));
        }
    }
    _return_value = __sn__req;
    goto __sn__HttpRequest_parse_return;
__sn__HttpRequest_parse_return:
    return _return_value;
}

RtHandle __sn__HttpRequest_getHeader(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name) {
    RtHandle _return_value = RT_HANDLE_NULL;
    RtThreadHandle *__lowerName_pending__ = NULL;
    RtHandle __sn__lowerName = rt_str_toLower_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__name));
    {
        __sn__Header * __arr_4__ = ((__sn__Header *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_4__ = rt_array_length(__arr_4__);
        for (long __idx_4__ = 0; __idx_4__ < __len_4__; __idx_4__++) {
            __sn__Header __sn__h = __arr_4__[__idx_4__];
            {
                if (rt_eq_string(rt_str_toLower(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__name))), (char *)rt_managed_pin(__caller_arena__, __sn__lowerName))) {
                    {
                        _return_value = __sn__h.__sn__value;
                        goto __sn__HttpRequest_getHeader_return;
                    }
                }
            }
        }
    }
    _return_value = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "");
    goto __sn__HttpRequest_getHeader_return;
__sn__HttpRequest_getHeader_return:
    return _return_value;
}

bool __sn__HttpRequest_hasHeader(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name) {
    bool _return_value = 0;
    RtThreadHandle *__lowerName_pending__ = NULL;
    RtHandle __sn__lowerName = rt_str_toLower_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__name));
    {
        __sn__Header * __arr_5__ = ((__sn__Header *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_5__ = rt_array_length(__arr_5__);
        for (long __idx_5__ = 0; __idx_5__ < __len_5__; __idx_5__++) {
            __sn__Header __sn__h = __arr_5__[__idx_5__];
            {
                if (rt_eq_string(rt_str_toLower(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__name))), (char *)rt_managed_pin(__caller_arena__, __sn__lowerName))) {
                    {
                        _return_value = 1L;
                        goto __sn__HttpRequest_hasHeader_return;
                    }
                }
            }
        }
    }
    _return_value = 0L;
    goto __sn__HttpRequest_hasHeader_return;
__sn__HttpRequest_hasHeader_return:
    return _return_value;
}

RtHandle __sn__HttpRequest_queryParam(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name) {
    RtHandle _return_value = RT_HANDLE_NULL;
    if (rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__query)), "")) {
        {
            _return_value = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "");
            goto __sn__HttpRequest_queryParam_return;
        }
    }
    RtThreadHandle *__pairs_pending__ = NULL;
    RtHandle __sn__pairs = rt_str_split_h(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__query)), "&");
    {
        RtHandle * __arr_6__ = ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__pairs));
        long __len_6__ = rt_array_length(__arr_6__);
        for (long __idx_6__ = 0; __idx_6__ < __len_6__; __idx_6__++) {
            RtHandle __sn__pair = __arr_6__[__idx_6__];
            {
                RtThreadHandle *__eqIndex_pending__ = NULL;
                long long __sn__eqIndex = rt_str_indexOf((char *)rt_managed_pin(__caller_arena__, __sn__pair), "=");
                if (rt_gt_long(__sn__eqIndex, 0LL)) {
                    {
                        RtThreadHandle *__key_pending__ = NULL;
                        RtHandle __sn__key = rt_str_substring_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__pair), 0LL, __sn__eqIndex);
                        if (rt_eq_string((char *)rt_managed_pin(__caller_arena__, __sn__key), (char *)rt_managed_pin(__caller_arena__, __sn__name))) {
                            {
                                _return_value = rt_str_substring_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__pair), rt_add_long(__sn__eqIndex, 1LL), rt_str_length((char *)rt_managed_pin(__caller_arena__, __sn__pair)));
                                goto __sn__HttpRequest_queryParam_return;
                            }
                        }
                    }
                }
                else {
                    if (rt_eq_string((char *)rt_managed_pin(__caller_arena__, __sn__pair), (char *)rt_managed_pin(__caller_arena__, __sn__name))) {
                        {
                            _return_value = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "");
                            goto __sn__HttpRequest_queryParam_return;
                        }
                    }
                }
            }
        }
    }
    _return_value = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "");
    goto __sn__HttpRequest_queryParam_return;
__sn__HttpRequest_queryParam_return:
    return _return_value;
}

bool __sn__HttpRequest_hasQueryParam(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self, RtHandle __sn__name) {
    bool _return_value = 0;
    if (rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__query)), "")) {
        {
            _return_value = 0L;
            goto __sn__HttpRequest_hasQueryParam_return;
        }
    }
    RtThreadHandle *__pairs_pending__ = NULL;
    RtHandle __sn__pairs = rt_str_split_h(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__query)), "&");
    {
        RtHandle * __arr_7__ = ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__pairs));
        long __len_7__ = rt_array_length(__arr_7__);
        for (long __idx_7__ = 0; __idx_7__ < __len_7__; __idx_7__++) {
            RtHandle __sn__pair = __arr_7__[__idx_7__];
            {
                RtThreadHandle *__eqIndex_pending__ = NULL;
                long long __sn__eqIndex = rt_str_indexOf((char *)rt_managed_pin(__caller_arena__, __sn__pair), "=");
                if (rt_gt_long(__sn__eqIndex, 0LL)) {
                    {
                        RtThreadHandle *__key_pending__ = NULL;
                        RtHandle __sn__key = rt_str_substring_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__pair), 0LL, __sn__eqIndex);
                        if (rt_eq_string((char *)rt_managed_pin(__caller_arena__, __sn__key), (char *)rt_managed_pin(__caller_arena__, __sn__name))) {
                            {
                                _return_value = 1L;
                                goto __sn__HttpRequest_hasQueryParam_return;
                            }
                        }
                    }
                }
                else {
                    if (rt_eq_string((char *)rt_managed_pin(__caller_arena__, __sn__pair), (char *)rt_managed_pin(__caller_arena__, __sn__name))) {
                        {
                            _return_value = 1L;
                            goto __sn__HttpRequest_hasQueryParam_return;
                        }
                    }
                }
            }
        }
    }
    _return_value = 0L;
    goto __sn__HttpRequest_hasQueryParam_return;
__sn__HttpRequest_hasQueryParam_return:
    return _return_value;
}

RtHandle __sn__HttpRequest_contentType(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    RtHandle _return_value = RT_HANDLE_NULL;
    _return_value = ({
    RtHandle __iarg_29_0 = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__caller_arena__, (void *)__sn__self, sizeof(__sn__HttpRequest), 58068878);
        __args[1] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __iarg_29_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpRequest.getHeader", __args, 2, __thunk_29);
        __intercept_result = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)__sn__self, rt_unbox_struct(__args[0], 58068878), sizeof(__sn__HttpRequest));
    } else {
        __intercept_result = __sn__HttpRequest_getHeader(__caller_arena__, __sn__self, __iarg_29_0);
    }
    __intercept_result;
});
    goto __sn__HttpRequest_contentType_return;
__sn__HttpRequest_contentType_return:
    return _return_value;
}

long long __sn__HttpRequest_contentLength(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    long long _return_value = 0;
    RtThreadHandle *__lenStr_pending__ = NULL;
    RtHandle __sn__lenStr = ({
    RtHandle __iarg_30_0 = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Length");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__caller_arena__, (void *)__sn__self, sizeof(__sn__HttpRequest), 58068878);
        __args[1] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __iarg_30_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpRequest.getHeader", __args, 2, __thunk_30);
        __intercept_result = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)__sn__self, rt_unbox_struct(__args[0], 58068878), sizeof(__sn__HttpRequest));
    } else {
        __intercept_result = __sn__HttpRequest_getHeader(__caller_arena__, __sn__self, __iarg_30_0);
    }
    __intercept_result;
});
    if (rt_eq_string((char *)rt_managed_pin(__caller_arena__, __sn__lenStr), "")) {
        {
            _return_value = 0LL;
            goto __sn__HttpRequest_contentLength_return;
        }
    }
    _return_value = rt_str_to_int((char *)rt_managed_pin(__caller_arena__, __sn__lenStr));
    goto __sn__HttpRequest_contentLength_return;
__sn__HttpRequest_contentLength_return:
    return _return_value;
}

bool __sn__HttpRequest_hasBody(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_gt_long(rt_str_length(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__body))), 0LL);
    goto __sn__HttpRequest_hasBody_return;
__sn__HttpRequest_hasBody_return:
    return _return_value;
}

bool __sn__HttpRequest_isGet(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "GET");
    goto __sn__HttpRequest_isGet_return;
__sn__HttpRequest_isGet_return:
    return _return_value;
}

bool __sn__HttpRequest_isPost(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "POST");
    goto __sn__HttpRequest_isPost_return;
__sn__HttpRequest_isPost_return:
    return _return_value;
}

bool __sn__HttpRequest_isPut(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "PUT");
    goto __sn__HttpRequest_isPut_return;
__sn__HttpRequest_isPut_return:
    return _return_value;
}

bool __sn__HttpRequest_isDelete(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "DELETE");
    goto __sn__HttpRequest_isDelete_return;
__sn__HttpRequest_isDelete_return:
    return _return_value;
}

bool __sn__HttpRequest_isPatch(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "PATCH");
    goto __sn__HttpRequest_isPatch_return;
__sn__HttpRequest_isPatch_return:
    return _return_value;
}

bool __sn__HttpRequest_isHead(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "HEAD");
    goto __sn__HttpRequest_isHead_return;
__sn__HttpRequest_isHead_return:
    return _return_value;
}

bool __sn__HttpRequest_isOptions(RtManagedArena *__caller_arena__, __sn__HttpRequest *__sn__self) {
    bool _return_value = 0;
    _return_value = rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__method)), "OPTIONS");
    goto __sn__HttpRequest_isOptions_return;
__sn__HttpRequest_isOptions_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_new(RtManagedArena *__caller_arena__, long long __sn__code) {
    __sn__HttpResponse _return_value = {0};
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = (__sn__HttpResponse){ .__sn__statusCode = __sn__code, .__sn__statusText = ({
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __args[0] = rt_box_int(__sn__code);
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("statusText", __args, 1, __thunk_31);
        __intercept_result = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
    } else {
        __intercept_result = __sn__statusText(__caller_arena__, __sn__code);
    }
    __intercept_result;
}), .__sn__version = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "HTTP/1.1"), .__sn__headers = RT_HANDLE_NULL, .__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "") };
    _return_value = __sn__res;
    goto __sn__HttpResponse_new_return;
__sn__HttpResponse_new_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_ok(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 200LL);
    goto __sn__HttpResponse_ok_return;
__sn__HttpResponse_ok_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_created(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 201LL);
    goto __sn__HttpResponse_created_return;
__sn__HttpResponse_created_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_noContent(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 204LL);
    goto __sn__HttpResponse_noContent_return;
__sn__HttpResponse_noContent_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_badRequest(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 400LL);
    goto __sn__HttpResponse_badRequest_return;
__sn__HttpResponse_badRequest_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_unauthorized(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 401LL);
    goto __sn__HttpResponse_unauthorized_return;
__sn__HttpResponse_unauthorized_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_forbidden(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 403LL);
    goto __sn__HttpResponse_forbidden_return;
__sn__HttpResponse_forbidden_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_notFound(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 404LL);
    goto __sn__HttpResponse_notFound_return;
__sn__HttpResponse_notFound_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_methodNotAllowed(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 405LL);
    goto __sn__HttpResponse_methodNotAllowed_return;
__sn__HttpResponse_methodNotAllowed_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_internalServerError(RtManagedArena *__caller_arena__) {
    __sn__HttpResponse _return_value = {0};
    _return_value = __sn__HttpResponse_new(__caller_arena__, 500LL);
    goto __sn__HttpResponse_internalServerError_return;
__sn__HttpResponse_internalServerError_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_setHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name, RtHandle __sn__value) {
    __sn__HttpResponse _return_value = {0};
    RtThreadHandle *__lowerName_pending__ = NULL;
    RtHandle __sn__lowerName = rt_str_toLower_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__name));
    RtThreadHandle *__newHeaders_pending__ = NULL;
    RtHandle __sn__newHeaders = rt_array_create_generic_h(__caller_arena__, 0, sizeof(__sn__ResponseHeader), NULL);
    {
        __sn__ResponseHeader * __arr_8__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_8__ = rt_array_length(__arr_8__);
        for (long __idx_8__ = 0; __idx_8__ < __len_8__; __idx_8__++) {
            __sn__ResponseHeader __sn__h = __arr_8__[__idx_8__];
            {
                if (rt_ne_string(rt_str_toLower(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__name))), (char *)rt_managed_pin(__caller_arena__, __sn__lowerName))) {
                    {
                        (__sn__newHeaders = rt_array_push_struct_h(__caller_arena__, __sn__newHeaders, &__sn__h, sizeof(__sn__ResponseHeader)));
                    }
                }
            }
        }
    }
    (__sn__newHeaders = rt_array_push_struct_h(__caller_arena__, __sn__newHeaders, &(__sn__ResponseHeader){ .__sn__name = __sn__name, .__sn__value = __sn__value }, sizeof(__sn__ResponseHeader)));
    __sn__self->__sn__headers = __sn__newHeaders;
    _return_value = (*__sn__self);
    goto __sn__HttpResponse_setHeader_return;
__sn__HttpResponse_setHeader_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_addHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name, RtHandle __sn__value) {
    __sn__HttpResponse _return_value = {0};
    (__sn__self->__sn__headers = rt_array_push_struct_h(__caller_arena__, __sn__self->__sn__headers, &(__sn__ResponseHeader){ .__sn__name = __sn__name, .__sn__value = __sn__value }, sizeof(__sn__ResponseHeader)));
    _return_value = (*__sn__self);
    goto __sn__HttpResponse_addHeader_return;
__sn__HttpResponse_addHeader_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_setBody(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content) {
    __sn__HttpResponse _return_value = {0};
    __sn__self->__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__content));
    _return_value = (*__sn__self);
    goto __sn__HttpResponse_setBody_return;
__sn__HttpResponse_setBody_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_html(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content) {
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse_setHeader(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Type"), rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "text/html; charset=utf-8"));
    __sn__self->__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__content));
    _return_value = (*__sn__self);
    goto __sn__HttpResponse_html_return;
__sn__HttpResponse_html_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_text(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content) {
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse_setHeader(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Type"), rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "text/plain; charset=utf-8"));
    __sn__self->__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__content));
    _return_value = (*__sn__self);
    goto __sn__HttpResponse_text_return;
__sn__HttpResponse_text_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_json(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__content) {
    __sn__HttpResponse _return_value = {0};
    __sn__HttpResponse_setHeader(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Type"), rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "application/json; charset=utf-8"));
    __sn__self->__sn__body = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__content));
    _return_value = (*__sn__self);
    goto __sn__HttpResponse_json_return;
__sn__HttpResponse_json_return:
    return _return_value;
}

__sn__HttpResponse __sn__HttpResponse_redirect(RtManagedArena *__caller_arena__, RtHandle __sn__location) {
    __sn__HttpResponse _return_value = {0};
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = __sn__HttpResponse_new(__caller_arena__, 302LL);
    __sn__HttpResponse_setHeader(__caller_arena__, &__sn__res, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Location"), __sn__location);
    _return_value = __sn__res;
    goto __sn__HttpResponse_redirect_return;
__sn__HttpResponse_redirect_return:
    return _return_value;
}

RtHandle __sn__HttpResponse_getHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name) {
    RtHandle _return_value = RT_HANDLE_NULL;
    RtThreadHandle *__lowerName_pending__ = NULL;
    RtHandle __sn__lowerName = rt_str_toLower_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__name));
    {
        __sn__ResponseHeader * __arr_9__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_9__ = rt_array_length(__arr_9__);
        for (long __idx_9__ = 0; __idx_9__ < __len_9__; __idx_9__++) {
            __sn__ResponseHeader __sn__h = __arr_9__[__idx_9__];
            {
                if (rt_eq_string(rt_str_toLower(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__name))), (char *)rt_managed_pin(__caller_arena__, __sn__lowerName))) {
                    {
                        _return_value = __sn__h.__sn__value;
                        goto __sn__HttpResponse_getHeader_return;
                    }
                }
            }
        }
    }
    _return_value = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "");
    goto __sn__HttpResponse_getHeader_return;
__sn__HttpResponse_getHeader_return:
    return _return_value;
}

bool __sn__HttpResponse_hasHeader(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self, RtHandle __sn__name) {
    bool _return_value = 0;
    RtThreadHandle *__lowerName_pending__ = NULL;
    RtHandle __sn__lowerName = rt_str_toLower_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__name));
    {
        __sn__ResponseHeader * __arr_10__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_10__ = rt_array_length(__arr_10__);
        for (long __idx_10__ = 0; __idx_10__ < __len_10__; __idx_10__++) {
            __sn__ResponseHeader __sn__h = __arr_10__[__idx_10__];
            {
                if (rt_eq_string(rt_str_toLower(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__name))), (char *)rt_managed_pin(__caller_arena__, __sn__lowerName))) {
                    {
                        _return_value = 1L;
                        goto __sn__HttpResponse_hasHeader_return;
                    }
                }
            }
        }
    }
    _return_value = 0L;
    goto __sn__HttpResponse_hasHeader_return;
__sn__HttpResponse_hasHeader_return:
    return _return_value;
}

RtHandle __sn__HttpResponse_toString(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self) {
    RtHandle _return_value = RT_HANDLE_NULL;
    RtThreadHandle *__result_pending__ = NULL;
    RtHandle __sn__result = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "");
    (__sn__result = ({
        char *_p0 = rt_to_string_long(__caller_arena__, __sn__self->__sn__statusCode);
        char *_r = rt_str_concat(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__version)), " ");
        _r = rt_str_concat(__caller_arena__, _r, _p0);
        _r = rt_str_concat(__caller_arena__, _r, " ");
        _r = rt_str_concat(__caller_arena__, _r, ((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__statusText)));
        _r = rt_str_concat(__caller_arena__, _r, "\r\n");
        rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, _r);
    }));
    if (((rt_gt_long(rt_str_length(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__body))), 0LL) != 0 && rt_not_bool(({
    RtHandle __iarg_32_0 = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Length");
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__caller_arena__, (void *)__sn__self, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __iarg_32_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.hasHeader", __args, 2, __thunk_32);
        __intercept_result = rt_unbox_bool(__intercepted);
        memcpy((void *)__sn__self, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_hasHeader(__caller_arena__, __sn__self, __iarg_32_0);
    }
    __intercept_result;
})) != 0) ? 1L : 0L)) {
        {
            (__sn__result = rt_str_concat_h(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__result), ({
        char *_p0 = rt_to_string_long(__caller_arena__, rt_str_length(((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__body))));
        char *_r = rt_str_concat(__caller_arena__, "Content-Length: ", _p0);
        _r = rt_str_concat(__caller_arena__, _r, "\r\n");
        _r;
    })));
        }
    }
    {
        __sn__ResponseHeader * __arr_11__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_11__ = rt_array_length(__arr_11__);
        for (long __idx_11__ = 0; __idx_11__ < __len_11__; __idx_11__++) {
            __sn__ResponseHeader __sn__h = __arr_11__[__idx_11__];
            {
                (__sn__result = rt_str_concat_h(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__result), ({
        char *_r = rt_str_concat(__caller_arena__, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__name)), ": ");
        _r = rt_str_concat(__caller_arena__, _r, ((char *)rt_managed_pin(__caller_arena__, __sn__h.__sn__value)));
        _r = rt_str_concat(__caller_arena__, _r, "\r\n");
        _r;
    })));
            }
        }
    }
    (__sn__result = rt_str_concat_h(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__result), "\r\n"));
    (__sn__result = rt_str_concat_h(__caller_arena__, RT_HANDLE_NULL, (char *)rt_managed_pin(__caller_arena__, __sn__result), ((char *)rt_managed_pin(__caller_arena__, __sn__self->__sn__body))));
    _return_value = __sn__result;
    goto __sn__HttpResponse_toString_return;
__sn__HttpResponse_toString_return:
    return _return_value;
}

RtHandle __sn__HttpResponse_toBytes(RtManagedArena *__caller_arena__, __sn__HttpResponse *__sn__self) {
    RtHandle _return_value = RT_HANDLE_NULL;
    _return_value = rt_array_clone_byte_h(__caller_arena__, RT_HANDLE_NULL, ({ char *_obj_tmp = (char *)rt_managed_pin(__caller_arena__, ({
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __args[0] = rt_box_struct(__caller_arena__, (void *)__sn__self, sizeof(__sn__HttpResponse), 1988968148);
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.toString", __args, 1, __thunk_33);
        __intercept_result = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)__sn__self, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_toString(__caller_arena__, __sn__self);
    }
    __intercept_result;
})); unsigned char *_res = rt_string_to_bytes(__caller_arena__, _obj_tmp); _res; }));
    goto __sn__HttpResponse_toBytes_return;
__sn__HttpResponse_toBytes_return:
    return _return_value;
}

__sn__Router __sn__Router_new(RtManagedArena *__caller_arena__) {
    __sn__Router _return_value = {0};
    _return_value = (__sn__Router){ .__sn__routes = RT_HANDLE_NULL, .__sn__notFoundHandler = __sn__defaultNotFoundHandler, .__sn__methodNotAllowedHandler = __sn__defaultMethodNotAllowedHandler };
    goto __sn__Router_new_return;
__sn__Router_new_return:
    return _return_value;
}

__sn__Router __sn__Router_route(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__method, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    (__sn__self->__sn__routes = rt_array_push_struct_h(__caller_arena__, __sn__self->__sn__routes, &(__sn__Route){ .__sn__method = rt_str_toUpper_h(__caller_arena__, (char *)rt_managed_pin(__caller_arena__, __sn__method)), .__sn__pattern = __sn__path, .__sn__handler = __sn__handler }, sizeof(__sn__Route)));
    _return_value = (*__sn__self);
    goto __sn__Router_route_return;
__sn__Router_route_return:
    return _return_value;
}

__sn__Router __sn__Router_get(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "GET"), __sn__path, __sn__handler);
    goto __sn__Router_get_return;
__sn__Router_get_return:
    return _return_value;
}

__sn__Router __sn__Router_post(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "POST"), __sn__path, __sn__handler);
    goto __sn__Router_post_return;
__sn__Router_post_return:
    return _return_value;
}

__sn__Router __sn__Router_put(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "PUT"), __sn__path, __sn__handler);
    goto __sn__Router_put_return;
__sn__Router_put_return:
    return _return_value;
}

__sn__Router __sn__Router_delete(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "DELETE"), __sn__path, __sn__handler);
    goto __sn__Router_delete_return;
__sn__Router_delete_return:
    return _return_value;
}

__sn__Router __sn__Router_patch(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "PATCH"), __sn__path, __sn__handler);
    goto __sn__Router_patch_return;
__sn__Router_patch_return:
    return _return_value;
}

__sn__Router __sn__Router_head(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "HEAD"), __sn__path, __sn__handler);
    goto __sn__Router_head_return;
__sn__Router_head_return:
    return _return_value;
}

__sn__Router __sn__Router_options(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "OPTIONS"), __sn__path, __sn__handler);
    goto __sn__Router_options_return;
__sn__Router_options_return:
    return _return_value;
}

__sn__Router __sn__Router_all(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    _return_value = __sn__Router_route(__caller_arena__, __sn__self, rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "*"), __sn__path, __sn__handler);
    goto __sn__Router_all_return;
__sn__Router_all_return:
    return _return_value;
}

__sn__Router __sn__Router_setNotFoundHandler(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    __sn__self->__sn__notFoundHandler = __sn__handler;
    _return_value = (*__sn__self);
    goto __sn__Router_setNotFoundHandler_return;
__sn__Router_setNotFoundHandler_return:
    return _return_value;
}

__sn__Router __sn__Router_setMethodNotAllowedHandler(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, __Closure__ * __sn__handler) {
    __sn__Router _return_value = {0};
    __sn__self->__sn__methodNotAllowedHandler = __sn__handler;
    _return_value = (*__sn__self);
    goto __sn__Router_setMethodNotAllowedHandler_return;
__sn__Router_setMethodNotAllowedHandler_return:
    return _return_value;
}

__sn__HttpResponse __sn__Router_handle(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, __sn__HttpRequest __sn__req) {
    __sn__HttpResponse _return_value = {0};
    RtThreadHandle *__pathMatches_pending__ = NULL;
    bool __sn__pathMatches = 0L;
    {
        __sn__Route * __arr_12__ = ((__sn__Route *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__routes));
        long __len_12__ = rt_array_length(__arr_12__);
        for (long __idx_12__ = 0; __idx_12__ < __len_12__; __idx_12__++) {
            __sn__Route __sn__route = __arr_12__[__idx_12__];
            {
                if (({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__pattern));
        __args[1] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __sn__req.__sn__path));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_34);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__caller_arena__, __sn__route.__sn__pattern, __sn__req.__sn__path);
    }
    __intercept_result;
})) {
                    {
                        (__sn__pathMatches = 1L);
                        if (((rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__method)), "*") != 0 || rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__method)), ((char *)rt_managed_pin(__caller_arena__, __sn__req.__sn__method))) != 0) ? 1L : 0L)) {
                            {
                                _return_value = __sn__route.__sn__handler(__sn__req);
                                goto __sn__Router_handle_return;
                            }
                        }
                    }
                }
            }
        }
    }
    if (__sn__pathMatches) {
        {
            _return_value = __sn__self->__sn__methodNotAllowedHandler(__sn__req);
            goto __sn__Router_handle_return;
        }
    }
    _return_value = __sn__self->__sn__notFoundHandler(__sn__req);
    goto __sn__Router_handle_return;
__sn__Router_handle_return:
    return _return_value;
}

RtHandle __sn__Router_allowedMethods(RtManagedArena *__caller_arena__, __sn__Router *__sn__self, RtHandle __sn__path) {
    RtHandle _return_value = RT_HANDLE_NULL;
    RtThreadHandle *__methods_pending__ = NULL;
    RtHandle __sn__methods = rt_array_create_string_h(__caller_arena__, 0, (char *[]){});
    {
        __sn__Route * __arr_13__ = ((__sn__Route *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__routes));
        long __len_13__ = rt_array_length(__arr_13__);
        for (long __idx_13__ = 0; __idx_13__ < __len_13__; __idx_13__++) {
            __sn__Route __sn__route = __arr_13__[__idx_13__];
            {
                if (({
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__pattern));
        __args[1] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __sn__path));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("matchPath", __args, 2, __thunk_35);
        __intercept_result = rt_unbox_bool(__intercepted);
    } else {
        __intercept_result = __sn__matchPath(__caller_arena__, __sn__route.__sn__pattern, __sn__path);
    }
    __intercept_result;
})) {
                    {
                        if (rt_eq_string(((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__method)), "*")) {
                            {
                                _return_value = rt_array_create_string_h(__caller_arena__, 7, (char *[]){"GET", "POST", "PUT", "DELETE", "PATCH", "HEAD", "OPTIONS"});
                                goto __sn__Router_allowedMethods_return;
                            }
                        }
                        RtThreadHandle *__found_pending__ = NULL;
                        bool __sn__found = 0L;
                        {
                            RtHandle * __arr_14__ = ((RtHandle *)rt_managed_pin_array(__caller_arena__, __sn__methods));
                            long __len_14__ = rt_array_length(__arr_14__);
                            for (long __idx_14__ = 0; __idx_14__ < __len_14__; __idx_14__++) {
                                RtHandle __sn__m = __arr_14__[__idx_14__];
                                {
                                    if (rt_eq_string((char *)rt_managed_pin(__caller_arena__, __sn__m), ((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__method)))) {
                                        {
                                            (__sn__found = 1L);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        if (rt_not_bool(__sn__found)) {
                            {
                                (__sn__methods = rt_array_push_string_h(__caller_arena__, __sn__methods, ((char *)rt_managed_pin(__caller_arena__, __sn__route.__sn__method))));
                            }
                        }
                    }
                }
            }
        }
    }
    _return_value = __sn__methods;
    goto __sn__Router_allowedMethods_return;
__sn__Router_allowedMethods_return:
    return _return_value;
}


/* Interceptor thunk definitions */
static RtAny __thunk_0(void) {
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__normalizePath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])))));
    return __result;
}

static RtAny __thunk_1(void) {
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__normalizePath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])))));
    return __result;
}

static RtAny __thunk_2(void) {
    __sn__testRouteRegistration((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_3(void) {
    __sn__testBasicRouting((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_4(void) {
    __sn__testPathMatching((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_5(void) {
    __sn__testMethodMatching((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_6(void) {
    __sn__testWildcards((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_7(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_8(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_9(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_10(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_11(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_12(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_13(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_14(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_15(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_16(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_17(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_18(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_19(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_20(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_21(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_22(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_23(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_24(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_25(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_26(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_27(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_28(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_29(void) {
    __sn__HttpRequest *__self = (__sn__HttpRequest *)rt_unbox_struct(__rt_thunk_args[0], 58068878);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpRequest_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_30(void) {
    __sn__HttpRequest *__self = (__sn__HttpRequest *)rt_unbox_struct(__rt_thunk_args[0], 58068878);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpRequest_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_31(void) {
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__statusText((RtArena *)__rt_thunk_arena, rt_unbox_int(__rt_thunk_args[0]))));
    return __result;
}

static RtAny __thunk_32(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_bool(__sn__HttpResponse_hasHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_33(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_toString((RtArena *)__rt_thunk_arena, __self)));
    return __result;
}

static RtAny __thunk_34(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_35(void) {
    RtAny __result = rt_box_bool(__sn__matchPath((RtArena *)__rt_thunk_arena, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[0])), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

