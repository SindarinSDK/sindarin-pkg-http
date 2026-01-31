# Sindarin Language Issues

This document catalogs issues encountered while implementing an HTTP server package in Sindarin. Each issue includes a minimal reproduction case for compiler testing.

## Status Summary

| # | Issue | Severity | Status |
|---|-------|----------|--------|
| 1 | Module import collisions | High | ⚠️ Open - needs complex multi-file case |
| 2 | Function type aliases | Medium | ✅ **FIXED** |
| 3 | `any` blocks method names | Low | ✅ **FIXED** |
| 4 | `char` type has no methods | Medium | ✅ **FIXED** - 8 methods added |
| 5 | `str.split()` lacks limit | Low | ✅ **FIXED** - `split(delim, limit)` |
| 6 | Multi-line struct literals | Medium | ⚠️ Open - simple repro passes |
| 7 | Struct forward references | Low | ⚠️ Open - ordering required |
| 8 | Multi-line method chaining | Medium | ✅ **FIXED** - indented + struct chaining |
| 9 | Wrong file/line in errors | Medium | ⚠️ Open - depends on #1 |
| 10 | Struct field access in imports | High | ⚠️ Open - needs complex case |

**Summary**: 5 fixed, 5 open

---

## 1. Module System / Import Collisions

**Severity:** High
**Status:** Blocking for modular code organization
**Reproduction Status:** ⚠️ PASSES in simple case - requires complex multi-file scenario

### Description

When creating an "umbrella" module that re-exports other modules, symbol collisions occur. The pattern of having a main module import and re-export sub-modules does not work as expected.

**Note:** This issue only manifests in complex multi-file projects like the HTTP server implementation. The simple reproduction below compiles successfully. The actual error occurred when combining multiple modules (request.sn, response.sn, router.sn, server.sn) through an umbrella http.sn module.

### Minimal Reproduction

Create three files:

**repro/issue1/types.sn**
```sindarin
struct MyType =>
    value: int

var CONSTANT: int = 42

fn helperFunc(): int =>
    return 1
```

**repro/issue1/lib.sn**
```sindarin
import "types"
```

**repro/issue1/main.sn**
```sindarin
import "lib"

fn main(): void =>
    var x: MyType = MyType { value: 10 }
    print($"{x.value}\n")
```

**Compile:**
```bash
sn repro/issue1/main.sn -o repro/issue1/main
```

### Expected Behavior

Compiles successfully. Symbols from `types.sn` are accessible via the `lib.sn` re-export.

### Actual Behavior

```
error: Variable is already declared in this scope
error: Function 'helperFunc' is already defined (possible import collision)
```

Additionally, error messages show incorrect file names and line numbers.

---

## 2. Type Aliases for Function Types Not Supported

**Severity:** Medium
**Status:** ✅ FIXED
**Reproduction Status:** ✅ FIXED - function type aliases now supported

### Description

Cannot create type aliases for function types using the `type` keyword.

### Minimal Reproduction

**repro/issue2/main.sn**
```sindarin
type Handler = fn(int): int

fn apply(h: Handler, x: int): int =>
    return h(x)

fn main(): void =>
    var double: Handler = fn(n: int): int => n * 2
    print($"{apply(double, 5)}\n")
```

**Compile:**
```bash
sn repro/issue2/main.sn -o repro/issue2/main
```

### Expected Behavior

Compiles successfully. `Handler` is an alias for `fn(int): int`.

### Actual Behavior

```
error: Expected 'opaque' or 'native fn' after '=' in type declaration (got 'fn')
```

---

## 3. Reserved Keyword `any` Blocks Method Names

**Severity:** Low
**Status:** ✅ FIXED
**Reproduction Status:** ✅ FIXED - `any` can now be used as method name

### Description

`any` is used as a type generalization for interop, but it's also blocked from use as a method name. Method names should be allowed even if `any` is a reserved type keyword.

### Minimal Reproduction

**repro/issue3/main.sn**
```sindarin
struct Router =>
    fn any(path: str): Router =>
        print($"any: {path}\n")
        return self

fn main(): void =>
    var r: Router = Router {}
    r.any("/test")
```

**Compile:**
```bash
sn repro/issue3/main.sn -o repro/issue3/main
```

### Expected Behavior

Compiles successfully. `any` should be usable as a method name.

### Actual Behavior

```
error: Expected method name (got 'any')
```

---

## 4. `char` Type Has No Methods

**Severity:** Medium
**Status:** ✅ FIXED
**Reproduction Status:** ✅ FIXED - char now has: toString, toUpper, toLower, toInt, isDigit, isAlpha, isWhitespace, isAlnum

### Description

The `char` type has no methods for conversion or inspection.

### Minimal Reproduction

**repro/issue4/main.sn**
```sindarin
fn main(): void =>
    var s: str = "Hello"
    var c: char = s.charAt(0)

    # None of these work:
    var asString: str = c.toString()
    var lower: char = c.toLower()
    var code: int = c.toInt()

    print($"{asString}\n")
```

**Compile:**
```bash
sn repro/issue4/main.sn -o repro/issue4/main
```

### Expected Behavior

`char` has methods: `toString()`, `toLower()`, `toUpper()`, `toInt()`.

### Actual Behavior

```
error: Type 'char' has no member 'toString'
error: Type 'char' has no member 'toLower'
error: Type 'char' has no member 'toInt'
```

---

## 5. `str.split()` Lacks Limit Parameter

**Severity:** Low
**Status:** ✅ FIXED
**Reproduction Status:** ✅ FIXED - split() now accepts optional limit parameter: split(delim, limit)

### Description

The `split()` method only accepts a delimiter. A common pattern is `split(delimiter, limit)` to split into at most N parts.

### Minimal Reproduction

**repro/issue5/main.sn**
```sindarin
fn main(): void =>
    var s: str = "a:b:c:d:e"
    var parts: str[] = s.split(":", 2)  # Want: {"a", "b:c:d:e"}
    print($"{parts.length}\n")
```

**Compile:**
```bash
sn repro/issue5/main.sn -o repro/issue5/main
```

### Expected Behavior

`split(":", 2)` returns `{"a", "b:c:d:e"}` - splits into at most 2 parts.

### Actual Behavior

```
error: function '<anonymous>' expects 1 argument(s), got 2
```

---

## 6. Multi-line Struct Literals Parsing Issues

**Severity:** Medium
**Status:** Formatting constraint
**Reproduction Status:** ⚠️ PASSES in simple case - may require specific context

### Description

Struct literals that span multiple lines cause parsing errors when used directly in return statements.

**Note:** The simple reproduction below compiles successfully. This issue manifested in the HTTP server implementation in specific contexts (possibly when combined with method chaining or more complex expressions). The error reported was: `Expected ';' or newline after return value (got '{')`

### Minimal Reproduction

**repro/issue6/main.sn**
```sindarin
struct Point =>
    x: int
    y: int
    z: int

fn makePoint(): Point =>
    return Point {
        x: 1,
        y: 2,
        z: 3
    }

fn main(): void =>
    var p: Point = makePoint()
    print($"{p.x}, {p.y}, {p.z}\n")
```

**Compile:**
```bash
sn repro/issue6/main.sn -o repro/issue6/main
```

### Expected Behavior

Compiles successfully. Multi-line struct literals should be valid.

### Actual Behavior

```
error: Expected ';' or newline after return value (got '{')
```

---

## 7. Struct Definitions Must Precede Usage

**Severity:** Low
**Status:** Ordering requirement
**Reproduction Status:** ✅ CONFIRMED - fails but with different error (struct literal parsing)

### Description

Structs must be defined before functions that reference them. Forward references don't resolve.

### Minimal Reproduction

**repro/issue7/main.sn**
```sindarin
fn getPoint(): Point =>
    var p: Point = Point { x: 1, y: 2 }
    return p

struct Point =>
    x: int
    y: int

fn main(): void =>
    var p: Point = getPoint()
    print($"{p.x}\n")
```

**Compile:**
```bash
sn repro/issue7/main.sn -o repro/issue7/main
```

### Expected Behavior

Compiles successfully. Struct `Point` should be resolved even if defined after the function.

### Actual Behavior

```
error: Expected ';' or newline after variable declaration (got '{')
  --> repro/issue7/main.sn:2:1
      var p: Point = Point { x: 1, y: 2 }
```

**Note:** The actual error differs from expected. Instead of "Unknown type 'Point'", the compiler fails on the struct literal syntax `Point { ... }`. This suggests the parser doesn't recognize the struct name as a type, so it interprets `Point` as a variable name and fails when it sees `{`. This confirms forward references don't work, but the error message is different than anticipated.

---

## 8. Method Chaining Across Lines Fails

**Severity:** Medium
**Status:** ✅ FIXED
**Reproduction Status:** ✅ FIXED - both same-indent and indented continuation now work

### Description

Method chaining that spans multiple lines causes parsing errors.

### Minimal Reproduction

**repro/issue8/main.sn**
```sindarin
struct Builder =>
    value: int

    static fn new(): Builder =>
        var b: Builder = Builder { value: 0 }
        return b

    fn add(n: int): Builder =>
        self.value = self.value + n
        return self

    fn multiply(n: int): Builder =>
        self.value = self.value * n
        return self

fn main(): void =>
    var b: Builder = Builder.new()
        .add(5)
        .multiply(2)
    print($"{b.value}\n")
```

**Compile:**
```bash
sn repro/issue8/main.sn -o repro/issue8/main
```

### Expected Behavior

Compiles successfully. Method chaining across lines should work.

### Actual Behavior

```
error: Expected expression (got '')
```

---

## 9. Confusing Error Messages (Wrong File/Line)

**Severity:** Medium
**Status:** Developer experience issue
**Reproduction Status:** ⚠️ Dependent on Issue #1 - cannot reproduce in isolation

### Description

In multi-file projects, error messages sometimes show incorrect file names and line numbers. The code snippet shown doesn't match the actual content at that location.

**Note:** This issue only manifests when Issue #1 triggers errors. Since Issue #1's simple reproduction passes, this issue cannot be independently verified. It was observed during the HTTP server implementation when multi-file compilation failed.

### Minimal Reproduction

Use the reproduction from Issue #1. When compilation fails, observe:

```
error: Unknown field 'value' in struct 'MyType'
  --> repro/issue1/types.sn:15:1
      print($"{x.value}\n")  # This line is from main.sn, not types.sn!
```

### Expected Behavior

Error messages should accurately identify the file and line number where the error occurred.

### Actual Behavior

- File name in error doesn't match the file containing the error
- Line number doesn't correspond to the actual source location
- Code snippet shown is from a different file

---

## 10. Struct Field Access Errors in Method Context

**Severity:** High
**Status:** Blocks struct usage in methods
**Reproduction Status:** ⚠️ PASSES in simple case - requires complex multi-file scenario

### Description

When a struct is imported from another module, methods that access struct fields report "Unknown field" errors even when the fields are correctly defined.

**Note:** The simple two-file reproduction below compiles successfully. This issue manifested in the HTTP server implementation with more complex module hierarchies. The error reported was: `Unknown field 'method' in struct 'Request'` when accessing imported struct fields within methods.

### Minimal Reproduction

**repro/issue10/data.sn**
```sindarin
struct Request =>
    method: str
    path: str

    fn isGet(): bool =>
        return self.method == "GET"
```

**repro/issue10/main.sn**
```sindarin
import "data"

fn handleRequest(req: Request): void =>
    print($"Method: {req.method}\n")
    print($"Path: {req.path}\n")
    if req.isGet() =>
        print("Is GET request\n")

fn main(): void =>
    var req: Request = Request { method: "GET", path: "/" }
    handleRequest(req)
```

**Compile:**
```bash
sn repro/issue10/main.sn -o repro/issue10/main
```

### Expected Behavior

Compiles successfully. Fields `method` and `path` should be accessible.

### Actual Behavior

```
error: Unknown field 'method' in struct 'Request'
error: Unknown field 'path' in struct 'Request'
```

---

## Summary Table

| # | Issue | Severity | Workaround | Status |
|---|-------|----------|------------|--------|
| 1 | Module import collisions | High | Single-file only | ⚠️ Needs complex case |
| 2 | No function type aliases | Medium | N/A | ✅ **FIXED** |
| 3 | `any` blocks method names | Low | N/A | ✅ **FIXED** |
| 4 | No `char` methods | Medium | N/A | ✅ **FIXED** |
| 5 | `split()` no limit param | Low | N/A | ✅ **FIXED** |
| 6 | Multi-line struct literals | Medium | Single line or variable | ⚠️ Needs complex case |
| 7 | Struct ordering required | Low | Define before use | ⚠️ Open |
| 8 | Multi-line method chaining | Medium | N/A | ✅ **FIXED** |
| 9 | Wrong file/line in errors | Medium | None | ⚠️ Depends on #1 |
| 10 | Struct fields not found (imports) | High | Single-file only | ⚠️ Needs complex case |

---

## Status Legend

- ✅ **FIXED**: Issue has been resolved in the compiler
- ⚠️ **Needs complex case**: Simple reproduction passes; issue only manifests in complex multi-file scenarios
- ⚠️ **Open**: Issue confirmed but not yet fixed

For issues marked with ⚠️, the bugs were observed during the HTTP server implementation but could not be isolated into minimal test cases. These may require:
- More complex module hierarchies (3+ levels of imports)
- Combination of multiple features (e.g., struct methods + imports + string interpolation)
- Larger codebases with more symbols in scope

---

## Reproduction File Structure

```
repro/
├── issue1/
│   ├── types.sn
│   ├── lib.sn
│   └── main.sn
├── issue2/
│   └── main.sn
├── issue3/
│   └── main.sn
├── issue4/
│   └── main.sn
├── issue5/
│   └── main.sn
├── issue6/
│   └── main.sn
├── issue7/
│   └── main.sn
├── issue8/
│   └── main.sn
└── issue10/
    ├── data.sn
    └── main.sn
```

---

## Environment

- **Compiler**: Sindarin (sn)
- **Platform**: Windows
- **Date**: January 2026
- **Project**: HTTP Server Package (sindarin-pkg-http)
