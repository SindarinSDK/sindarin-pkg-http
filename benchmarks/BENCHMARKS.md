# HTTP Server Benchmark Results

Generated: 2026-03-16T00:16:48+00:00

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
| sindarin | 1349.11 | 1369.82 | 1440.60 | 6.24ms | 21.98ms | 6940 | 34.92 |
| c | 9098.98 | 8003.03 | 7975.19 | 1.23ms | 7.74ms | 1584 | 46.66 |
| rust | 188.20 | 4751.35 | 4753.64 | 42.48ms | 45.02ms | 6340 | 62.20 |
| go | 1993.99 | 14848.31 | 17293.65 | 4.01ms | 8.25ms | 21944 | 191.42 |
| java | 194.09 | 78564.83 | 82468.86 | 41.15ms | 42.04ms | 2774008 | 300.56 |
| csharp | 5915.08 | 19784.77 | 21928.71 | 1.45ms | 5.92ms | 86568 | 173.93 |
| python | 6837.44 | 185.81 | 188.04 | 9.10ms | 41.00ms | 43788 | 22.50 |
| nodejs | 9026.34 | 8607.68 | 8377.41 | 0.88ms | 1.85ms | 134104 | 30.45 |

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
