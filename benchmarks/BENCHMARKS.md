# HTTP Server Benchmark Results

Generated: 2026-03-15T17:17:13+00:00

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
| sindarin | 161.53 | 176.73 | 195.15 | 605.82ms | 1.38s | 78072 | 132.77 |
| c | 3323.34 | 3524.09 | 3609.18 | 40.88ms | 205.90ms | 9904 | 150.70 |
| rust | 147.07 | 172.08 | 156.63 | 674.08ms | 1.42s | 302264 | 142.95 |
| go | 4677.83 | 23.99 | 23.32 | 21.66ms | 52.17ms | 110688 | 1428.75 |
| java | 178.40 | 10550.50 | 9216.32 | 563.17ms | 1.68s |  |  |
| csharp | 193.24 | 244.25 | 246.43 | 523.43ms | 1.29s | 18487880 | 588.23 |
| python | 336.40 | 163.45 | 263.28 | 282.87ms | 879.20ms | 212884 | 121.58 |
| nodejs | 390.13 | 307.25 | 271.49 | 268.16ms | 648.55ms | 349384 | 124.70 |

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
