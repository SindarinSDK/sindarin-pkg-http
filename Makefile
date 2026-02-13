# Sindarin SDK - Makefile
#
# Simple Makefile for running SDK tests.
# Dependencies are managed via sn.yaml package references.

#------------------------------------------------------------------------------
# Phony targets
#------------------------------------------------------------------------------
.PHONY: all test clean help examples benchmark benchmark-build benchmark-clean benchmark-prereqs

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
.PHONY: benchmark benchmark-build benchmark-clean benchmark-prereqs

BENCHMARK_DIR := benchmarks
BENCHMARK_SCRIPT := $(BENCHMARK_DIR)/benchmark.sh
BENCHMARK_SINDARIN_SN := $(BENCHMARK_DIR)/sindarin/server.sn
BENCHMARK_SINDARIN_BIN := $(BIN_DIR)/benchmark_sindarin$(EXE_EXT)

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
