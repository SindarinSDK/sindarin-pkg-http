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

/* Forward declarations */
static RtManagedArena *__main_arena__ = NULL;

void __sn__myCheck(RtManagedArena *, bool, RtHandle);

/* Interceptor thunk forward declarations */
static RtAny __thunk_0(void);

void __sn__myCheck(RtManagedArena *__caller_arena__, bool __sn__condition, RtHandle __sn__message) {
    RtManagedArena *__local_arena__ = rt_managed_arena_create_child(__caller_arena__);
    __sn__message = rt_managed_clone_any(__local_arena__, __caller_arena__, __sn__message);
    if (rt_not_bool(__sn__condition)) {
        {
            ({
        char *_str_arg0 = ({
        char *_r = rt_str_concat(__local_arena__, "FAIL: ", (char *)rt_managed_pin(__local_arena__, __sn__message));
        _r = rt_str_concat(__local_arena__, _r, "\n");
        _r;
    });
        rt_print_string(_str_arg0);
    });
        }
    }
    goto __sn__myCheck_return;
__sn__myCheck_return:
    rt_managed_arena_destroy_child(__local_arena__);
    return;
}

int main() {
    RtManagedArena *__local_arena__ = rt_managed_arena_create();
    __main_arena__ = __local_arena__;
    int _return_value = 0;
    RtThreadHandle *__text_pending__ = NULL;
    RtHandle __sn__text = rt_managed_strdup(__local_arena__, RT_HANDLE_NULL, "Hello World");
    ({
    bool __iarg_0_0 = rt_str_contains((char *)rt_managed_pin(__local_arena__, __sn__text), "Hello");
    if (__rt_interceptor_count > 0) {
        RtAny __args[2];
        __args[0] = rt_box_bool(__iarg_0_0);
        __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should contain Hello"));
        __rt_thunk_args = __args;
        __rt_thunk_arena = __local_arena__;
        RtAny __intercepted = rt_call_intercepted("myCheck", __args, 2, __thunk_0);
    } else {
        __sn__myCheck(__local_arena__, __iarg_0_0, "Should contain Hello");
    }
    (void)0;
});
    goto main_return;
main_return:
    rt_managed_arena_destroy(__local_arena__);
    return _return_value;
}


/* Interceptor thunk definitions */
static RtAny __thunk_0(void) {
    __sn__myCheck((RtArena *)__rt_thunk_arena, rt_unbox_bool(__rt_thunk_args[0]), rt_managed_strdup((RtArena *)__rt_thunk_arena, RT_HANDLE_NULL, rt_unbox_string(__rt_thunk_args[1])));
    return rt_box_nil();
}

