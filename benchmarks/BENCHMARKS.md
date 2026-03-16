# HTTP Server Benchmark Results

Generated: 2026-03-16T21:14:26+00:00

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
| sindarin | 4612.66 | 3611.43 | 3715.73 | 2.48ms | 14.84ms | 4028 | 45.30 |
| c | 9635.25 | 8422.56 | 8577.48 | 1.16ms | 7.46ms | 1648 | 51.42 |
| rust | 169.71 | 23655.65 | 21080.33 | 41.21ms | 42.10ms | 9372 | 216.84 |
| go | 2125.80 | 13913.20 | 16041.32 | 3.76ms | 7.78ms | 21108 | 200.42 |
| java | 193.79 | 89417.12 | 94703.88 | 41.16ms | 42.07ms | 1327128 | 197.16 |
| csharp | 6032.66 | 19029.59 | 20943.56 | 1.36ms | 4.42ms | 90816 | 178.16 |
| python | 191.35 | 187.36 | 186.27 | 41.62ms | 43.13ms | 30768 | 6.52 |
| nodejs | 8944.71 | 8455.49 | 8137.14 | 0.89ms | 1.86ms | 133872 | 33.65 |

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
