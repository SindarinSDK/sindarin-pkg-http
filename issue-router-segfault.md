# Sindarin Issue: Segfault When Calling Handler Through Imported Router

**Severity:** Critical
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

When importing a router module that contains function-typed struct fields, calling a method that invokes those function fields causes a segmentation fault at runtime. The code compiles successfully but crashes before any output is produced.

## Minimal Reproduction

**File:** `tests/test_router_minimal.sn`

```sindarin
import "../src/http/router"

fn homeHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().text("Home")

fn main(): void =>
    print("Creating router\n")
    var router: Router = Router.new()
    print("Adding route\n")
    router.get("/", homeHandler)
    print("Creating request\n")
    var req: HttpRequest = HttpRequest.parse("GET / HTTP/1.1\r\n\r\n")
    print("Handling request\n")
    var res: HttpResponse = router.handle(req)  # SEGFAULT HERE
    print("Done\n")
```

**Compile and run:**
```bash
sn tests/test_router_minimal.sn -o tests/test_router_minimal
./tests/test_router_minimal
```

## Expected Behavior

Program runs successfully and prints all messages including "Done".

## Actual Behavior

```
Segmentation fault
```

No output is produced at all (crash happens during initialization, before main() executes).

## Key Observations

1. **Import is required to trigger the bug** - A self-contained single-file version with the same logic works correctly.

2. **The crash happens before main()** - No print statements execute, suggesting the crash occurs during module initialization or static initialization of function references.

3. **Incremental testing shows**:
   - Just importing router: Works
   - Defining a handler function: Works
   - Creating Router.new(): Works
   - Adding routes with router.get(): Works
   - Calling router.handle(): CRASH

4. **The router module structure**:
   - Imports `request` and `response` modules
   - Has `Route` struct with `handler: fn(HttpRequest): HttpResponse` field
   - Has `Router` struct with `notFoundHandler` and `methodNotAllowedHandler` function fields
   - `Router.new()` initializes these with `defaultNotFoundHandler` and `defaultMethodNotAllowedHandler`

## Possibly Related

This may be related to how function references are stored in struct fields when those functions use types from imported modules. The single-file version works, but the multi-file import version crashes.

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
