# HTTP Server Benchmark Results

Generated: 2026-02-13T23:06:55+00:00

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
| sindarin | 21568.10 | 17467.82 | 9.19 | 4.52ms | 9.56ms | 2280332 | 38.34 |
| c | 15808.78 | 18690.35 | 29656.60 | 6.28ms | 13.89ms | 12180 | 57.13 |
| rust | 30410.45 | 25132.55 | 28600.46 | 2.46ms | 4.68ms | 310580 | 70.48 |
| go | 100780.89 | 56524.35 | 72669.19 | 1.44ms | 7.73ms | 771068 | 85.89 |
| java | 2326.24 | 2357.40 | 2401.41 | 41.13ms | 43.06ms | 252024 | 22.94 |
| csharp | 59325.77 | 39352.25 | 68062.19 | 1.76ms | 6.08ms | 479108 | 75.53 |
| python | 1050.49 | 1414.14 | 971.77 | 52.71ms | 451.09ms | 57476 | 14.39 |
| nodejs | 33236.41 | 23083.43 | 31982.45 | 4.81ms | 72.89ms | 108340 | 30.79 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
