# HTTP Server Benchmark Results

Generated: 2026-02-13T10:26:12+00:00

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
| sindarin | 13472.25 | 12339.21 | 18543.34 | 7.34ms | 14.84ms | 1912 | 0 |
| c | 18237.64 | 15477.61 | 17211.13 | 5.53ms | 12.91ms | 9072 | 42.21 |
| rust | 70099.08 | 40597.05 | 53531.00 | 2.14ms | 11.35ms | 175416 | 46.39 |
| go | 2346.45 | 2363.20 | 2420.39 | 41.16ms | 43.99ms | 535104 | 64.61 |
| java | 1212.69 | 1214.67 | 1218.38 | 41.12ms | 43.57ms | 242452 | 9.79 |
| csharp | 1107.06 | 1055.31 | 1033.18 | 54.82ms | 640.70ms | 3944 | 0 |
| python | 28742.63 | 19525.11 | 26623.23 | 5.08ms | 47.67ms | 41864 | 5.26 |
| nodejs | 27934.65 | 18850.04 | 25623.41 | 2.06ms | 5.79ms | 103020 | 29.90 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
