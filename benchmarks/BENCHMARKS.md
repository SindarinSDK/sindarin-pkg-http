# HTTP Server Benchmark Results

Generated: 2026-02-13T13:24:26+00:00

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
| sindarin | 20185.10 | 16622.88 | 0.00 | 4.83ms | 9.35ms | 3432224 | 77.64 |
| c | 14249.61 | 18458.36 | 28164.76 | 7.63ms | 36.43ms | 12300 | 55.90 |
| rust | 29708.54 | 23389.73 | 28322.16 | 2.52ms | 5.41ms | 297656 | 68.43 |
| go | 101506.45 | 56087.34 | 71965.01 | 1.54ms | 9.12ms | 758664 | 87.17 |
| java | 2302.33 | 2370.70 | 2351.71 | 41.26ms | 46.02ms | 263056 | 22.80 |
| csharp | 60362.87 | 40089.08 | 70275.65 | 1.71ms | 5.62ms | 487696 | 77.86 |
| python | 1137.58 | 1268.10 | 1282.23 | 56.63ms | 698.27ms | 42472 | 16.00 |
| nodejs | 33715.71 | 24046.41 | 31922.09 | 4.47ms | 53.21ms | 108864 | 30.84 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
