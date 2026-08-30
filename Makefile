# Sindarin HTTP Package

.PHONY: setup test benchmark benchmark-prereqs benchmark-sindarin

%.sn: %.sn.c
	@:

ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
else
    EXE_EXT :=
endif

BIN_DIR      := bin
SN           ?= sn
SRC_SOURCES  := $(wildcard src/*/*.sn)
RUN_TESTS_SN := .sn/sindarin-pkg-test/src/execute.sn
RUN_TESTS    := $(BIN_DIR)/run_tests$(EXE_EXT)
BENCHMARK_DIR := benchmarks
BENCHMARK_SCRIPT := $(BENCHMARK_DIR)/benchmark.sh
BENCHMARK_SINDARIN_SN := $(BENCHMARK_DIR)/sindarin/server.sn
BENCHMARK_SINDARIN_ASAN_BIN := $(BIN_DIR)/benchmark_sindarin_asan$(EXE_EXT)

setup:
	@$(SN) --install

test: setup $(RUN_TESTS)
	@$(RUN_TESTS) --verbose

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(RUN_TESTS): $(RUN_TESTS_SN) $(SRC_SOURCES) | $(BIN_DIR)
	@$(SN) $(RUN_TESTS_SN) -o $@ -l 1

benchmark:
	@$(BENCHMARK_SCRIPT)

benchmark-prereqs:
	@echo "Checking benchmark prerequisites..."
	@command -v wrk > /dev/null 2>&1 || (echo "ERROR: wrk not found. Install with: sudo apt install wrk" && exit 1)
	@command -v curl > /dev/null 2>&1 || (echo "ERROR: curl not found" && exit 1)
	@test -x /usr/bin/time || (echo "ERROR: GNU time not found. Install with: sudo apt install time" && exit 1)
	@echo "Prerequisites OK"

benchmark-sindarin: benchmark-prereqs | $(BIN_DIR)
	@echo "Compiling Sindarin benchmark server (ASAN enabled)..."
	@$(SN) $(BENCHMARK_SINDARIN_SN) -o $(BENCHMARK_SINDARIN_ASAN_BIN) -g -l 1
	@. $(BENCHMARK_DIR)/config.sh; \
	BENCHMARK_TMPDIR=$$(mktemp -d); \
	trap 'pkill -TERM -P $$$$ 2>/dev/null || true; fuser -k '$$BENCHMARK_PORT'/tcp 2>/dev/null || true; rm -rf "'$$BENCHMARK_TMPDIR'"' EXIT; \
	echo "Starting Sindarin server (ASAN enabled)..."; \
	/usr/bin/time -v -o "$$BENCHMARK_TMPDIR/time.txt" ./$(BENCHMARK_SINDARIN_ASAN_BIN) > "$$BENCHMARK_TMPDIR/server.log" 2>&1 & \
	SERVER_PID=$$!; \
	ATTEMPT=0; \
	while ! curl -s "http://localhost:$$BENCHMARK_PORT/items" > /dev/null 2>&1; do \
		sleep 0.5; \
		ATTEMPT=$$((ATTEMPT + 1)); \
		if [ $$ATTEMPT -ge 60 ]; then \
			echo "ERROR: Server failed to start within 30 seconds"; \
			cat "$$BENCHMARK_TMPDIR/server.log" 2>/dev/null; \
			exit 1; \
		fi; \
	done; \
	echo "Server ready on port $$BENCHMARK_PORT"; \
	echo "Benchmarking interleaved GET+POST+DELETE /items ($$WRK_DURATION)..."; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency "http://localhost:$$BENCHMARK_PORT/items" \
		> "$$BENCHMARK_TMPDIR/get_items.txt" 2>&1 & \
	GET_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency -s $(BENCHMARK_DIR)/wrk/post_item.lua \
		"http://localhost:$$BENCHMARK_PORT/items" \
		> "$$BENCHMARK_TMPDIR/post_items.txt" 2>&1 & \
	POST_PID=$$!; \
	wrk -t$$WRK_THREADS -c$$WRK_CONNECTIONS -d$$WRK_DURATION \
		--latency -s $(BENCHMARK_DIR)/wrk/delete_item.lua \
		"http://localhost:$$BENCHMARK_PORT/items" \
		> "$$BENCHMARK_TMPDIR/delete_items.txt" 2>&1 & \
	DELETE_PID=$$!; \
	wait $$GET_PID; \
	wait $$POST_PID; \
	wait $$DELETE_PID; \
	echo "Stopping server..."; \
	pkill -TERM -P $$SERVER_PID 2>/dev/null || true; \
	sleep 2; \
	if kill -0 $$SERVER_PID 2>/dev/null; then \
		pkill -9 -P $$SERVER_PID 2>/dev/null || true; \
		kill -9 $$SERVER_PID 2>/dev/null || true; \
	fi; \
	fuser -k $$BENCHMARK_PORT/tcp 2>/dev/null || true; \
	sleep 1; \
	GET_RPS=$$(grep "Requests/sec" "$$BENCHMARK_TMPDIR/get_items.txt" 2>/dev/null | awk '{print $$2}'); \
	POST_RPS=$$(grep "Requests/sec" "$$BENCHMARK_TMPDIR/post_items.txt" 2>/dev/null | awk '{print $$2}'); \
	DELETE_RPS=$$(grep "Requests/sec" "$$BENCHMARK_TMPDIR/delete_items.txt" 2>/dev/null | awk '{print $$2}'); \
	AVG_LAT=$$(grep "Latency" "$$BENCHMARK_TMPDIR/get_items.txt" 2>/dev/null | head -1 | awk '{print $$2}'); \
	P99_LAT=$$(grep "99%" "$$BENCHMARK_TMPDIR/get_items.txt" 2>/dev/null | awk '{print $$2}'); \
	PEAK_MEM=$$(grep "Maximum resident set size" "$$BENCHMARK_TMPDIR/time.txt" 2>/dev/null | awk '{print $$6}'); \
	USER_TIME=$$(grep "User time" "$$BENCHMARK_TMPDIR/time.txt" 2>/dev/null | awk '{print $$4}'); \
	SYS_TIME=$$(grep "System time" "$$BENCHMARK_TMPDIR/time.txt" 2>/dev/null | awk '{print $$4}'); \
	CPU_TIME=$$(awk "BEGIN { print $${USER_TIME:-0} + $${SYS_TIME:-0} }"); \
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
	if grep -qE "AddressSanitizer|LeakSanitizer|ERROR SUMMARY" "$$BENCHMARK_TMPDIR/server.log" 2>/dev/null; then \
		echo "ASAN errors detected:"; \
		cat "$$BENCHMARK_TMPDIR/server.log"; \
		exit 1; \
	fi; \
	echo "ASAN: No errors detected"
