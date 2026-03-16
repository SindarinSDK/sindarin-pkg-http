# HTTP Server Benchmark Results

Generated: 2026-03-16T00:42:54+00:00

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
| sindarin | 9488.50 | 8084.03 | 8129.94 | 1.15ms | 7.01ms | 1908 | 54.37 |
| c | 10061.42 | 9014.23 | 9065.01 | 1.09ms | 6.88ms | 1584 | 48.91 |
| rust | 191.96 | 6562.42 | 3339.85 | 41.64ms | 43.06ms | 5700 | 64.70 |
| go | 2130.18 | 14335.25 | 16761.71 | 3.76ms | 7.86ms | 20924 | 188.93 |
| java | 193.99 | 79376.06 | 83332.29 | 41.10ms | 42.03ms | 2182092 | 295.47 |
| csharp | 5464.09 | 18957.59 | 20955.16 | 1.55ms | 5.96ms | 86408 | 169.61 |
| python | 190.94 | 191.96 | 186.95 | 41.36ms | 43.31ms | 49056 | 9.39 |
| nodejs | 8924.80 | 8263.85 | 8144.75 | 0.90ms | 1.92ms | 130676 | 30.45 |

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
