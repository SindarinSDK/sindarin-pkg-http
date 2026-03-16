# HTTP Server Benchmark Results

Generated: 2026-03-16T21:58:43+00:00

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
| sindarin | 4658.42 | 3787.98 | 3876.87 | 2.36ms | 13.73ms | 3388 | 46.72 |
| c | 9164.18 | 7914.05 | 8068.90 | 1.24ms | 8.01ms | 1584 | 49.94 |
| rust | 13274.03 | 8506.89 | 9596.98 | 833.25us | 5.32ms | 18344 | 92.13 |
| go | 14973.99 | 4396.70 | 4553.76 | 537.12us | 1.47ms | 18920 | 159.66 |
| java | 12592.56 | 23132.17 | 24005.45 | 639.39us | 1.73ms | 2296360 | 226.56 |
| csharp | 19182.39 | 59196.60 | 67586.81 | 501.66us | 2.77ms | 151184 | 424.68 |
| python | 3027.79 | 3061.52 | 2978.25 | 2.63ms | 4.28ms | 33668 | 33.08 |
| nodejs | 9016.52 | 8839.26 | 8540.86 | 0.88ms | 1.85ms | 136632 | 33.72 |

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
