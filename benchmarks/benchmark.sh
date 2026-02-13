#!/bin/bash
set -e

# ============================================================================
# HTTP Server Benchmark Suite
# ============================================================================

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

# Load configuration
source "$SCRIPT_DIR/config.sh"

PORT=${BENCHMARK_PORT:-8081}
WRK_THREADS=${WRK_THREADS:-4}
WRK_CONNECTIONS=${WRK_CONNECTIONS:-100}
WRK_DURATION=${WRK_DURATION:-30s}
WARMUP_DURATION=${WARMUP_DURATION:-5s}
RESULTS_DIR="$SCRIPT_DIR/results"
REPORT_FILE="$SCRIPT_DIR/BENCHMARKS.md"

# Languages to benchmark (in order)
LANGUAGES=("sindarin" "c" "rust" "go" "java" "csharp" "python" "nodejs")

# ============================================================================
# Helper Functions
# ============================================================================

log() { echo "[$(date +%H:%M:%S)] $*"; }

wait_for_server() {
    local max_attempts=60
    local attempt=0
    while ! curl -s "http://localhost:$PORT/items" > /dev/null 2>&1; do
        sleep 0.5
        ((attempt++))
        if [ $attempt -ge $max_attempts ]; then
            log "ERROR: Server failed to start within 30 seconds"
            return 1
        fi
    done
    log "Server is ready"
}

stop_server() {
    local pid=$1
    # Kill the time process and its children
    if [ -n "$pid" ] && kill -0 "$pid" 2>/dev/null; then
        pkill -P "$pid" 2>/dev/null || true
        kill "$pid" 2>/dev/null || true
        sleep 1
        pkill -9 -P "$pid" 2>/dev/null || true
        kill -9 "$pid" 2>/dev/null || true
    fi
    # Also kill any process on the port
    fuser -k ${PORT}/tcp 2>/dev/null || true
    sleep 2
}

check_prereqs() {
    log "Checking prerequisites..."

    if ! command -v wrk &> /dev/null; then
        log "ERROR: wrk not found. Install with: sudo apt install wrk"
        exit 1
    fi

    if ! command -v curl &> /dev/null; then
        log "ERROR: curl not found"
        exit 1
    fi

    # Check for time command with verbose support
    if ! /usr/bin/time --version &> /dev/null; then
        log "WARNING: GNU time not found, memory metrics may not be available"
    fi

    log "Prerequisites OK"
}

# ============================================================================
# Build Functions
# ============================================================================

build_sindarin() {
    log "Building Sindarin server..."
    (cd "$PROJECT_DIR" && sn benchmarks/sindarin/server.sn -o bin/benchmark_sindarin -l 1)
}

build_c() {
    log "Building C server..."
    if command -v gcc &> /dev/null; then
        (cd "$SCRIPT_DIR/c" && make)
    else
        log "WARNING: gcc not found, skipping C"
        return 1
    fi
}

build_rust() {
    log "Building Rust server..."
    if command -v cargo &> /dev/null; then
        (cd "$SCRIPT_DIR/rust" && cargo build --release 2>&1 | tail -5)
    else
        log "WARNING: cargo not found, skipping Rust"
        return 1
    fi
}

build_go() {
    log "Building Go server..."
    if command -v go &> /dev/null; then
        (cd "$SCRIPT_DIR/go" && go build -o server .)
    else
        log "WARNING: go not found, skipping Go"
        return 1
    fi
}

build_java() {
    log "Building Java server..."
    if command -v javac &> /dev/null; then
        (cd "$SCRIPT_DIR/java" && javac -d out src/main/java/benchmark/Server.java)
    else
        log "WARNING: javac not found, skipping Java"
        return 1
    fi
}

build_csharp() {
    log "Building C# server..."
    if command -v dotnet &> /dev/null; then
        (cd "$SCRIPT_DIR/csharp" && dotnet build -c Release -o out 2>&1 | tail -3)
    else
        log "WARNING: dotnet not found, skipping C#"
        return 1
    fi
}

build_python() {
    log "Python server (no build needed)"
    if ! command -v python3 &> /dev/null; then
        log "WARNING: python3 not found, skipping Python"
        return 1
    fi
}

build_nodejs() {
    log "Node.js server (no build needed)"
    if ! command -v node &> /dev/null; then
        log "WARNING: node not found, skipping Node.js"
        return 1
    fi
}

# ============================================================================
# Run Functions (start server in background, echo PID)
# ============================================================================

run_sindarin() {
    /usr/bin/time -v -o "$RESULTS_DIR/sindarin_time.txt" \
        "$PROJECT_DIR/bin/benchmark_sindarin" > /dev/null 2>&1 &
    echo $!
}

run_c() {
    /usr/bin/time -v -o "$RESULTS_DIR/c_time.txt" \
        "$SCRIPT_DIR/c/server" > /dev/null 2>&1 &
    echo $!
}

run_rust() {
    /usr/bin/time -v -o "$RESULTS_DIR/rust_time.txt" \
        "$SCRIPT_DIR/rust/target/release/benchmark-rust" > /dev/null 2>&1 &
    echo $!
}

run_go() {
    /usr/bin/time -v -o "$RESULTS_DIR/go_time.txt" \
        "$SCRIPT_DIR/go/server" > /dev/null 2>&1 &
    echo $!
}

run_java() {
    /usr/bin/time -v -o "$RESULTS_DIR/java_time.txt" \
        java -cp "$SCRIPT_DIR/java/out" benchmark.Server > /dev/null 2>&1 &
    echo $!
}

run_csharp() {
    /usr/bin/time -v -o "$RESULTS_DIR/csharp_time.txt" \
        "$SCRIPT_DIR/csharp/out/Server" > /dev/null 2>&1 &
    echo $!
}

run_python() {
    /usr/bin/time -v -o "$RESULTS_DIR/python_time.txt" \
        python3 "$SCRIPT_DIR/python/server.py" > /dev/null 2>&1 &
    echo $!
}

run_nodejs() {
    /usr/bin/time -v -o "$RESULTS_DIR/nodejs_time.txt" \
        node "$SCRIPT_DIR/nodejs/server.js" > /dev/null 2>&1 &
    echo $!
}

# ============================================================================
# Benchmark Execution
# ============================================================================

run_benchmark() {
    local lang=$1
    local pid

    log "=== Benchmarking $lang ==="

    # Start server with time measurement
    pid=$(run_$lang)

    if ! wait_for_server; then
        log "ERROR: Failed to start $lang server"
        stop_server "$pid"
        return 1
    fi

    # GET /items benchmark (start fresh - no warmup for this)
    log "Benchmarking GET /items..."
    wrk -t"$WRK_THREADS" -c"$WRK_CONNECTIONS" -d"$WRK_DURATION" \
        --latency "http://localhost:$PORT/items" \
        > "$RESULTS_DIR/${lang}_get_items.txt" 2>&1

    # POST /items benchmark (using Lua script)
    log "Benchmarking POST /items..."
    wrk -t"$WRK_THREADS" -c"$WRK_CONNECTIONS" -d"$WRK_DURATION" \
        --latency -s "$SCRIPT_DIR/wrk/post_item.lua" \
        "http://localhost:$PORT/items" \
        > "$RESULTS_DIR/${lang}_post_items.txt" 2>&1

    # GET /items/{id} benchmark (items already exist from POST test)
    log "Benchmarking GET /items/1..."
    wrk -t"$WRK_THREADS" -c"$WRK_CONNECTIONS" -d"$WRK_DURATION" \
        --latency "http://localhost:$PORT/items/1" \
        > "$RESULTS_DIR/${lang}_get_item.txt" 2>&1

    # Stop server
    stop_server "$pid"
    sleep 2

    log "Completed $lang benchmark"
}

# ============================================================================
# Report Generation
# ============================================================================

parse_wrk_rps() {
    local file=$1
    grep "Requests/sec" "$file" 2>/dev/null | awk '{print $2}' || echo "N/A"
}

parse_wrk_latency() {
    local file=$1
    grep "Latency" "$file" 2>/dev/null | head -1 | awk '{print $2}' || echo "N/A"
}

parse_wrk_p99() {
    local file=$1
    grep "99%" "$file" 2>/dev/null | awk '{print $2}' || echo "N/A"
}

parse_time_memory() {
    local file=$1
    grep "Maximum resident set size" "$file" 2>/dev/null | awk '{print $6}' || echo "N/A"
}

parse_time_cpu() {
    local file=$1
    local user=$(grep "User time" "$file" 2>/dev/null | awk '{print $4}' || echo "0")
    local sys=$(grep "System time" "$file" 2>/dev/null | awk '{print $4}' || echo "0")
    echo "$user + $sys" | bc 2>/dev/null || echo "N/A"
}

generate_report() {
    log "Generating report..."

    local date_str=$(date -Iseconds 2>/dev/null || date)

    cat > "$REPORT_FILE" << EOF
# HTTP Server Benchmark Results

Generated: $date_str

## Test Configuration

| Parameter | Value |
|-----------|-------|
| Load Testing Tool | wrk |
| Duration | $WRK_DURATION per endpoint |
| Threads | $WRK_THREADS |
| Connections | $WRK_CONNECTIONS |
| Warmup | $WARMUP_DURATION |
| Port | $PORT |

## Results Summary

| Language | GET /items (req/s) | POST /items (req/s) | GET /items/1 (req/s) | Avg Latency | P99 Latency | Peak Memory (KB) | CPU Time (s) |
|----------|-------------------|--------------------|--------------------|-------------|-------------|------------------|--------------|
EOF

    for lang in "${LANGUAGES[@]}"; do
        if [ -f "$RESULTS_DIR/${lang}_get_items.txt" ]; then
            local get_rps=$(parse_wrk_rps "$RESULTS_DIR/${lang}_get_items.txt")
            local post_rps=$(parse_wrk_rps "$RESULTS_DIR/${lang}_post_items.txt")
            local getid_rps=$(parse_wrk_rps "$RESULTS_DIR/${lang}_get_item.txt")
            local lat=$(parse_wrk_latency "$RESULTS_DIR/${lang}_get_items.txt")
            local p99=$(parse_wrk_p99 "$RESULTS_DIR/${lang}_get_items.txt")
            local mem=$(parse_time_memory "$RESULTS_DIR/${lang}_time.txt")
            local cpu=$(parse_time_cpu "$RESULTS_DIR/${lang}_time.txt")

            echo "| $lang | $get_rps | $post_rps | $getid_rps | $lat | $p99 | $mem | $cpu |" >> "$REPORT_FILE"
        fi
    done

    cat >> "$REPORT_FILE" << 'EOF'

## Notes

- All servers implement the same REST API with in-memory storage
- Sindarin is the reference implementation using sindarin-pkg-http
- Memory measured using `/usr/bin/time -v` (Maximum resident set size in KB)
- CPU time is user + system time during the benchmark period

## Reproduction

```bash
make benchmark
```
EOF

    log "Report written to $REPORT_FILE"
}

# ============================================================================
# Main Execution
# ============================================================================

main() {
    check_prereqs

    mkdir -p "$RESULTS_DIR"
    rm -f "$RESULTS_DIR"/*.txt

    log "Starting HTTP Server Benchmark Suite"
    log "Configuration: threads=$WRK_THREADS, connections=$WRK_CONNECTIONS, duration=$WRK_DURATION"

    # Build all implementations
    local available=()
    for lang in "${LANGUAGES[@]}"; do
        if build_$lang; then
            available+=("$lang")
        fi
    done

    log "Available implementations: ${available[*]}"

    # Run benchmarks
    for lang in "${available[@]}"; do
        run_benchmark "$lang" || log "WARNING: $lang benchmark failed"
    done

    # Generate report
    generate_report

    log "Benchmark suite completed!"
    log "Results: $REPORT_FILE"
}

main "$@"
