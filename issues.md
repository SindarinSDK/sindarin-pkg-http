# Known Issues

## Windows: `localhost` DNS resolution causes 2-second delay per connection

**Status**: Documented workaround available

**Symptoms**:
- Each `TcpStream.connect("localhost:port")` call takes ~2 seconds on Windows
- Total request time is dominated by connection time, not actual I/O

**Root Cause**:
Windows DNS resolver attempts IPv6 lookup for `localhost` first. When IPv6 is not properly configured (common), the lookup times out after 2 seconds before falling back to IPv4.

**Workaround**:
Use `127.0.0.1` instead of `localhost`:

```sindarin
# Slow (~2000ms per connection)
var conn: TcpStream = TcpStream.connect("localhost:8080")

# Fast (~1ms per connection)
var conn: TcpStream = TcpStream.connect("127.0.0.1:8080")
```

**Potential Fixes**:
1. Update TCP implementation to try IPv4 first on Windows
2. Add a DNS cache to avoid repeated lookups
3. Detect and prefer numeric addresses when hostname is `localhost`

**Discovered**: 2025-02-01 while testing JSON API example
