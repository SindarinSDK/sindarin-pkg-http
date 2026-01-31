# Sindarin Issue: Cannot Return `self` from Instance Methods

**Severity:** Medium
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

Instance methods cannot return `self` when the declared return type is the struct type. The compiler reports "Return type does not match function return type".

This breaks the common builder/fluent pattern where methods return `self` to allow method chaining.

## Minimal Reproduction

**File:** `repro_return_self.sn`

```sindarin
struct Builder =>
    value: int

    fn setValue(v: int): Builder =>
        self.value = v
        return self

fn main(): void =>
    var b: Builder = Builder { value: 0 }
    b = b.setValue(10)
    print($"value={b.value}\n")
```

**Compile:**
```bash
sn repro_return_self.sn -o repro_return_self
```

## Expected Behavior

Compiles successfully. Instance methods should be able to return `self` for method chaining.

## Actual Behavior

```
error: Return type does not match function return type
  --> repro_return_self.sn:8:1
          return self
      ^^^^^^
```

## Additional Notes

Attempting to assign `self` to a local variable first also fails:

```sindarin
fn setValue(v: int): Builder =>
    self.value = v
    var result: Builder = self
    return result
```

**Error:**
```
error: Pointer types not allowed in non-native functions, use 'as val'
error: Initializer type does not match variable type
```

This suggests `self` is internally a pointer type that doesn't match the struct type for return/assignment purposes.

## Workaround

Use `void` return type instead of returning `self`. This means no method chaining.

**Before (doesn't work):**
```sindarin
struct HttpResponse =>
    body: str

    fn setBody(content: str): HttpResponse =>
        self.body = content
        return self

fn main(): void =>
    var res: HttpResponse = HttpResponse { body: "" }
    res = res.setBody("Hello").setHeader("X-Test", "value")  # Chaining
```

**After (works):**
```sindarin
struct HttpResponse =>
    body: str

    fn setBody(content: str): void =>
        self.body = content

fn main(): void =>
    var res: HttpResponse = HttpResponse { body: "" }
    res.setBody("Hello")
    res.setHeader("X-Test", "value")  # Separate calls
```

## Impact

This affects common patterns:
- Builder pattern (fluent interfaces)
- Method chaining for configuration
- Any method that returns `self` for convenience

Affected code in HTTP module:
- `response.sn`: `setHeader()`, `addHeader()`, `setBody()`, `html()`, `text()`, `json()`
- `router.sn`: `get()`, `post()`, `put()`, `delete()`, `route()`, etc.

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
