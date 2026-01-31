# Sindarin Issue: Import Collisions in Multi-File Projects

**Severity:** Critical
**Status:** Open
**Discovered:** During HTTP server implementation

## Description

When a project has multiple files that import each other in a diamond or chain pattern, symbols from shared dependencies are duplicated, causing "Variable is already declared" and "Function is already defined (possible import collision)" errors.

## Minimal Reproduction

The HTTP server module structure triggers this issue:

```
test_server.sn
    └── imports server.sn
            ├── imports tcp.sn
            ├── imports request.sn
            ├── imports response.sn
            │       └── imports status.sn
            └── imports router.sn
                    ├── imports request.sn
                    └── imports response.sn
                            └── imports status.sn  (DUPLICATE!)
```

**File:** `tests/test_server.sn`

```sindarin
import "../src/http/server"

fn homeHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().text("Hello!")

fn main(): void =>
    var router: Router = Router.new()
    router.get("/", homeHandler)
    var server: HttpServer = HttpServer.new(router)
    server.listen(8080)
```

**Compile:**
```bash
sn tests/test_server.sn -o tests/test_server
```

## Expected Behavior

Compiles successfully. Each module should only be included once regardless of how many times it's imported through different paths.

## Actual Behavior

```
error: Variable is already declared in this scope
  --> tests/../src/http/status.sn:15:1

error: Function 'statusText' is already defined (possible import collision)
  --> tests/../src/http/status.sn:71:1

error: Function 'isInformational' is already defined (possible import collision)
  --> tests/../src/http/status.sn:124:1

... (44 total errors)
```

## Analysis

The compiler appears to process imports without deduplication. When `status.sn` is reached through multiple import paths:
1. `server.sn` → `response.sn` → `status.sn`
2. `server.sn` → `router.sn` → `response.sn` → `status.sn`

The symbols from `status.sn` are included twice, causing redefinition errors.

## Import Dependency Chain

```
server.sn
├── tcp.sn (SDK)
├── request.sn
├── response.sn
│   └── status.sn
└── router.sn
    ├── request.sn (duplicate)
    └── response.sn (duplicate)
        └── status.sn (duplicate)
```

## Workaround

Currently none known for complex multi-file projects. Options attempted:
1. ❌ Importing files individually - still causes collisions
2. ❌ Removing umbrella module - still causes collisions through dependency chains
3. ⚠️ Single-file implementation - works but impractical for larger projects

## Impact

This blocks any project with:
- Diamond dependency patterns (A imports B and C, both B and C import D)
- Deep import chains where files are reachable through multiple paths
- Modular code organization with shared utility modules

Specifically blocks:
- The HTTP server module (server.sn cannot be imported)
- Any project with layered architecture
- Reusable library packages

## Environment

- **Compiler:** Sindarin (sn)
- **Platform:** Windows
- **Date:** January 2026
