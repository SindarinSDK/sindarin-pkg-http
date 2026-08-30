# HTTP Server Benchmark Results

Generated: 2026-08-30T13:10:28+01:00

## Test Configuration

| Parameter | Value |
|-----------|-------|
| Load Testing Tool | wrk |
| Duration | 30s (interleaved GET+POST+DELETE) |
| Threads | 4 |
| Connections | 10 |
| Warmup | 3s |
| Port | 8081 |

## Server Frameworks

| Language | Framework |
|----------|-----------|
| Sindarin | sindarin-pkg-http |
| C | Raw sockets + pthreads |
| Rust | actix-web |
| Go | net/http (stdlib) |
| Java | Javalin (Jetty) |
| C# | ASP.NET Core (Kestrel) |
| Python | uvicorn + starlette |
| Node.js | http (stdlib) |

## Results Summary

| Language | GET /items (req/s) | POST /items (req/s) | DELETE /items (req/s) | Avg Latency | P99 Latency | Peak Memory (KB) | CPU Time (s) |
|----------|-------------------|--------------------|--------------------|-------------|-------------|------------------|--------------|
| sindarin | 30692.27 | 2810.65 | 2810.80 | 256.89us | 644.00us | 4036 | 150.94 |
| c | 10927.29 | 9896.79 | 10174.94 | 0.98ms | 6.28ms | 1584 | 52.09 |
| rust | 21984.66 | 13392.76 | 11923.36 | 390.69us | 1.65ms | 18536 | 124.75 |
| go | 13861.21 | 4039.08 | 4196.77 | 578.49us | 1.58ms | 18956 | 168.23 |
| java | 11188.12 | 19951.02 | 20765.55 | 720.01us | 1.92ms | 2320036 | 223.96 |
| csharp | 19514.53 | 66395.38 | 74169.79 | 476.64us | 2.02ms | 154384 | 450.15 |
| python | 2818.54 | 2851.32 | 2817.71 | 2.83ms | 5.60ms | 33632 | 33.13 |
| nodejs | 7166.70 | 7073.30 | 6737.43 | 1.14ms | 3.76ms | 134808 | 33.62 |

## GET /items (req/s)

```
  sindarin  ######################################## 30692.27 req/s
  rust      ############################ 21984.66 req/s
  csharp    ######################### 19514.53 req/s
  go        ################## 13861.21 req/s
  java      ############## 11188.12 req/s
  c         ############## 10927.29 req/s
  nodejs    ######### 7166.70 req/s
  python    ### 2818.54 req/s
```

## POST /items (req/s)

```
  csharp    ######################################## 66395.38 req/s
  java      ############ 19951.02 req/s
  rust      ######## 13392.76 req/s
  c         ##### 9896.79 req/s
  nodejs    #### 7073.30 req/s
  go        ## 4039.08 req/s
  python    # 2851.32 req/s
  sindarin  # 2810.65 req/s
```

## DELETE /items (req/s)

```
  csharp    ######################################## 74169.79 req/s
  java      ########### 20765.55 req/s
  rust      ###### 11923.36 req/s
  c         ##### 10174.94 req/s
  nodejs    ### 6737.43 req/s
  go        ## 4196.77 req/s
  python    # 2817.71 req/s
  sindarin  # 2810.80 req/s
```

## Peak Memory

```
  c         # 1.5 MB
  sindarin  # 3.9 MB
  rust      # 18.1 MB
  go        # 18.5 MB
  python    # 32.8 MB
  nodejs    ## 131.6 MB
  csharp    ## 150.7 MB
  java      ######################################## 2265.6 MB
```

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
