# HTTP Server Benchmark Results

Generated: 2026-03-16T20:36:47+00:00

## Test Configuration

| Parameter | Value |
|-----------|-------|
| Load Testing Tool | wrk |
| Duration | 30s (interleaved GET+POST+DELETE) |
| Threads | 4 |
| Connections | 10 |
| Warmup | 3s |
| Port | 8081 |

## Results Summary

| Language | GET /items (req/s) | POST /items (req/s) | DELETE /items (req/s) | Avg Latency | P99 Latency | Peak Memory (KB) | CPU Time (s) |
|----------|-------------------|--------------------|--------------------|-------------|-------------|------------------|--------------|
| sindarin | 4694.29 | 3908.42 | 3983.96 | 2.29ms | 13.04ms | 3548 | 43.46 |
| c | 10095.06 | 9005.28 | 9053.08 | 1.06ms | 6.45ms | 1584 | 49.00 |
| rust | 188.00 | 4750.15 | 4755.39 | 42.51ms | 45.02ms | 6840 | 63.36 |
| go | 2092.75 | 14626.10 | 17066.98 | 3.82ms | 8.01ms | 22300 | 191.18 |
| java | 194.31 | 79641.82 | 83618.70 | 41.14ms | 42.04ms | 2189104 | 293.51 |
| csharp | 5851.22 | 19613.63 | 21660.13 | 1.45ms | 5.66ms | 84632 | 170.69 |
| python | 10751.28 | 186.13 | 187.27 | 8.16ms | 8.16ms
40.97ms | 44588 | 32.80 |
| nodejs | 8537.65 | 8400.59 | 8126.47 | 0.94ms | 2.02ms | 133600 | 30.45 |

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
