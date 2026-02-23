# HTTP Server Benchmark Results

Generated: 2026-02-23T09:38:36+00:00

## Test Configuration

| Parameter | Value |
|-----------|-------|
| Load Testing Tool | wrk |
| Duration | 10s per endpoint |
| Threads | 4 |
| Connections | 100 |
| Warmup | 3s |
| Port | 8081 |

## Results Summary

| Language | GET /items (req/s) | POST /items (req/s) | GET /items/1 (req/s) | Avg Latency | P99 Latency | Peak Memory (KB) | CPU Time (s) |
|----------|-------------------|--------------------|--------------------|-------------|-------------|------------------|--------------|
| sindarin | 48817.59 | 38577.58 | 36850.68 | 3.29ms | 11.62ms |  |  |
| c | 50579.28 | 55483.62 | 70631.86 | 2.07ms | 8.24ms | 7296 | 136.40 |
| rust | 41167.82 | 38342.67 | 41086.29 | 2.38ms | 3.35ms | 328864 | 222.88 |
| go | 217641.36 | 413586.51 | 595701.25 | 607.77us | 2.94ms | 5029272 | 350.15 |
| java | 214863.19 | 199214.32 | 207114.60 | 499.33us | 828.00us | 6666700 | 175.19 |
| csharp | 182139.89 | 98626.97 | 201620.35 | 640.52us | 2.84ms | 1150528 | 257.58 |
| python | 1020.36 | 1001.47 | 989.79 | 54.75ms | 627.94ms | 42132 | 5.53 |
| nodejs | 117523.99 | 85898.90 | 113891.11 | 0.99ms | 1.66ms | 254356 | 30.92 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
