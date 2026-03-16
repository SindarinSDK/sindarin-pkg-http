# HTTP Server Benchmark Results

Generated: 2026-03-16T22:42:12+00:00

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
| sindarin | 7979.33 | 7178.08 | 7391.91 | 1.31ms | 7.51ms | 2748 | 58.82 |
| c | 9132.09 | 8036.63 | 8124.92 | 1.23ms | 7.83ms | 1420 | 50.04 |
| rust | 13969.14 | 8867.37 | 7987.83 | 781.36us | 5.07ms | 18312 | 95.82 |
| go | 14748.66 | 4359.90 | 4519.95 | 543.27us | 1.47ms | 18784 | 159.71 |
| java | 12657.40 | 23462.08 | 24177.64 | 639.33us | 1.79ms | 2285148 | 229.90 |
| csharp | 18592.66 | 61545.73 | 65405.85 | 511.64us | 2.79ms | 149880 | 420.89 |
| python | 2720.60 | 2684.24 | 2624.26 | 2.93ms | 5.92ms | 33824 | 33.17 |
| nodejs | 8783.58 | 8467.04 | 8170.10 | 0.91ms | 1.93ms | 135348 | 33.48 |

## GET /items (req/s)

```
  csharp    ######################################## 18592.66 req/s
  go        ############################### 14748.66 req/s
  rust      ############################## 13969.14 req/s
  java      ########################### 12657.40 req/s
  c         ################### 9132.09 req/s
  nodejs    ################## 8783.58 req/s
  sindarin  ################# 7979.33 req/s
  python    ##### 2720.60 req/s
```

## POST /items (req/s)

```
  csharp    ######################################## 61545.73 req/s
  java      ############### 23462.08 req/s
  rust      ##### 8867.37 req/s
  nodejs    ##### 8467.04 req/s
  c         ##### 8036.63 req/s
  sindarin  #### 7178.08 req/s
  go        ## 4359.90 req/s
  python    # 2684.24 req/s
```

## DELETE /items (req/s)

```
  csharp    ######################################## 65405.85 req/s
  java      ############## 24177.64 req/s
  nodejs    #### 8170.10 req/s
  c         #### 8124.92 req/s
  rust      #### 7987.83 req/s
  sindarin  #### 7391.91 req/s
  go        ## 4519.95 req/s
  python    # 2624.26 req/s
```

## Peak Memory

```
  c         # 1.3 MB
  sindarin  # 2.6 MB
  rust      # 17.8 MB
  go        # 18.3 MB
  python    # 33.0 MB
  nodejs    ## 132.1 MB
  csharp    ## 146.3 MB
  java      ######################################## 2231.5 MB
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
