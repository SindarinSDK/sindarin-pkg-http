# Sindarin HTTP

A lightweight HTTP/1.1 server library for the [Sindarin](https://github.com/SindarinSDK/sindarin-compiler) programming language, providing request parsing, response building, routing, and multithreaded server capabilities.

## Installation

Add the package as a dependency in your `sn.yaml`:

```yaml
dependencies:
- name: sindarin-pkg-http
  git: git@github.com:SindarinSDK/sindarin-pkg-http.git
  branch: main
```

Then run `sn pkg install` to fetch the package.

## Quick Start

```sindarin
import "http/server"
import "http/router"

fn homeHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().html("<h1>Hello World!</h1>")

fn apiHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().json("{\"message\": \"Hello API\"}")

fn main(): void =>
    var router: Router = Router.new()
    router.get("/", homeHandler)
    router.get("/api/**", apiHandler)

    var server: HttpServer = HttpServer.new(router)
    server.listen(8080)
```

Or use the quick-start helper for simple servers:

```sindarin
import "http/server"

fn handler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().text($"Hello! You requested: {req.path}")

fn main(): void =>
    serve(8080, handler)
```

## Documentation

### Modules

| Module | Import | Description |
|--------|--------|-------------|
| Status | `import "http/status"` | HTTP status codes and category helpers |
| Request | `import "http/request"` | HTTP request parsing and inspection |
| Response | `import "http/response"` | HTTP response building with fluent API |
| Router | `import "http/router"` | URL routing with pattern matching |
| Server | `import "http/server"` | Multithreaded TCP server |

### Status

Status codes and helper functions for HTTP responses.

```sindarin
import "http/status"

var code: int = STATUS_OK           // 200
var code: int = STATUS_NOT_FOUND    // 404
var text: str = statusText(200)     // "OK"

isSuccess(200)      // true
isClientError(404)  // true
isServerError(500)  // true
isError(400)        // true (4xx or 5xx)
```

### Request

Parse and inspect incoming HTTP requests.

```sindarin
import "http/request"

var req: HttpRequest = HttpRequest.parse(rawData)

req.method          // "GET", "POST", etc.
req.path            // "/users/123"
req.query           // "page=1&limit=10"
req.body            // Request body content

req.getHeader("Content-Type")
req.hasHeader("Authorization")
req.queryParam("page")
req.isGet()
req.isPost()
```

### Response

Build HTTP responses with a fluent API.

```sindarin
import "http/response"

var res: HttpResponse = HttpResponse.ok()
res.text("Hello World")              // text/plain
res.html("<h1>Hello</h1>")           // text/html
res.json("{\"key\": \"value\"}")     // application/json

res.setHeader("X-Custom", "value")
var output: str = res.toString()
```

### Router

Route requests to handlers based on method and path patterns.

```sindarin
import "http/router"

var router: Router = Router.new()
router.get("/", homeHandler)
router.post("/users", createUserHandler)
router.get("/users/*", getUserHandler)      // Single segment wildcard
router.get("/api/**", apiHandler)           // Multi-segment wildcard
router.all("/health", healthHandler)        // Any method

router.setNotFoundHandler(custom404Handler)
var response: HttpResponse = router.handle(request)
```

### Server

Full HTTP server with TCP networking and statistics.

```sindarin
import "http/server"

var server: HttpServer = HttpServer.new(router)
server.setHost("0.0.0.0")
server.setPort(8080)
server.setMaxRequestSize(1048576)  // 1MB
server.listen(8080)

var stats: ServerStats = getStats()
stats.totalRequests
stats.activeConnections
```

## Running Tests

To run the test suite:

```bash
make test
```

This will compile and run all tests with parallel execution. Use `make help` to see all available targets.

## Dependencies

This package depends on [sindarin-pkg-sdk](https://github.com/SindarinSDK/sindarin-pkg-sdk) for TCP networking. Dependencies are automatically managed via the `sn.yaml` package manifest.

## License

MIT License - see [LICENSE](./LICENSE) for details.
