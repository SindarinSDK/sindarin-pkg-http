# Sindarin Issue: Cannot Call Function-Typed Struct Fields

**Severity:** High
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

When a struct has a field with a function type, attempting to call that function through the field fails at the C compilation stage. The generated C code treats the closure pointer as if it were directly callable, but it's actually a `__Closure__ *` that requires special invocation.

## Minimal Reproduction

**File:** `repro_fn_field.sn`

```sindarin
struct Handler =>
    callback: fn(int): int

fn multiply(x: int): int =>
    return x * 2

fn main(): void =>
    var h: Handler = Handler { callback: multiply }
    var result: int = h.callback(5)
    print($"Result: {result}\n")
```

**Compile:**
```bash
sn repro_fn_field.sn -o repro_fn_field
```

## Expected Behavior

Compiles and runs successfully, printing `Result: 10`.

## Actual Behavior

```
repro_fn_field.c:45:52: error: called object type '__Closure__ *' (aka 'struct __Closure__ *') is not a function or function pointer
   45 |     long long __sn__result = __sn__h.__sn__callback(5LL);
      |                              ~~~~~~~~~~~~~~~~~~~~~~^
1 error generated.
```

## Analysis

The generated C code attempts to call the closure directly:
```c
__sn__h.__sn__callback(5LL)
```

But `__sn__callback` is of type `__Closure__ *`, which is a pointer to a closure struct, not a function pointer. Closures need to be invoked through the runtime's closure invocation mechanism.

## Impact

This blocks any pattern that stores callbacks or handlers in structs, including:

- **Router pattern**: Storing route handlers `fn(HttpRequest): HttpResponse`
- **Event handlers**: Storing callbacks for events
- **Strategy pattern**: Storing interchangeable algorithms
- **Middleware**: Storing processing functions

Affected code in HTTP module:
- `router.sn`: `Route.handler`, `Router.notFoundHandler`, `Router.methodNotAllowedHandler`
- `server.sn`: Any callback-based patterns

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
