# Sindarin Issue: Static Methods Cannot Access Struct Fields

**Severity:** High
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

When inside a static method, accessing fields on a local struct variable fails with "Unknown field" errors. The compiler doesn't recognize struct fields when accessed via a local variable inside a static method context.

This issue blocks common patterns like factory methods (`static fn new()`) and parser methods (`static fn parse()`).

## Minimal Reproduction

**File:** `repro_static_method.sn`

```sindarin
struct Point =>
    x: int
    y: int

    static fn create(a: int, b: int): Point =>
        var p: Point = Point { x: 0, y: 0 }
        p.x = a
        p.y = b
        return p

fn main(): void =>
    var p: Point = Point.create(10, 20)
    print($"x={p.x}, y={p.y}\n")
```

**Compile:**
```bash
sn repro_static_method.sn -o repro_static_method
```

## Expected Behavior

Compiles successfully. The static method should be able to access fields on local struct variables.

## Actual Behavior

```
error: Unknown field 'x' in struct 'Point'
  --> repro_static_method.sn:9:1
          p.x = a
      ^

error: Unknown field 'y' in struct 'Point'
  --> repro_static_method.sn:10:1
          p.y = b
      ^
```

## Workarounds

### Workaround 1: Use Regular Functions

Replace static methods with regular factory functions:

```sindarin
struct Point =>
    x: int
    y: int

fn createPoint(a: int, b: int): Point =>
    var p: Point = Point { x: 0, y: 0 }
    p.x = a
    p.y = b
    return p

fn main(): void =>
    var p: Point = createPoint(10, 20)
    print($"x={p.x}, y={p.y}\n")
```

**Status:** Works

### Workaround 2: Use Instance Methods with `self`

Instance methods can access fields via `self`:

```sindarin
struct Point =>
    x: int
    y: int

    fn setValues(a: int, b: int): void =>
        self.x = a
        self.y = b

fn main(): void =>
    var p: Point = Point { x: 0, y: 0 }
    p.setValues(10, 20)
    print($"x={p.x}, y={p.y}\n")
```

**Status:** Works

### Workaround 3: Initialize All Fields in Struct Literal

If you don't need to modify fields after creation, initialize everything in the struct literal:

```sindarin
struct Point =>
    x: int
    y: int

    static fn create(a: int, b: int): Point =>
        return Point { x: a, y: b }

fn main(): void =>
    var p: Point = Point.create(10, 20)
    print($"x={p.x}, y={p.y}\n")
```

**Status:** Works (but limited - can't do conditional logic before assignment)

## Impact

This bug affects common patterns:
- Factory methods (`static fn new()`)
- Parser methods (`static fn parse()`)
- Builder patterns
- Any static method that creates and configures struct instances

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
