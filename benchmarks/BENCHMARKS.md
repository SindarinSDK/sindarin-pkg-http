# HTTP Server Benchmark Results

Generated: 2026-02-26T19:28:34+00:00

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
| sindarin | 50715.08 | 40074.60 | 37217.92 | 2.87ms | 9.51ms |  |  |
| c | 50896.84 | 55684.56 | 69821.52 | 2.07ms | 7.89ms | 7224 | 136.43 |
| rust | 39867.35 | 37503.00 | 40557.18 | 2.24ms | 4.07ms | 319400 | 205.13 |
| go | 231988.72 | 406834.72 | 568263.31 | 542.99us | 2.53ms | 4994400 | 347.00 |
| java | 220555.65 | 49228.51 |  | 534.87us | 848.00us | 2405664 | 75.01 |
| csharp | 170711.12 | 4554.79 | 43232.96 | 678.87us | 3.17ms | 5225640 | 225.64 |
| python | 550.78 |  |  | 54.10ms | 574.59ms | 19468 | .96 |
| nodejs | 106809.06 | 62325.99 | 63050.84 | 1.08ms | 1.74ms | 286756 | 30.96 |

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
