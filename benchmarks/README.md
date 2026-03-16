# HTTP Server Benchmark Results

Generated: 2026-03-16T22:35:09+00:00

## Test Configuration

| Parameter | Value |
|-----------|-------|
| Load Testing Tool | wrk |
| Duration | 30s (interleaved GET+POST+DELETE) |
| Threads | 4 |
| Connections | 10 |
| Warmup | 3s |
| Port | 8081 |

## Server Frameworks

| Language | Framework |
|----------|-----------|
| Sindarin | sindarin-pkg-http |
| C | Raw sockets + pthreads |
| Rust | actix-web |
| Go | net/http (stdlib) |
| Java | Javalin (Jetty) |
| C# | ASP.NET Core (Kestrel) |
| Python | uvicorn + starlette |
| Node.js | http (stdlib) |

## Results Summary

| Language | GET /items (req/s) | POST /items (req/s) | DELETE /items (req/s) | Avg Latency | P99 Latency | Peak Memory (KB) | CPU Time (s) |
|----------|-------------------|--------------------|--------------------|-------------|-------------|------------------|--------------|
| sindarin | 7925.58 | 7082.85 | 7236.01 | 1.31ms | 7.53ms | 2588 | 58.46 |
| c | 9584.11 | 8451.55 | 8458.81 | 1.16ms | 7.44ms | 1424 | 51.47 |
| rust | 22929.68 | 10948.60 | 11388.92 | 393.14us | 1.95ms | 18376 | 127.43 |
| go | 14635.96 | 4330.59 | 4497.97 | 547.79us | 1.48ms | 19248 | 160.60 |
| java | 12781.60 | 23535.68 | 24326.77 | 632.01us | 1.71ms | 2284668 | 228.66 |
| csharp | 17468.84 | 62267.68 | 58667.77 | 540.63us | 2.92ms | 149992 | 424.56 |
| python | 2798.80 | 2832.33 | 2822.47 | 2.85ms | 5.61ms | 34184 | 33.08 |
| nodejs | 8861.00 | 8365.56 | 8430.25 | 0.90ms | 1.90ms | 135560 | 33.62 |

## GET /items (req/s)

```
  rust      тттттттттттттттттттттттттттттттттттттттт 22929.68 req/s
  csharp    тттттттттттттттттттттттттттттт 17468.84 req/s
  go        ттттттттттттттттттттттттт 14635.96 req/s
  java      тттттттттттттттттттттт 12781.60 req/s
  c         тттттттттттттттт 9584.11 req/s
  nodejs    ттттттттттттттт 8861.00 req/s
  sindarin  ттттттттттттт 7925.58 req/s
  python    тттт 2798.80 req/s
```

## POST /items (req/s)

```
  csharp    тттттттттттттттттттттттттттттттттттттттт 62267.68 req/s
  java      ттттттттттттттт 23535.68 req/s
  rust      ттттттт 10948.60 req/s
  c         ттттт 8451.55 req/s
  nodejs    ттттт 8365.56 req/s
  sindarin  тттт 7082.85 req/s
  go        тт 4330.59 req/s
  python    т 2832.33 req/s
```

## DELETE /items (req/s)

```
  csharp    тттттттттттттттттттттттттттттттттттттттт 58667.77 req/s
  java      тттттттттттттттт 24326.77 req/s
  rust      ттттттт 11388.92 req/s
  c         ттттт 8458.81 req/s
  nodejs    ттттт 8430.25 req/s
  sindarin  тттт 7236.01 req/s
  go        ттт 4497.97 req/s
  python    т 2822.47 req/s
```

## Peak Memory

```
  c         т 1.3 MB
  sindarin  т 2.5 MB
  rust      т 17.9 MB
  go        т 18.7 MB
  python    т 33.3 MB
  nodejs    тт 132.3 MB
  csharp    тт 146.4 MB
  java      тттттттттттттттттттттттттттттттттттттттт 2231.1 MB
```

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- All endpoints (GET, POST, DELETE) are benchmarked concurrently (interleaved)
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
