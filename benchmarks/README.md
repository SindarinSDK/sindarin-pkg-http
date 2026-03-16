# HTTP Server Benchmark Results

Generated: 2026-03-16T21:43:23+00:00

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
| sindarin | 4705.00 | 3759.01 | 3825.28 | 2.38ms | 13.90ms | 4668 | 45.97 |
| c | 9386.72 | 8306.07 | 8318.59 | 1.17ms | 7.18ms | 1584 | 50.55 |
| rust | 20501.56 | 10600.45 | 9930.42 | 462.88us | 2.71ms | 18216 | 119.19 |
| go | 2025.35 | 14983.79 | 17391.45 | 3.95ms | 8.05ms | 21332 | 207.96 |
| java | 11504.53 | 21200.80 | 22179.20 | 699.81us | 1.87ms | 2269756 | 217.34 |
| csharp | 17928.00 | 59814.31 | 59114.17 | 590.68us | 3.31ms | 150236 | 421.18 |
| python | 2844.62 | 2856.74 | 2821.87 | 2.80ms | 5.49ms | 33112 | 33.18 |
| nodejs | 9045.73 | 8813.06 | 8337.72 | 0.88ms | 1.83ms | 136068 | 33.66 |

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
