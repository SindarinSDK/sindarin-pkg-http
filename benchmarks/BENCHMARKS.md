# HTTP Server Benchmark Results

Generated: 2026-03-15T21:30:16+00:00

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
| sindarin | 1886.15 | 1887.96 | 1939.77 | 4.67ms | 18.95ms | 134904 | 36.50 |
| c | 8868.84 | 7507.74 | 7668.04 | 1.33ms | 8.87ms | 1412 | 45.16 |
| rust | 192.66 | 19406.20 | 19684.77 | 41.49ms | 43.04ms | 27868 | 215.45 |
| go | 1913.12 | 156.50 | 161.03 | 4.19ms | 9.64ms | 19784 | 141.38 |
| java | 193.86 | 92710.21 | 97163.29 | 41.24ms | 42.10ms | 1288412 | 198.62 |
| csharp | 5456.60 | 19276.13 | 21311.43 | 1.58ms | 6.57ms | 86004 | 171.96 |
| python | 1379.76 | 186.53 | 184.59 | 11.09ms | 44.03ms | 42828 | 30.14 |
| nodejs | 8919.52 | 8536.16 | 8185.24 | 0.90ms | 1.95ms | 134196 | 30.47 |

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
