# HTTP Server Benchmark Results

Generated: 2026-02-21T08:27:29+00:00

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
| sindarin | 181537.07 | 95254.88 | 203735.80 | 652.30us | 2.77ms | 1500 | 0 |
| c | 50952.38 | 56268.43 | 71802.70 | 2.14ms | 8.83ms | 7328 | 130.05 |
| rust | 44154.53 | 37990.09 | 41925.73 | 2.27ms | 3.30ms | 326608 | 216.03 |
| go | 223835.83 | 420760.66 | 591984.11 | 612.96us | 3.19ms | 5308420 | 337.35 |
| java | 214459.65 | 195429.40 | 209732.85 | 465.84us | 826.00us | 5688100 | 168.95 |
| csharp | 183148.47 | 99237.03 | 203074.33 | 633.77us | 2.79ms | 1155400 | 260.58 |
| python | 1032.89 | 927.08 | 1131.08 | 53.36ms | 533.60ms | 39492 | 5.66 |
| nodejs | 115613.20 | 86961.77 | 106960.75 | 1.21ms | 2.01ms | 255372 | 30.89 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
