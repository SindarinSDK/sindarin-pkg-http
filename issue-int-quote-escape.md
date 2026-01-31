# Sindarin Issue: Escaped Quotes in Interpolated Strings

**Severity:** Medium
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

Escaped quotes (`\"`) inside interpolated string expressions cause parsing errors. The parser reports "Unterminated interpolated expression" when encountering escaped quotes within the `{...}` interpolation braces.

## Minimal Reproduction

**File:** `repro_interp_escape.sn`

```sindarin
fn main(): void =>
    var x: str = "hello"
    print($"Value: {x.getHeader(\"Content-Type\")}\n")
```

**Compile:**
```bash
sn repro_interp_escape.sn -o repro_interp_escape
```

## Expected Behavior

Compiles successfully. Escaped quotes inside interpolated expressions should work.

## Actual Behavior

```
error: Unterminated interpolated expression (got ')')
  --> repro_interp_escape.sn:3:1
          print($"Value: {x.getHeader(\"Content-Type\")}\n")
      ^
```

## Workaround

Extract the expression to a variable first:

```sindarin
fn main(): void =>
    var x: str = "hello"
    var result: str = x.getHeader("Content-Type")
    print($"Value: {result}\n")
```

## Impact

This affects any code that wants to:
- Call methods with string arguments inside interpolated strings
- Use string literals as parameters within `{...}` interpolation

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
