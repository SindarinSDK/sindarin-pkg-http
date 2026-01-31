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
} __sn__ResponseHeader;
typedef struct {
    long long __sn__statusCode;
    RtHandle __sn__statusText;
    RtHandle __sn__version;
    RtHandle __sn__headers;
    RtHandle __sn__body;
} __sn__HttpResponse;

/* Struct method forward declarations */
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

/* Forward declarations */
static RtManagedArena *__main_arena__ = NULL;

RtHandle __sn__statusText(RtManagedArena *, long long);
bool __sn__isInformational(RtManagedArena *, long long);
bool __sn__isSuccess(RtManagedArena *, long long);
bool __sn__isRedirect(RtManagedArena *, long long);
bool __sn__isClientError(RtManagedArena *, long long);
bool __sn__isServerError(RtManagedArena *, long long);
bool __sn__isError(RtManagedArena *, long long);
void __sn__check(RtManagedArena *, bool, RtHandle);
void __sn__testBasicResponse(RtManagedArena *);
void __sn__testStatusFactories(RtManagedArena *);
void __sn__testHeaders(RtManagedArena *);
void __sn__testContentTypes(RtManagedArena *);
void __sn__testSerialization(RtManagedArena *);

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
static RtAny __thunk_36(void);
static RtAny __thunk_37(void);
static RtAny __thunk_38(void);
static RtAny __thunk_39(void);
static RtAny __thunk_40(void);
static RtAny __thunk_41(void);
static RtAny __thunk_42(void);
static RtAny __thunk_43(void);
static RtAny __thunk_44(void);
static RtAny __thunk_45(void);

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

int main() {
    RtManagedArena *__local_arena__ = rt_managed_arena_create();
    __main_arena__ = __local_arena__;
    int _return_value = 0;
    rt_print_string("Testing HTTP Response Builder\n");
    rt_print_string("==============================\n\n");
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testBasicResponse", __args, 0, __thunk_0);
    } else {
        __sn__testBasicResponse(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testStatusFactories", __args, 0, __thunk_1);
    } else {
        __sn__testStatusFactories(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testHeaders", __args, 0, __thunk_2);
    } else {
        __sn__testHeaders(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testContentTypes", __args, 0, __thunk_3);
    } else {
        __sn__testContentTypes(__local_arena__);
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("testSerialization", __args, 0, __thunk_4);
    } else {
        __sn__testSerialization(__local_arena__);
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
            rt_print_string("All response tests passed!\n");
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

void __sn__testBasicResponse(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing basic response creation...\n");
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = __sn__HttpResponse_new(__local_arena__, 200LL);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__res.__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status code should be 200")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_5);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__res.__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status code should be 200"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__res.__sn__statusText)), "OK"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status text should be OK")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_6);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__res.__sn__statusText)), "OK"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status text should be OK"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__res.__sn__version)), "HTTP/1.1"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Version should be HTTP/1.1")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_7);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__res.__sn__version)), "HTTP/1.1"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Version should be HTTP/1.1"));
    }
    (void)0;
});
    RtThreadHandle *__res404_pending__ = NULL;
    __sn__HttpResponse __sn__res404 = __sn__HttpResponse_new(__local_arena__, 404LL);
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__res404.__sn__statusCode, 404LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status code should be 404")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_8);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__res404.__sn__statusCode, 404LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status code should be 404"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__res404.__sn__statusText)), "Not Found"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status text should be Not Found")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_9);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__res404.__sn__statusText)), "Not Found"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Status text should be Not Found"));
    }
    (void)0;
});
    rt_print_string("  Basic response OK\n");
    goto __sn__testBasicResponse_return;
__sn__testBasicResponse_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testStatusFactories(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing status factory methods...\n");
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_ok(__local_arena__).__sn__statusCode, 200LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "ok() should return 200")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_10);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_ok(__local_arena__).__sn__statusCode, 200LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "ok() should return 200"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_created(__local_arena__).__sn__statusCode, 201LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "created() should return 201")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_11);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_created(__local_arena__).__sn__statusCode, 201LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "created() should return 201"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_noContent(__local_arena__).__sn__statusCode, 204LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "noContent() should return 204")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_12);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_noContent(__local_arena__).__sn__statusCode, 204LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "noContent() should return 204"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_badRequest(__local_arena__).__sn__statusCode, 400LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "badRequest() should return 400")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_13);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_badRequest(__local_arena__).__sn__statusCode, 400LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "badRequest() should return 400"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_unauthorized(__local_arena__).__sn__statusCode, 401LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "unauthorized() should return 401")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_14);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_unauthorized(__local_arena__).__sn__statusCode, 401LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "unauthorized() should return 401"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_forbidden(__local_arena__).__sn__statusCode, 403LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "forbidden() should return 403")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_15);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_forbidden(__local_arena__).__sn__statusCode, 403LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "forbidden() should return 403"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_notFound(__local_arena__).__sn__statusCode, 404LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "notFound() should return 404")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_16);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_notFound(__local_arena__).__sn__statusCode, 404LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "notFound() should return 404"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_methodNotAllowed(__local_arena__).__sn__statusCode, 405LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "methodNotAllowed() should return 405")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_17);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_methodNotAllowed(__local_arena__).__sn__statusCode, 405LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "methodNotAllowed() should return 405"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_long(__sn__HttpResponse_internalServerError(__local_arena__).__sn__statusCode, 500LL));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "internalServerError() should return 500")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_18);
    } else {
        __sn__check(__local_arena__, rt_eq_long(__sn__HttpResponse_internalServerError(__local_arena__).__sn__statusCode, 500LL), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "internalServerError() should return 500"));
    }
    (void)0;
});
    rt_print_string("  Status factories OK\n");
    goto __sn__testStatusFactories_return;
__sn__testStatusFactories_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testHeaders(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing header methods...\n");
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = __sn__HttpResponse_ok(__local_arena__);
    __sn__HttpResponse_setHeader(__local_arena__, &__sn__res, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "value1"));
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    RtHandle __iarg_19_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom");
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_19_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.hasHeader", __args, 2, __thunk_19);
        __intercept_result = rt_unbox_bool(__intercepted);
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_hasHeader(__local_arena__, &__sn__res, __iarg_19_0);
    }
    __intercept_result;
})) == (1L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Should have X-Custom header")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_20);
    } else {
        __sn__check(__local_arena__, ((({
    RtHandle __iarg_19_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom");
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_19_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.hasHeader", __args, 2, __thunk_19);
        __intercept_result = rt_unbox_bool(__intercepted);
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_hasHeader(__local_arena__, &__sn__res, __iarg_19_0);
    }
    __intercept_result;
})) == (1L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Should have X-Custom header"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_21_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_21_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_21);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__res, __iarg_21_0);
    }
    __intercept_result;
})), "value1"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom should be value1")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_22);
    } else {
        __sn__check(__local_arena__, rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_21_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_21_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_21);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__res, __iarg_21_0);
    }
    __intercept_result;
})), "value1"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom should be value1"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_23_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "x-custom");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_23_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_23);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__res, __iarg_23_0);
    }
    __intercept_result;
})), "value1"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Header access should be case-insensitive")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_24);
    } else {
        __sn__check(__local_arena__, rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_23_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "x-custom");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_23_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_23);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__res, __iarg_23_0);
    }
    __intercept_result;
})), "value1"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Header access should be case-insensitive"));
    }
    (void)0;
});
    __sn__HttpResponse_setHeader(__local_arena__, &__sn__res, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "value2"));
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_25_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_25_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_25);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__res, __iarg_25_0);
    }
    __intercept_result;
})), "value2"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "setHeader should replace existing")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_26);
    } else {
        __sn__check(__local_arena__, rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_25_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Custom");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_25_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_25);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__res, __iarg_25_0);
    }
    __intercept_result;
})), "value2"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "setHeader should replace existing"));
    }
    (void)0;
});
    __sn__HttpResponse_addHeader(__local_arena__, &__sn__res, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Multi"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "a"));
    __sn__HttpResponse_addHeader(__local_arena__, &__sn__res, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Multi"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "b"));
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(((({
    RtHandle __iarg_27_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Multi");
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_27_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.hasHeader", __args, 2, __thunk_27);
        __intercept_result = rt_unbox_bool(__intercepted);
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_hasHeader(__local_arena__, &__sn__res, __iarg_27_0);
    }
    __intercept_result;
})) == (1L)));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Should have X-Multi header")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_28);
    } else {
        __sn__check(__local_arena__, ((({
    RtHandle __iarg_27_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "X-Multi");
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_27_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.hasHeader", __args, 2, __thunk_27);
        __intercept_result = rt_unbox_bool(__intercepted);
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_hasHeader(__local_arena__, &__sn__res, __iarg_27_0);
    }
    __intercept_result;
})) == (1L)), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Should have X-Multi header"));
    }
    (void)0;
});
    rt_print_string("  Header methods OK\n");
    goto __sn__testHeaders_return;
__sn__testHeaders_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testContentTypes(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing content type helpers...\n");
    RtThreadHandle *__htmlRes_pending__ = NULL;
    __sn__HttpResponse __sn__htmlRes = __sn__HttpResponse_ok(__local_arena__);
    __sn__HttpResponse_html(__local_arena__, &__sn__htmlRes, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "<h1>Hello</h1>"));
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_29_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__htmlRes, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_29_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_29);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__htmlRes, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__htmlRes, __iarg_29_0);
    }
    __intercept_result;
})), "text/html; charset=utf-8"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "html() should set Content-Type")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_30);
    } else {
        __sn__check(__local_arena__, rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_29_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__htmlRes, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_29_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_29);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__htmlRes, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__htmlRes, __iarg_29_0);
    }
    __intercept_result;
})), "text/html; charset=utf-8"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "html() should set Content-Type"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__htmlRes.__sn__body)), "<h1>Hello</h1>"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "html() should set body")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_31);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__htmlRes.__sn__body)), "<h1>Hello</h1>"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "html() should set body"));
    }
    (void)0;
});
    RtThreadHandle *__textRes_pending__ = NULL;
    __sn__HttpResponse __sn__textRes = __sn__HttpResponse_ok(__local_arena__);
    __sn__HttpResponse_text(__local_arena__, &__sn__textRes, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Hello World"));
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_32_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__textRes, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_32_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_32);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__textRes, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__textRes, __iarg_32_0);
    }
    __intercept_result;
})), "text/plain; charset=utf-8"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "text() should set Content-Type")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_33);
    } else {
        __sn__check(__local_arena__, rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_32_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__textRes, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_32_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_32);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__textRes, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__textRes, __iarg_32_0);
    }
    __intercept_result;
})), "text/plain; charset=utf-8"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "text() should set Content-Type"));
    }
    (void)0;
});
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__textRes.__sn__body)), "Hello World"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "text() should set body")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_34);
    } else {
        __sn__check(__local_arena__, rt_eq_string(((char *)rt_managed_pin(__local_arena__, __sn__textRes.__sn__body)), "Hello World"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "text() should set body"));
    }
    (void)0;
});
    RtThreadHandle *__jsonRes_pending__ = NULL;
    __sn__HttpResponse __sn__jsonRes = __sn__HttpResponse_ok(__local_arena__);
    __sn__HttpResponse_json(__local_arena__, &__sn__jsonRes, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "{\"key\": \"value\"}"));
    ({
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_35_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__jsonRes, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_35_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_35);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__jsonRes, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__jsonRes, __iarg_35_0);
    }
    __intercept_result;
})), "application/json; charset=utf-8"));
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "json() should set Content-Type")));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_36);
    } else {
        __sn__check(__local_arena__, rt_eq_string((char *)rt_managed_pin(__local_arena__, ({
    RtHandle __iarg_35_0 = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Content-Type");
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__jsonRes, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, __iarg_35_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.getHeader", __args, 2, __thunk_35);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__jsonRes, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_getHeader(__local_arena__, &__sn__jsonRes, __iarg_35_0);
    }
    __intercept_result;
})), "application/json; charset=utf-8"), rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "json() should set Content-Type"));
    }
    (void)0;
});
    rt_print_string("  Content type helpers OK\n");
    goto __sn__testContentTypes_return;
__sn__testContentTypes_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

void __sn__testSerialization(RtManagedArena *__caller_arena__) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    rt_print_string("Testing response serialization...\n");
    RtThreadHandle *__res_pending__ = NULL;
    __sn__HttpResponse __sn__res = __sn__HttpResponse_ok(__local_arena__);
    __sn__HttpResponse_text(__local_arena__, &__sn__res, rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Hello"));
    RtThreadHandle *__output_pending__ = NULL;
    RtHandle __sn__output = ({
    RtHandle __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[1];
        __args[0] = rt_box_struct(__local_arena__, (void *)&__sn__res, sizeof(__sn__HttpResponse), 1988968148);
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.toString", __args, 1, __thunk_37);
        __intercept_result = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, rt_unbox_string(__intercepted));
        memcpy((void *)&__sn__res, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_toString(__local_arena__, &__sn__res);
    }
    __intercept_result;
});
    ({
    bool __iarg_38_0 = rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__output), "HTTP/1.1 200 OK");
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(__iarg_38_0);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should contain status line"));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_38);
    } else {
        __sn__check(__local_arena__, __iarg_38_0, "Should contain status line");
    }
    (void)0;
});
    ({
    bool __iarg_39_0 = rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__output), "Content-Type: text/plain");
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(__iarg_39_0);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should contain Content-Type"));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_39);
    } else {
        __sn__check(__local_arena__, __iarg_39_0, "Should contain Content-Type");
    }
    (void)0;
});
    ({
    bool __iarg_40_0 = rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__output), "Content-Length: 5");
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(__iarg_40_0);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should contain Content-Length"));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_40);
    } else {
        __sn__check(__local_arena__, __iarg_40_0, "Should contain Content-Length");
    }
    (void)0;
});
    ({
    bool __iarg_41_0 = rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__output), "Hello");
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(__iarg_41_0);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should contain body"));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_41);
    } else {
        __sn__check(__local_arena__, __iarg_41_0, "Should contain body");
    }
    (void)0;
});
    ({
    bool __iarg_42_0 = rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__output), "\r\n\r\n");
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(__iarg_42_0);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should have header/body separator"));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("check", __args, 2, __thunk_42);
    } else {
        __sn__check(__local_arena__, __iarg_42_0, "Should have header/body separator");
    }
    (void)0;
});
    rt_print_string("  Serialization OK\n");
    goto __sn__testSerialization_return;
__sn__testSerialization_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
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
        RtAny __intercepted = rt_call_intercepted("statusText", __args, 1, __thunk_43);
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
        __sn__ResponseHeader * __arr_0__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_0__ = rt_array_length(__arr_0__);
        for (long __idx_0__ = 0; __idx_0__ < __len_0__; __idx_0__++) {
            __sn__ResponseHeader __sn__h = __arr_0__[__idx_0__];
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
        __sn__ResponseHeader * __arr_1__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_1__ = rt_array_length(__arr_1__);
        for (long __idx_1__ = 0; __idx_1__ < __len_1__; __idx_1__++) {
            __sn__ResponseHeader __sn__h = __arr_1__[__idx_1__];
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
        __sn__ResponseHeader * __arr_2__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_2__ = rt_array_length(__arr_2__);
        for (long __idx_2__ = 0; __idx_2__ < __len_2__; __idx_2__++) {
            __sn__ResponseHeader __sn__h = __arr_2__[__idx_2__];
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
    RtHandle __iarg_44_0 = rt_managed_strdup(__caller_arena__, RT_HANDLE_NULL, "Content-Length");
    bool __intercept_result;
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_struct(__caller_arena__, (void *)__sn__self, sizeof(__sn__HttpResponse), 1988968148);
        __args[1] = rt_box_string((char *)rt_managed_pin(__caller_arena__, __iarg_44_0));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __caller_arena__;
        RtAny __intercepted = rt_call_intercepted("HttpResponse.hasHeader", __args, 2, __thunk_44);
        __intercept_result = rt_unbox_bool(__intercepted);
        memcpy((void *)__sn__self, rt_unbox_struct(__args[0], 1988968148), sizeof(__sn__HttpResponse));
    } else {
        __intercept_result = __sn__HttpResponse_hasHeader(__caller_arena__, __sn__self, __iarg_44_0);
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
        __sn__ResponseHeader * __arr_3__ = ((__sn__ResponseHeader *)rt_managed_pin_array(__caller_arena__, __sn__self->__sn__headers));
        long __len_3__ = rt_array_length(__arr_3__);
        for (long __idx_3__ = 0; __idx_3__ < __len_3__; __idx_3__++) {
            __sn__ResponseHeader __sn__h = __arr_3__[__idx_3__];
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
        RtAny __intercepted = rt_call_intercepted("HttpResponse.toString", __args, 1, __thunk_45);
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


/* Interceptor thunk definitions */
static RtAny __thunk_0(void) {
    __sn__testBasicResponse((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_1(void) {
    __sn__testStatusFactories((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_2(void) {
    __sn__testHeaders((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_3(void) {
    __sn__testContentTypes((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_4(void) {
    __sn__testSerialization((RtArena *)__rt_thunk_arena);
    return rt_box_nil();
}

static RtAny __thunk_5(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_6(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
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
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_14(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_15(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_16(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_17(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_18(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_19(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_bool(__sn__HttpResponse_hasHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_20(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_21(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_22(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_23(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_24(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_25(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_26(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_27(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_bool(__sn__HttpResponse_hasHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_28(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_29(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_30(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_31(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_32(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_33(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_34(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_35(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_getHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])))));
    return __result;
}

static RtAny __thunk_36(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_37(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_toString((RtArena *)__rt_thunk_arena, __self)));
    return __result;
}

static RtAny __thunk_38(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_39(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_40(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_41(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_42(void) {
    __sn__check((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

static RtAny __thunk_43(void) {
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__statusText((RtArena *)__rt_thunk_arena, rt_unbox_int(__rt_thunk_args[0]))));
    return __result;
}

static RtAny __thunk_44(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_bool(__sn__HttpResponse_hasHeader((RtArena *)__rt_thunk_arena, __self, rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1]))));
    return __result;
}

static RtAny __thunk_45(void) {
    __sn__HttpResponse *__self = (__sn__HttpResponse *)rt_unbox_struct(__rt_thunk_args[0], 1988968148);
    RtAny __result = rt_box_string((char *)rt_managed_pin((RtArena *)__rt_thunk_arena, __sn__HttpResponse_toString((RtArena *)__rt_thunk_arena, __self)));
    return __result;
}

