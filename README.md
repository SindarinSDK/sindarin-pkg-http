# sindarin-pkg-http

A lightweight HTTP/1.1 server library for the [Sindarin](https://github.com/SindarinLang/sindarin) programming language.

## Features

- HTTP/1.1 request parsing and response building
- Flexible routing with pattern matching
- Support for all standard HTTP methods (GET, POST, PUT, DELETE, PATCH, HEAD, OPTIONS)
- Wildcard routes (`*` and `**`)
- Builder pattern for responses
- Multithreaded request handling
- Thread-safe server statistics

## Installation

Add to your `sn.yaml`:

```yaml
dependencies:
- name: sindarin-pkg-http
  git: https://github.com/SindarinSDK/sindarin-pkg-http.git
  branch: main
```

Then run:

```bash
sn install
```

## Quick Start

```sindarin
import "server"
import "router"

fn homeHandler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().html("<h1>Hello World!</h1>")

fn main(): void =>
    var router: Router = Router.new()
    router.get("/", homeHandler)

    var server: HttpServer = HttpServer.new(router)
    server.listen(8080)
```

Or use the quick-start helper:

```sindarin
import "server"

fn handler(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().text($"Hello! You requested: {req.path}")

fn main(): void =>
    serve(8080, handler)
```

## Modules

### status

HTTP status codes and helper functions.

```sindarin
import "status"

# Status code constants
var code: int = STATUS_OK           # 200
var code: int = STATUS_NOT_FOUND    # 404

# Get status text
var text: str = statusText(200)     # "OK"

# Category helpers
isSuccess(200)      # true
isClientError(404)  # true
isServerError(500)  # true
isError(400)        # true (4xx or 5xx)
```

### request

Parse and inspect HTTP requests.

```sindarin
import "request"

var req: HttpRequest = HttpRequest.parse(rawData)

# Access request properties
req.method          # "GET", "POST", etc.
req.path            # "/users/123"
req.query           # "page=1&limit=10"
req.version         # "HTTP/1.1"
req.body            # Request body content

# Headers
req.getHeader("Content-Type")
req.hasHeader("Authorization")
req.contentType()
req.contentLength()

# Query parameters
req.queryParam("page")      # "1"
req.hasQueryParam("limit")  # true

# Method helpers
req.isGet()
req.isPost()
req.isPut()
req.isDelete()
```

### response

Build HTTP responses with a fluent API.

```sindarin
import "response"

# Factory methods
var res: HttpResponse = HttpResponse.ok()           # 200
var res: HttpResponse = HttpResponse.created()      # 201
var res: HttpResponse = HttpResponse.notFound()     # 404
var res: HttpResponse = HttpResponse.new(418)       # Custom status

# Set content with appropriate Content-Type
res.text("Hello World")              # text/plain
res.html("<h1>Hello</h1>")          # text/html
res.json("{\"message\": \"hi\"}")   # application/json

# Headers
res.setHeader("X-Custom", "value")
res.addHeader("Set-Cookie", "session=abc")

# Redirects
var redirect: HttpResponse = HttpResponse.redirect("/new-location")

# Serialize
var httpString: str = res.toString()
var httpBytes: byte[] = res.toBytes()
```

### router

Route requests to handlers.

```sindarin
import "router"

var router: Router = Router.new()

# Register routes by method
router.get("/", homeHandler)
router.post("/users", createUserHandler)
router.put("/users/*", updateUserHandler)
router.delete("/users/*", deleteUserHandler)

# Match any method
router.all("/api/**", apiHandler)

# Pattern matching:
#   /users       - exact match
#   /users/*     - matches one path segment (/users/123)
#   /users/**    - matches any path starting with /users/

# Custom error handlers
router.setNotFoundHandler(custom404Handler)
router.setMethodNotAllowedHandler(custom405Handler)

# Route a request
var response: HttpResponse = router.handle(request)
```

### server

Full HTTP server with TCP networking.

```sindarin
import "server"

var server: HttpServer = HttpServer.new(router)

# Configuration
server.setHost("0.0.0.0")
server.setPort(8080)
server.setMaxRequestSize(1048576)  # 1MB

# Start server (blocking)
server.listen(8080)

# Server statistics
var stats: ServerStats = getStats()
stats.totalRequests
stats.activeConnections
stats.totalErrors
```

## Examples

### RESTful API

```sindarin
import "server"
import "router"

fn getUsers(req: HttpRequest): HttpResponse =>
    return HttpResponse.ok().json("[{\"id\": 1, \"name\": \"Alice\"}]")

fn getUser(req: HttpRequest): HttpResponse =>
    # Extract ID from path (e.g., /users/123)
    var id: str = req.path.substring(7, req.path.length)
    return HttpResponse.ok().json($"{{\"id\": {id}}}")

fn createUser(req: HttpRequest): HttpResponse =>
    # req.body contains the JSON payload
    return HttpResponse.created().json("{\"id\": 2, \"created\": true}")

fn main(): void =>
    var router: Router = Router.new()
    router.get("/users", getUsers)
    router.get("/users/*", getUser)
    router.post("/users", createUser)

    print("API server starting on http://localhost:3000\n")
    serveRouter(3000, router)
```

### Static File Server

```sindarin
import "server"
import "router"

fn serveFile(req: HttpRequest): HttpResponse =>
    var path: str = req.path
    if path == "/" =>
        path = "/index.html"

    # Read file and serve (pseudo-code)
    # var content: str = TextFile.readAll("public" + path)
    # return HttpResponse.ok().html(content)

    return HttpResponse.notFound().text("File not found")

fn main(): void =>
    var router: Router = Router.new()
    router.get("/**", serveFile)
    serveRouter(8080, router)
```

## Development

### Building

```bash
make test    # Run all tests
make clean   # Remove build artifacts
```

### Running Examples

```bash
sn examples/hello_server.sn -o bin/hello_server
./bin/hello_server
# Server runs at http://localhost:8080
```

## Project Structure

```
sindarin-pkg-http/
├── src/
│   ├── status.sn      # HTTP status codes
│   ├── request.sn     # Request parsing
│   ├── response.sn    # Response building
│   ├── router.sn      # URL routing
│   └── server.sn      # TCP server
├── tests/
│   ├── test_status.sn
│   ├── test_request.sn
│   ├── test_response.sn
│   └── test_router.sn
├── examples/
│   ├── hello_server.sn
│   └── server_integration.sn
├── sn.yaml
├── Makefile
└── README.md
```

## License

MIT
