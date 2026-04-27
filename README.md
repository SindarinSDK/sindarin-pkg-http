# Sindarin HTTP

A lightweight HTTP/1.1 server library for the [Sindarin](https://github.com/SindarinSDK/sindarin-compiler) programming language, providing request parsing, response building, routing, and a generic multithreaded server that works with any transport (TCP, TLS, etc.).

## Installation

Add the package as a dependency in your `sn.yaml`:

```yaml
dependencies:
- name: sindarin-pkg-http
  git: git@github.com:SindarinSDK/sindarin-pkg-http.git
  branch: main
```

Then run `sn --install` to fetch the package.

## Quick Start

```sindarin
import "http/server"
import "sindarin-pkg-sdk/src/net/tcp"

fn homeHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().html("<h1>Hello World!</h1>")

fn apiHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().json("{\"message\": \"Hello API\"}")

fn main(): void =>
    var router: Router = Router.new()
    router.get("/", homeHandler)
    router.get("/api/**", apiHandler)

    var listener: TcpListener = TcpListener.bind(":8080")
    var server: HttpServer<TcpStream> = HttpServer<TcpStream>.new(router)
    var acceptFn: fn(): TcpStream = fn(): TcpStream => listener.accept()
    server.serve(acceptFn, listener.port())
```

## Documentation

### Modules

| Module | Import | Description |
|--------|--------|-------------|
| Status | `import "http/status"` | HTTP status codes and category helpers |
| Request | `import "http/request"` | HTTP request parsing and inspection |
| Response | `import "http/response"` | HTTP response building with fluent API |
| Router | `import "http/router"` | URL routing with pattern matching |
| Stream | `import "http/stream"` | `NetStream` interface for generic transport |
| Server | `import "http/server"` | Generic multithreaded HTTP server |

### Status

Status codes and helper methods for HTTP responses.

```sindarin
import "http/status"

var code: int = STATUS_OK           // 200
var code: int = STATUS_NOT_FOUND    // 404
var text: str = HttpStatus.text(200)     // "OK"

HttpStatus.isInformational(100) // true (1xx)
HttpStatus.isSuccess(200)       // true (2xx)
HttpStatus.isRedirect(301)      // true (3xx)
HttpStatus.isClientError(404)   // true (4xx)
HttpStatus.isServerError(500)   // true (5xx)
HttpStatus.isError(400)         // true (4xx or 5xx)
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
```

#### Content Inspection

```sindarin
req.contentType()       // Content-Type header value
req.contentLength()     // Content-Length as int
req.hasBody()           // true if body is non-empty
req.isJson()            // true if Content-Type starts with application/json
req.hasQueryParam("page")
```

#### Method Helpers

```sindarin
req.isGet()
req.isPost()
req.isPut()
req.isDelete()
req.isPatch()
req.isHead()
req.isOptions()
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

#### Convenience Factories

```sindarin
HttpResponse.new(201)                // Any status code
HttpResponse.ok()                    // 200
HttpResponse.created()               // 201
HttpResponse.noContent()             // 204
HttpResponse.badRequest()            // 400
HttpResponse.unauthorized()          // 401
HttpResponse.forbidden()             // 403
HttpResponse.notFound()              // 404
HttpResponse.methodNotAllowed()      // 405
HttpResponse.internalServerError()   // 500
HttpResponse.redirect("/new-path")   // 302 with Location header
```

#### Builder Methods

```sindarin
var res: HttpResponse = HttpResponse.ok()
res.addHeader("X-Custom", "value")   // Append header
res.setBody("raw content")           // Set body directly
res.getHeader("Content-Type")        // Read header value
res.hasHeader("X-Custom")            // Check header exists
```

#### Streaming Responses

Return a streaming response when the body is large, slow, or open-ended (SSE / NDJSON / log tails). The producer is called repeatedly; each non-empty return is sent as one HTTP/1.1 chunked-transfer chunk. Return `""` to end the body. The server writes headers immediately, then drains the producer — keep-alive is preserved.

```sindarin
sync var idx: int = 0

fn streamHandler(req: HttpRequest): HttpResponse =>
    idx = 0
    return HttpResponse.stream(fn(): str =>
        if idx >= 10 =>
            return ""
        idx += 1
        return $"chunk {idx}\n"
    )
```

For Server-Sent Events, `HttpResponse.sse(producer)` is `stream()` with the right `Content-Type: text/event-stream`, `Cache-Control: no-cache`, and `X-Accel-Buffering: no` headers preset. Producers should return well-formed `data: ...\n\n` frames.

```sindarin
fn sseHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.sse(fn(): str =>
        # Wait for next event from your queue / source
        var ev: str = nextEvent()
        if ev == "" =>
            return ""
        return $"data: {ev}\n\n"
    )
```

### Router

Route requests to handlers based on method and path patterns.

```sindarin
import "http/router"

var router: Router = Router.new()
router.get("/", homeHandler)
router.post("/users", createUserHandler)
router.put("/users/*", updateUserHandler)
router.delete("/users/*", deleteUserHandler)
router.patch("/users/*", patchUserHandler)
router.head("/health", headHealthHandler)
router.options("/api/**", corsHandler)
router.all("/health", healthHandler)        // Any method
router.route("CUSTOM", "/rpc", rpcHandler)  // Arbitrary method

router.get("/users/*", getUserHandler)      // Single segment wildcard
router.get("/api/**", apiHandler)           // Multi-segment wildcard

router.setNotFoundHandler(custom404Handler)
router.setMethodNotAllowedHandler(custom405Handler)
var response: HttpResponse = router.handle(request)
```

### Server

Generic HTTP server parameterized over any `NetStream` transport (TCP, TLS, etc.).

```sindarin
import "http/server"
import "sindarin-pkg-sdk/src/net/tcp"

# Create router and listener
var router: Router = Router.new()
router.get("/", homeHandler)

var listener: TcpListener = TcpListener.bind(":8080")
var server: HttpServer<TcpStream> = HttpServer<TcpStream>.new(router)

# Serve with an accept callback
var acceptFn: fn(): TcpStream = fn(): TcpStream => listener.accept()
server.serve(acceptFn, listener.port())
```

#### HTTPS with TLS

```sindarin
import "http/server"
import "sindarin-pkg-sdk/src/net/tls"

var listener: TlsListener = TlsListener.bind(":8443", "cert.pem", "key.pem")
var server: HttpServer<TlsStream> = HttpServer<TlsStream>.new(router)
var acceptFn: fn(): TlsStream = fn(): TlsStream => listener.accept()
server.serve(acceptFn, listener.port())
```

#### Server Statistics

```sindarin
var stats: ServerStats = HttpServer<TcpStream>.stats()
stats.totalRequests
stats.activeConnections
stats.totalErrors
```

## Development

### Running Tests

```bash
make test
```

### Building Examples

```bash
make examples
```

### Available Targets

```bash
make test       # Run tests
make examples   # Build all examples
make clean      # Remove build artifacts
make help       # Show all targets
```

## Dependencies

This package depends on:

- [sindarin-pkg-sdk](https://github.com/SindarinSDK/sindarin-pkg-sdk) - TCP networking and core utilities
- [sindarin-pkg-json](https://github.com/SindarinSDK/sindarin-pkg-json) - JSON support
- [sindarin-pkg-threads](https://github.com/SindarinSDK/sindarin-pkg-threads) - Multithreading primitives
- [sindarin-pkg-test](https://github.com/SindarinSDK/sindarin-pkg-test) - Testing framework

Dependencies are automatically managed via the `sn.yaml` package manifest.

## License

MIT License - see [LICENSE](./LICENSE) for details.
