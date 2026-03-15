# HTTP Server Benchmark Results

Generated: 2026-03-15T18:52:56+00:00

## Test Configuration

| Parameter | Value |
|-----------|-------|
| Load Testing Tool | wrk |
| Duration | 120s (interleaved GET+POST+DELETE) |
| Threads | 4 |
| Connections | 100 |
| Warmup | 3s |
| Port | 8081 |

## Results Summary

| Language | GET /items (req/s) | POST /items (req/s) | DELETE /items (req/s) | Avg Latency | P99 Latency | Peak Memory (KB) | CPU Time (s) |
|----------|-------------------|--------------------|--------------------|-------------|-------------|------------------|--------------|
| sindarin | 1377.99 | 1369.24 | 1447.48 | 78.78ms | 279.24ms | 402136 | 145.63 |
| c | 9975.97 | 8330.46 | 8411.39 | 13.80ms | 67.79ms | 9904 | 201.70 |
| rust | 1951.53 | 11000.76 | 11173.59 | 51.16ms | 67.01ms | 142808 | 563.27 |
| go | 6583.05 | 37.09 | 41.51 | 15.22ms | 29.50ms | 72420 | 1326.68 |
| java | 2584.24 | 91925.49 | 99956.15 | 37.73ms | 42.26ms | 1810828 | 740.89 |
| csharp | 2740.72 | 3158.17 | 3170.65 | 36.53ms | 65.36ms | 183316 | 458.25 |
| python | 993.34 | 1656.26 | 810.38 | 25.09ms | 91.03ms | 103892 | 143.40 |
| nodejs | 8478.40 | 8334.64 | 8299.02 | 14.23ms | 15.66ms | 238548 | 120.76 |

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
