# HTTP Server Benchmark Results

Generated: 2026-03-16T23:41:11+00:00

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
| sindarin | 31697.75 | 3087.45 | 3091.00 | 247.38us | 608.00us | 1956 | 139.98 |
| c | 10113.55 | 9036.32 | 9113.20 | 1.04ms | 6.31ms | 1744 | 52.97 |
| rust | 14363.46 | 10534.15 | 10659.81 | 737.21us | 4.58ms | 17704 | 97.77 |
| go | 15489.60 | 4207.47 | 4350.76 | 517.53us | 1.42ms | 19508 | 165.68 |
| java | 13305.82 | 23989.26 | 24793.82 | 607.56us | 1.65ms | 2285516 | 233.97 |
| csharp | 16121.62 | 57275.49 | 52163.53 | 577.06us | 3.12ms | 150440 | 397.29 |
| python | 2802.69 | 2782.10 | 2760.91 | 2.84ms | 5.90ms | 33788 | 33.09 |
| nodejs | 8691.66 | 9076.86 | 8928.14 | 0.92ms | 1.92ms | 135544 | 33.65 |

## GET /items (req/s)

```
  sindarin  ######################################## 31697.75 req/s
  csharp    #################### 16121.62 req/s
  go        ################### 15489.60 req/s
  rust      ################## 14363.46 req/s
  java      ################ 13305.82 req/s
  c         ############ 10113.55 req/s
  nodejs    ########## 8691.66 req/s
  python    ### 2802.69 req/s
```

## POST /items (req/s)

```
  csharp    ######################################## 57275.49 req/s
  java      ################ 23989.26 req/s
  rust      ####### 10534.15 req/s
  nodejs    ###### 9076.86 req/s
  c         ###### 9036.32 req/s
  go        ## 4207.47 req/s
  sindarin  ## 3087.45 req/s
  python    # 2782.10 req/s
```

## DELETE /items (req/s)

```
  csharp    ######################################## 52163.53 req/s
  java      ################### 24793.82 req/s
  rust      ######## 10659.81 req/s
  c         ###### 9113.20 req/s
  nodejs    ###### 8928.14 req/s
  go        ### 4350.76 req/s
  sindarin  ## 3091.00 req/s
  python    ## 2760.91 req/s
```

## Peak Memory

```
  c         # 1.7 MB
  sindarin  # 1.9 MB
  rust      # 17.2 MB
  go        # 19.0 MB
  python    # 32.9 MB
  nodejs    ## 132.3 MB
  csharp    ## 146.9 MB
  java      ######################################## 2231.9 MB
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
