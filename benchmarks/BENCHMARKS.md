# HTTP Server Benchmark Results

Generated: 2026-03-15T20:42:57+00:00

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
| sindarin | 193.06 | 20120.68 | 20373.08 | 41.40ms | 43.02ms | 3736 | 0 |
| c | 9576.54 | 8346.15 | 8503.74 | 1.18ms | 7.68ms | 1412 | 47.32 |
| rust | 192.77 | 19712.63 | 19937.49 | 41.48ms | 43.03ms | 23572 | 216.43 |
| go | 1909.43 | 159.28 | 168.89 | 4.20ms | 9.67ms | 20760 | 141.95 |
| java | 193.69 | 93147.14 | 97547.34 | 41.24ms | 42.07ms | 1304260 | 199.24 |
| csharp | 4834.36 | 18535.28 | 20477.86 | 1.76ms | 7.06ms | 86624 | 168.06 |
| python | 191.26 | 187.78 | 187.16 | 41.64ms | 43.16ms | 32532 | 6.38 |
| nodejs | 9011.15 | 8830.40 | 8292.42 | 0.89ms | 1.86ms | 131632 | 30.41 |

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
