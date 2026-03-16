# HTTP Server Benchmark Results

Generated: 2026-03-16T20:09:15+00:00

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
| sindarin | 2926.52 | 2244.94 | 2328.45 | 3.42ms | 17.89ms | 3012 | 37.08 |
| c | 9889.32 | 8634.69 | 8813.92 | 1.12ms | 7.18ms | 1584 | 48.52 |
| rust | 189.12 | 6003.58 | 3746.54 | 42.26ms | 44.04ms | 6500 | 63.54 |
| go | 2082.95 | 14288.31 | 16678.03 | 3.84ms | 8.02ms | 20872 | 188.61 |
| java | 194.22 | 79879.04 | 83410.45 | 41.13ms | 42.04ms | 2775964 | 298.98 |
| csharp | 5513.27 | 19043.91 | 21197.12 | 1.57ms | 6.80ms | 90620 | 171.85 |
| python | 6898.29 | 185.13 | 191.36 | 8.91ms | 41.00ms | 42608 | 22.70 |
| nodejs | 8856.33 | 8540.27 | 8203.30 | 0.90ms | 1.91ms | 133304 | 30.46 |

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
