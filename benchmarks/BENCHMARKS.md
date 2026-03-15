# HTTP Server Benchmark Results

Generated: 2026-03-15T18:25:11+00:00

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
| sindarin | 1382.40 | 1391.94 | 1453.21 | 78.33ms | 274.83ms | 407676 | 145.81 |
| c | 9931.22 | 8296.19 | 8381.06 | 13.93ms | 68.84ms | 10052 | 200.88 |
| rust | 1952.29 | 11228.44 | 11237.46 | 51.11ms | 68.00ms | 152976 | 568.87 |
| go | 5592.25 | 28.01 | 28.39 | 17.90ms | 33.43ms | 74176 | 1373.53 |
| java | 2519.93 | 79759.52 | 108171.40 | 38.84ms | 42.20ms | 1429004 | 713.10 |
| csharp | 2714.13 | 3128.35 | 3142.03 | 36.90ms | 65.64ms | 183908 | 465.54 |
| python | 1199.43 | 473.03 | 383.17 | 63.75ms | 120.25ms | 151672 | 136.93 |
| nodejs | 8653.67 | 8676.91 | 8383.78 | 14.95ms | 16.85ms | 236240 | 120.76 |

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
