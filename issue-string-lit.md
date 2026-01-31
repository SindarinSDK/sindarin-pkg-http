# Sindarin Issue: String Literal Codegen Failure with Method Call Arguments

**Severity:** High
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

When a function is called with a method call result as one argument and a string literal as another argument, the string literal is not properly converted to `RtHandle` in the generated C code. The C compiler receives a raw `char[]` where it expects `RtHandle`.

## Minimal Reproduction

**File:** `repro_string_codegen.sn`

```sindarin
fn myCheck(condition: bool, message: str): void =>
    if !condition =>
        print($"FAIL: {message}\n")

fn main(): void =>
    var text: str = "Hello World"
    myCheck(text.contains("Hello"), "Should contain Hello")
```

**Compile:**
```bash
sn repro_string_codegen.sn -o repro_string_codegen
```

## Expected Behavior

Compiles successfully. String literals should be properly converted to managed strings in all contexts.

## Actual Behavior

```
repro_string_codegen.c:58:75: error: incompatible pointer to integer conversion passing 'char[21]' to parameter of type 'RtHandle' (aka 'unsigned int') [-Wint-conversion]
   58 |         __args[1] = rt_box_string((char *)rt_managed_pin(__local_arena__, "Should contain Hello"));
      |                                                                           ^~~~~~~~~~~~~~~~~~~~~~
C:\Users\gavin\.sn\bin\..\lib\sindarin\include/runtime/arena/managed_arena.h:232:51: note: passing argument to parameter 'h' here
  232 | void *rt_managed_pin(RtManagedArena *ma, RtHandle h);
      |                                                   ^
repro_string_codegen.c:63:52: error: incompatible pointer to integer conversion passing 'char[21]' to parameter of type 'RtHandle' (aka 'unsigned int') [-Wint-conversion]
   63 |         __sn__myCheck(__local_arena__, __iarg_0_0, "Should contain Hello");
      |                                                    ^~~~~~~~~~~~~~~~~~~~~~
```

## Analysis

The generated C code passes the string literal directly instead of wrapping it with `rt_managed_strdup()` or similar. This appears to happen specifically when:

1. A function call has multiple arguments
2. One argument is a method call result (e.g., `text.contains(...)`)
3. Another argument is a string literal

## Workaround

Assign the string literal to a variable first:

```sindarin
fn main(): void =>
    var text: str = "Hello World"
    var msg: str = "Should contain Hello"
    myCheck(text.contains("Hello"), msg)
```

## Impact

This affects any test or utility code that uses patterns like:
- `check(expr.method(), "message")`
- `assert(condition, "description")`
- `log(obj.getValue(), "context")`

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
