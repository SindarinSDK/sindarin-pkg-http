# HTTP Server Benchmark Results

Generated: 2026-02-13T14:03:09+00:00

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
| sindarin | 17672.54 | 13751.62 | 10.29 | 5.61ms | 14.35ms | 2631792 | 71.80 |
| c | 10972.22 | 12761.42 | 19268.19 | 9.17ms | 23.66ms | 12432 | 42.89 |
| rust | 19630.52 | 16150.96 | 22447.50 | 3.86ms | 10.92ms | 196624 | 50.50 |
| go | 100752.44 | 54317.03 | 71618.12 | 1.55ms | 8.77ms | 742400 | 85.91 |
| java | 2306.12 | 2380.27 | 2425.17 | 41.15ms | 43.10ms | 243652 | 23.06 |
| csharp | 51357.71 | 30572.08 | 58135.01 | 2.12ms | 8.63ms | 393888 | 65.65 |
| python | 1612.11 | 1017.79 | 899.37 | 56.93ms | 673.41ms | 39552 | 14.17 |
| nodejs | 32364.79 | 23201.79 | 32068.87 | 4.73ms | 60.70ms | 108516 | 30.75 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
