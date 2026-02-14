# HTTP Server Benchmark Results

Generated: 2026-02-14T00:59:46+00:00

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
| sindarin | 21069.75 | 17981.54 | 18440.30 | 4.64ms | 9.68ms | 2392444 | 60.28 |
| c | 16296.38 | 19184.97 | 29772.85 | 6.09ms | 13.20ms | 12428 | 58.19 |
| rust | 30359.00 | 25894.24 | 28432.22 | 2.47ms | 4.35ms | 318380 | 71.26 |
| go | 101224.92 | 56104.33 | 71819.64 | 1.47ms | 8.05ms | 761072 | 87.15 |
| java | 2359.09 | 2359.88 | 2426.81 | 41.16ms | 43.25ms | 260076 | 24.52 |
| csharp | 59620.36 | 39862.99 | 70070.04 | 1.75ms | 6.07ms | 482396 | 77.87 |
| python | 1116.50 | 1011.40 | 1012.41 | 58.05ms | 764.71ms | 41556 | 13.58 |
| nodejs | 31769.10 | 22004.00 | 29644.48 | 5.58ms | 108.24ms | 108204 | 30.22 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
