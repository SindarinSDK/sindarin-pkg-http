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
    __Closure__ * __sn__callback;
} __sn__Handler;

/* Forward declarations */
static RtManagedArena *__main_arena__ = NULL;

long long __sn__multiply(RtManagedArena *, long long);

long long __sn__multiply(RtManagedArena *__caller_arena__, long long __sn__x) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    long long _return_value = 0;
    _return_value = rt_mul_long(__sn__x, 2LL);
    goto __sn__multiply_return;
__sn__multiply_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return _return_value;
}

int main() {
    RtManagedArena *__local_arena__ = rt_managed_arena_create();
    __main_arena__ = __local_arena__;
    int _return_value = 0;
    RtThreadHandle *__h_pending__ = NULL;
    __sn__Handler __sn__h = (__sn__Handler){ .__sn__callback = __sn__multiply };
    RtThreadHandle *__result_pending__ = NULL;
    long long __sn__result = __sn__h.__sn__callback(5LL);
    ({
        char *_str_arg0 = ({
        char *_p0 = rt_to_string_long(__local_arena__, __sn__result);
        char *_r = rt_str_concat(__local_arena__, "Result: ", _p0);
        _r = rt_str_concat(__local_arena__, _r, "\n");
        _r;
    });
        rt_print_string(_str_arg0);
    });
    goto main_return;
main_return:
    rt_managed_arena_destroy(__local_arena__);
    return _return_value;
}

