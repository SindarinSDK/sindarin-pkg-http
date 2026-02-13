# HTTP Server Benchmark Results

Generated: 2026-02-13T13:15:19+00:00

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
| sindarin | 20053.59 | 18299.81 | 0.00 | 4.90ms | 10.98ms |  |  |
| c | 16535.55 | 19483.57 | 29777.08 | 5.99ms | 13.83ms |  |  |
| rust | 31184.95 | 26109.38 | 28910.75 | 2.38ms | 4.27ms |  |  |
| go | 102483.42 | 56171.72 | 73043.22 | 1.48ms | 8.41ms |  |  |
| java | 2362.48 | 2356.30 | 2415.62 | 41.07ms | 42.86ms |  |  |
| csharp | 61151.46 | 40551.82 | 70161.46 | 1.68ms | 5.37ms |  |  |
| python | 1520.18 | 1299.18 | 1080.03 | 65.65ms | 951.79ms |  |  |
| nodejs | 32582.85 | 23643.80 | 32144.46 | 4.60ms | 54.89ms |  |  |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
