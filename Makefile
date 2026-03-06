# Sindarin SDK - Makefile
#
# Simple Makefile for running SDK tests.
# Dependencies are managed via sn.yaml package references.

#------------------------------------------------------------------------------
# Phony targets
#------------------------------------------------------------------------------
.PHONY: all test clean help examples benchmark benchmark-build benchmark-clean benchmark-prereqs benchmark-sindarin benchmark-sindarin-profile

# Disable implicit rules for .sn.c files (these are compiled by the Sindarin compiler)
%.sn: %.sn.c
	@:

#------------------------------------------------------------------------------
# Platform Detection
#------------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
    PLATFORM := windows
    EXE_EXT := .exe
    MKDIR := mkdir
else
    UNAME_S := $(shell uname -s 2>/dev/null || echo Unknown)
    ifeq ($(UNAME_S),Darwin)
        PLATFORM := darwin
    else
        PLATFORM := linux
    endif
    EXE_EXT :=
    MKDIR := mkdir -p
endif

#------------------------------------------------------------------------------
# Configuration
#------------------------------------------------------------------------------
BIN_DIR := bin

# Sindarin compiler (from PATH, or override with SN=path/to/sn)
SN ?= sn

# Test runner from sindarin-pkg-test dependency
RUN_TESTS_SN := .sn/sindarin-pkg-test/src/execute.sn

# SDK source files (for dependency tracking)
# Note: .sn.c files are compiled by the Sindarin compiler, not tracked separately
SDK_SOURCES := $(wildcard src/*/*.sn)

# Compiled script binaries
RUN_TESTS_BIN := $(BIN_DIR)/run_tests$(EXE_EXT)

#------------------------------------------------------------------------------
# Default target
#------------------------------------------------------------------------------
all: test

#------------------------------------------------------------------------------
# test - Run SDK tests using compiled Sindarin test runner
#------------------------------------------------------------------------------
test: $(RUN_TESTS_BIN)
	@$(RUN_TESTS_BIN)

#------------------------------------------------------------------------------
# Build the test runner
#------------------------------------------------------------------------------
$(BIN_DIR):
	@$(MKDIR) $(BIN_DIR)

$(RUN_TESTS_BIN): $(RUN_TESTS_SN) $(SDK_SOURCES) | $(BIN_DIR)
	@echo "Compiling execute.sn..."
	@$(SN) $(RUN_TESTS_SN) -o $(RUN_TESTS_BIN) -l 1

#------------------------------------------------------------------------------
# clean - Remove build artifacts
#------------------------------------------------------------------------------
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BIN_DIR)
	@echo "Clean complete."

#------------------------------------------------------------------------------
# help - Show available targets
#------------------------------------------------------------------------------
help:
	@echo "Sindarin HTTP Package"
	@echo ""
	@echo "Targets:"
	@echo "  make test            Run tests"
	@echo "  make examples        Build all examples"
	@echo "  make benchmark       Run HTTP server benchmarks"
	@echo "  make benchmark-build Build benchmark implementations only"
	@echo "  make benchmark-clean Clean benchmark artifacts"
	@echo "  make benchmark-sindarin  Run Sindarin-only benchmark (interleaved, ASAN)"
	@echo "  make benchmark-sindarin-profile  Profile benchmark (perf + flame graph)"
	@echo "  make clean           Remove build artifacts"
	@echo "  make help            Show this help"
	@echo ""
	@echo "Dependencies are managed via sn.yaml package references."
	@echo ""
	@echo "Platform: $(PLATFORM)"

#------------------------------------------------------------------------------
# examples - Build all examples
#------------------------------------------------------------------------------
EXAMPLES_DIR := examples
HTML_SERVER_SN := $(EXAMPLES_DIR)/html/server.sn
HTML_SERVER_BIN := $(BIN_DIR)/html_server$(EXE_EXT)
JSON_SERVER_SN := $(EXAMPLES_DIR)/json/server.sn
JSON_SERVER_BIN := $(BIN_DIR)/json_server$(EXE_EXT)
JSON_CLIENT_SN := $(EXAMPLES_DIR)/json/client.sn
JSON_CLIENT_BIN := $(BIN_DIR)/json_client$(EXE_EXT)
SIMPLE_SERVER_SN := $(EXAMPLES_DIR)/simple/server.sn
SIMPLE_SERVER_BIN := $(BIN_DIR)/simple_server$(EXE_EXT)
SIMPLE_CLIENT_SN := $(EXAMPLES_DIR)/simple/client.sn
SIMPLE_CLIENT_BIN := $(BIN_DIR)/simple_client$(EXE_EXT)

$(HTML_SERVER_BIN): $(HTML_SERVER_SN) | $(BIN_DIR)
	@echo "Compiling html/server.sn..."
	@$(SN) $(HTML_SERVER_SN) -o $(HTML_SERVER_BIN) -l 1

$(JSON_SERVER_BIN): $(JSON_SERVER_SN) | $(BIN_DIR)
	@echo "Compiling json/server.sn..."
	@$(SN) $(JSON_SERVER_SN) -o $(JSON_SERVER_BIN) -l 1

$(JSON_CLIENT_BIN): $(JSON_CLIENT_SN) | $(BIN_DIR)
	@echo "Compiling json/client.sn..."
	@$(SN) $(JSON_CLIENT_SN) -o $(JSON_CLIENT_BIN) -l 1

$(SIMPLE_SERVER_BIN): $(SIMPLE_SERVER_SN) | $(BIN_DIR)
	@echo "Compiling simple/server.sn..."
	@$(SN) $(SIMPLE_SERVER_SN) -o $(SIMPLE_SERVER_BIN) -l 1

$(SIMPLE_CLIENT_BIN): $(SIMPLE_CLIENT_SN) | $(BIN_DIR)
	@echo "Compiling simple/client.sn..."
	@$(SN) $(SIMPLE_CLIENT_SN) -o $(SIMPLE_CLIENT_BIN) -l 1

examples: $(HTML_SERVER_BIN) $(JSON_SERVER_BIN) $(JSON_CLIENT_BIN) $(SIMPLE_SERVER_BIN) $(SIMPLE_CLIENT_BIN)
	@echo "All examples built."

#------------------------------------------------------------------------------
# benchmark - Run HTTP server benchmarks
#------------------------------------------------------------------------------
.PHONY: benchmark benchmark-build benchmark-clean benchmark-prereqs benchmark-sindarin

BENCHMARK_DIR := benchmarks
BENCHMARK_SCRIPT := $(BENCHMARK_DIR)/benchmark.sh
BENCHMARK_SINDARIN_SN := $(BENCHMARK_DIR)/sindarin/server.sn
BENCHMARK_SINDARIN_BIN := $(BIN_DIR)/benchmark_sindarin$(EXE_EXT)
BENCHMARK_SINDARIN_ASAN_BIN := $(BIN_DIR)/benchmark_sindarin_asan$(EXE_EXT)
BENCHMARK_SINDARIN_PROFILE_BIN := $(BIN_DIR)/benchmark_sindarin_profile$(EXE_EXT)

# Check prerequisites
benchmark-prereqs:
	@echo "Checking benchmark prerequisites..."
	@which wrk > /dev/null 2>&1 || (echo "ERROR: wrk not found. Install with: sudo apt install wrk" && exit 1)
	@echo "Prerequisites OK"

# Build Sindarin benchmark server
$(BENCHMARK_SINDARIN_BIN): $(BENCHMARK_SINDARIN_SN) $(SDK_SOURCES) | $(BIN_DIR)
	@echo "Compiling benchmark sindarin server..."
	@$(SN) $(BENCHMARK_SINDARIN_SN) -o $(BENCHMARK_SINDARIN_BIN) -l 1

# Build all benchmark implementations
benchmark-build: benchmark-prereqs $(BENCHMARK_SINDARIN_BIN)
	@echo "Building benchmark implementations..."
	@if [ -d "$(BENCHMARK_DIR)/c" ] && command -v gcc > /dev/null 2>&1; then \
		echo "Building C server..."; \
		(cd $(BENCHMARK_DIR)/c && make); \
	fi
	@if [ -d "$(BENCHMARK_DIR)/rust" ] && command -v cargo > /dev/null 2>&1; then \
		echo "Building Rust server..."; \
		(cd $(BENCHMARK_DIR)/rust && cargo build --release 2>&1 | tail -3); \
	fi
	@if [ -d "$(BENCHMARK_DIR)/go" ] && command -v go > /dev/null 2>&1; then \
		echo "Building Go server..."; \
		(cd $(BENCHMARK_DIR)/go && go build -o server .); \
	fi
	@if [ -d "$(BENCHMARK_DIR)/java" ] && command -v javac > /dev/null 2>&1; then \
		echo "Building Java server..."; \
		mkdir -p $(BENCHMARK_DIR)/java/out; \
		javac -d $(BENCHMARK_DIR)/java/out $(BENCHMARK_DIR)/java/src/main/java/benchmark/Server.java; \
	fi
	@if [ -d "$(BENCHMARK_DIR)/csharp" ] && command -v dotnet > /dev/null 2>&1; then \
		echo "Building C# server..."; \
		(cd $(BENCHMARK_DIR)/csharp && dotnet build -c Release -o out 2>&1 | tail -3); \
	fi
	@echo "Benchmark build complete."

# Run the full benchmark suite
benchmark: benchmark-build
	@echo "Running benchmark suite..."
	@chmod +x $(BENCHMARK_SCRIPT)
	@$(BENCHMARK_SCRIPT)
	@echo ""
	@echo "Benchmark complete. Results in $(BENCHMARK_DIR)/BENCHMARKS.md"

# Clean benchmark artifacts
benchmark-clean:
	@echo "Cleaning benchmark artifacts..."
	@rm -f $(BIN_DIR)/benchmark_*
	@rm -rf $(BENCHMARK_DIR)/results/*
	@if [ -d "$(BENCHMARK_DIR)/c" ]; then (cd $(BENCHMARK_DIR)/c && make clean 2>/dev/null || true); fi
	@if [ -d "$(BENCHMARK_DIR)/rust" ]; then (cd $(BENCHMARK_DIR)/rust && cargo clean 2>/dev/null || true); fi
	@if [ -d "$(BENCHMARK_DIR)/go" ]; then rm -f $(BENCHMARK_DIR)/go/server; fi
	@if [ -d "$(BENCHMARK_DIR)/java" ]; then rm -rf $(BENCHMARK_DIR)/java/out; fi
	@if [ -d "$(BENCHMARK_DIR)/csharp" ]; then rm -rf $(BENCHMARK_DIR)/csharp/out $(BENCHMARK_DIR)/csharp/bin $(BENCHMARK_DIR)/csharp/obj; fi
	@echo "Benchmark clean complete."

#------------------------------------------------------------------------------
# benchmark-sindarin - Interleaved GET+POST+DELETE benchmark with ASAN enabled
#------------------------------------------------------------------------------
benchmark-sindarin: benchmark-prereqs | $(BIN_DIR)
	@echo "Compiling Sindarin benchmark server (ASAN enabled)..."
	@$(SN) $(BENCHMARK_SINDARIN_SN) -o $(BENCHMARK_SINDARIN_ASAN_BIN) -g -l 1
	@. $(BENCHMARK_DIR)/config.sh; \
	TMPDIR=$$(mktemp -d); \
	echo "Starting Sindarin server (ASAN enabled)..."; \
	/usr/bin/time -v -o "$$TMPDIR/time.txt" ./$(BENCHMARK_SINDARIN_ASAN_BIN) > "$$TMPDIR/server.log" 2>&1 & \
	SERVER_PID=$$!; \
	ATTEMPT=0; \
	while ! curl -s "http://localhost:$$BENCHMARK_PORT/items" > /dev/null 2>&1; do \
		sleep 0.5; \
		ATTEMPT=$$((ATTEMPT + 1)); \
		if [ $$ATTEMPT -ge 60 ]; then \
			echo "ERROR: Server failed to start within 30 seconds"; \
			cat "$$TMPDIR/server.log" 2>/dev/null; \
			kill $$SERVER_PID 2>/dev/null; \
			rm -rf "$$TMPDIR"; \
			exit 1; \
		fi; \
	done && \
	echo "Server ready on port $$BENCHMARK_PORT" && \
	echo "" && \
	echo "Benchmarking interleaved GET+POST+DELETE /items ($$WRK_DURATION)..."; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency "http://localhost:$$BENCHMARK_PORT/items" \
		> "$$TMPDIR/get_items.txt" 2>&1 & \
	GET_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency -s $(BENCHMARK_DIR)/wrk/post_item.lua \
		"http://localhost:$$BENCHMARK_PORT/items" \
		> "$$TMPDIR/post_items.txt" 2>&1 & \
	POST_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency -s $(BENCHMARK_DIR)/wrk/delete_item.lua \
		"http://localhost:$$BENCHMARK_PORT/items" \
		> "$$TMPDIR/delete_items.txt" 2>&1 & \
	DELETE_PID=$$!; \
	wait $$GET_PID; \
	wait $$POST_PID; \
	wait $$DELETE_PID; \
	echo "Stopping server..."; \
	pkill -TERM -P $$SERVER_PID 2>/dev/null || true; \
	sleep 2; \
	kill -0 $$SERVER_PID 2>/dev/null && { pkill -9 -P $$SERVER_PID 2>/dev/null; kill -9 $$SERVER_PID 2>/dev/null; } || true; \
	fuser -k $$BENCHMARK_PORT/tcp 2>/dev/null || true; \
	sleep 1; \
	GET_RPS=$$(grep "Requests/sec" "$$TMPDIR/get_items.txt" 2>/dev/null | awk '{print $$2}'); \
	POST_RPS=$$(grep "Requests/sec" "$$TMPDIR/post_items.txt" 2>/dev/null | awk '{print $$2}'); \
	DELETE_RPS=$$(grep "Requests/sec" "$$TMPDIR/delete_items.txt" 2>/dev/null | awk '{print $$2}'); \
	AVG_LAT=$$(grep "Latency" "$$TMPDIR/get_items.txt" 2>/dev/null | head -1 | awk '{print $$2}'); \
	P99_LAT=$$(grep "99%" "$$TMPDIR/get_items.txt" 2>/dev/null | awk '{print $$2}'); \
	PEAK_MEM=$$(grep "Maximum resident set size" "$$TMPDIR/time.txt" 2>/dev/null | awk '{print $$6}'); \
	USER_TIME=$$(grep "User time" "$$TMPDIR/time.txt" 2>/dev/null | awk '{print $$4}'); \
	SYS_TIME=$$(grep "System time" "$$TMPDIR/time.txt" 2>/dev/null | awk '{print $$4}'); \
	CPU_TIME=$$(echo "$${USER_TIME:-0} + $${SYS_TIME:-0}" | bc 2>/dev/null || echo "N/A"); \
	echo ""; \
	echo "========================================="; \
	echo " Sindarin HTTP Benchmark Results (ASAN)"; \
	echo "========================================="; \
	echo ""; \
	printf "  %-16s %s\n" "Threads:" "$$WRK_THREADS"; \
	printf "  %-16s %s\n" "Connections:" "$$WRK_CONNECTIONS"; \
	printf "  %-16s %s\n" "Duration:" "$$WRK_DURATION"; \
	printf "  %-16s %s\n" "Port:" "$$BENCHMARK_PORT"; \
	printf "  %-16s %s\n" "Mode:" "interleaved GET+POST+DELETE"; \
	printf "  %-16s %s\n" "ASAN:" "enabled"; \
	echo ""; \
	echo "  Throughput"; \
	echo "  -----------------------------------------"; \
	printf "  %-16s %s req/s\n" "GET  /items" "$${GET_RPS:-N/A}"; \
	printf "  %-16s %s req/s\n" "POST /items" "$${POST_RPS:-N/A}"; \
	printf "  %-16s %s req/s\n" "DELETE /items" "$${DELETE_RPS:-N/A}"; \
	echo ""; \
	echo "  Latency (GET)"; \
	echo "  -----------------------------------------"; \
	printf "  %-16s %s\n" "Average:" "$${AVG_LAT:-N/A}"; \
	printf "  %-16s %s\n" "P99:" "$${P99_LAT:-N/A}"; \
	echo ""; \
	echo "  Resources"; \
	echo "  -----------------------------------------"; \
	printf "  %-16s %s KB\n" "Peak Memory:" "$${PEAK_MEM:-N/A}"; \
	printf "  %-16s %s s\n" "CPU Time:" "$${CPU_TIME:-N/A}"; \
	echo ""; \
	if grep -qE "AddressSanitizer|LeakSanitizer|ERROR SUMMARY" "$$TMPDIR/server.log" 2>/dev/null; then \
		echo "  ASAN Report"; \
		echo "  -----------------------------------------"; \
		cat "$$TMPDIR/server.log"; \
		echo ""; \
	else \
		echo "  ASAN: No errors detected"; \
		echo ""; \
	fi; \
	rm -rf "$$TMPDIR"

#------------------------------------------------------------------------------
# benchmark-sindarin-profile - CPU profile with perf + flame graph
#------------------------------------------------------------------------------
FLAMEGRAPH_DIR := /tmp/FlameGraph

benchmark-sindarin-profile: benchmark-prereqs | $(BIN_DIR)
	@echo "Compiling Sindarin benchmark server (profile mode)..."
	@$(SN) $(BENCHMARK_SINDARIN_SN) -o $(BENCHMARK_SINDARIN_PROFILE_BIN) -p -l 1
	@if [ ! -d "$(FLAMEGRAPH_DIR)" ]; then \
		echo "Cloning FlameGraph tools..."; \
		git clone --depth 1 https://github.com/brendangregg/FlameGraph.git $(FLAMEGRAPH_DIR) 2>&1 | tail -1; \
	fi
	@. $(BENCHMARK_DIR)/config.sh; \
	RESULTS_DIR=$(BENCHMARK_DIR)/results/profile-$$(date +%Y%m%d-%H%M%S); \
	mkdir -p "$$RESULTS_DIR"; \
	echo "Results will be saved to $$RESULTS_DIR"; \
	echo ""; \
	echo "Starting Sindarin server (profile mode)..."; \
	./$(BENCHMARK_SINDARIN_PROFILE_BIN) > "$$RESULTS_DIR/server.log" 2>&1 & \
	SERVER_PID=$$!; \
	ATTEMPT=0; \
	while ! curl -s "http://localhost:$$BENCHMARK_PORT/items" > /dev/null 2>&1; do \
		sleep 0.5; \
		ATTEMPT=$$((ATTEMPT + 1)); \
		if [ $$ATTEMPT -ge 60 ]; then \
			echo "ERROR: Server failed to start within 30 seconds"; \
			cat "$$RESULTS_DIR/server.log" 2>/dev/null; \
			kill $$SERVER_PID 2>/dev/null; \
			exit 1; \
		fi; \
	done && \
	echo "Server ready on port $$BENCHMARK_PORT (PID $$SERVER_PID)" && \
	echo "" && \
	echo "Recording perf profile during benchmark ($$WRK_DURATION)..." && \
	perf record -g --call-graph dwarf -F 997 -p $$SERVER_PID -o "$$RESULTS_DIR/perf.data" & \
	PERF_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency "http://localhost:$$BENCHMARK_PORT/items" \
		> "$$RESULTS_DIR/wrk_get.txt" 2>&1 & \
	GET_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency -s $(BENCHMARK_DIR)/wrk/post_item.lua \
		"http://localhost:$$BENCHMARK_PORT/items" \
		> "$$RESULTS_DIR/wrk_post.txt" 2>&1 & \
	POST_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency -s $(BENCHMARK_DIR)/wrk/delete_item.lua \
		"http://localhost:$$BENCHMARK_PORT/items" \
		> "$$RESULTS_DIR/wrk_delete.txt" 2>&1 & \
	DELETE_PID=$$!; \
	wait $$GET_PID; \
	wait $$POST_PID; \
	wait $$DELETE_PID; \
	echo "Benchmark complete, stopping perf..." && \
	kill -INT $$PERF_PID 2>/dev/null; \
	wait $$PERF_PID 2>/dev/null; \
	echo "Stopping server..." && \
	pkill -TERM -P $$SERVER_PID 2>/dev/null || true; \
	sleep 2; \
	kill -0 $$SERVER_PID 2>/dev/null && { pkill -9 -P $$SERVER_PID 2>/dev/null; kill -9 $$SERVER_PID 2>/dev/null; } || true; \
	fuser -k $$BENCHMARK_PORT/tcp 2>/dev/null || true; \
	sleep 1; \
	echo "" && \
	echo "Generating profile reports..." && \
	perf report --stdio -i "$$RESULTS_DIR/perf.data" --no-children \
		> "$$RESULTS_DIR/profile-flat.txt" 2>/dev/null && \
	perf report --stdio -i "$$RESULTS_DIR/perf.data" -g \
		> "$$RESULTS_DIR/profile-callgraph.txt" 2>/dev/null && \
	perf script -i "$$RESULTS_DIR/perf.data" 2>/dev/null \
		| $(FLAMEGRAPH_DIR)/stackcollapse-perf.pl 2>/dev/null \
		| $(FLAMEGRAPH_DIR)/flamegraph.pl --title "Sindarin HTTP Server Profile" \
		> "$$RESULTS_DIR/flamegraph.svg" 2>/dev/null; \
	GET_RPS=$$(grep "Requests/sec" "$$RESULTS_DIR/wrk_get.txt" 2>/dev/null | awk '{print $$2}'); \
	POST_RPS=$$(grep "Requests/sec" "$$RESULTS_DIR/wrk_post.txt" 2>/dev/null | awk '{print $$2}'); \
	DELETE_RPS=$$(grep "Requests/sec" "$$RESULTS_DIR/wrk_delete.txt" 2>/dev/null | awk '{print $$2}'); \
	AVG_LAT=$$(grep "Latency" "$$RESULTS_DIR/wrk_get.txt" 2>/dev/null | head -1 | awk '{print $$2}'); \
	P99_LAT=$$(grep "99%" "$$RESULTS_DIR/wrk_get.txt" 2>/dev/null | awk '{print $$2}'); \
	echo ""; \
	echo "========================================="; \
	echo " Sindarin HTTP Profile Results"; \
	echo "========================================="; \
	echo ""; \
	printf "  %-16s %s\n" "Threads:" "$$WRK_THREADS"; \
	printf "  %-16s %s\n" "Connections:" "$$WRK_CONNECTIONS"; \
	printf "  %-16s %s\n" "Duration:" "$$WRK_DURATION"; \
	printf "  %-16s %s\n" "Mode:" "interleaved GET+POST+DELETE"; \
	printf "  %-16s %s\n" "Build:" "profile (-O2, frame pointers, no ASAN)"; \
	echo ""; \
	echo "  Throughput"; \
	echo "  -----------------------------------------"; \
	printf "  %-16s %s req/s\n" "GET  /items" "$${GET_RPS:-N/A}"; \
	printf "  %-16s %s req/s\n" "POST /items" "$${POST_RPS:-N/A}"; \
	printf "  %-16s %s req/s\n" "DELETE /items" "$${DELETE_RPS:-N/A}"; \
	echo ""; \
	echo "  Latency (GET)"; \
	echo "  -----------------------------------------"; \
	printf "  %-16s %s\n" "Average:" "$${AVG_LAT:-N/A}"; \
	printf "  %-16s %s\n" "P99:" "$${P99_LAT:-N/A}"; \
	echo ""; \
	echo "  Top 20 Functions (CPU %)"; \
	echo "  -----------------------------------------"; \
	head -80 "$$RESULTS_DIR/profile-flat.txt" 2>/dev/null \
		| grep -E '^\s+[0-9]+\.[0-9]+%' | head -20; \
	echo ""; \
	echo "  Output Files"; \
	echo "  -----------------------------------------"; \
	echo "  $$RESULTS_DIR/profile-flat.txt"; \
	echo "  $$RESULTS_DIR/profile-callgraph.txt"; \
	echo "  $$RESULTS_DIR/flamegraph.svg"; \
	echo ""
