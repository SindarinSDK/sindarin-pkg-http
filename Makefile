# Sindarin SDK - Makefile
#
# Simple Makefile for running SDK tests.
# Dependencies are managed via sn.yaml package references.

#------------------------------------------------------------------------------
# Phony targets
#------------------------------------------------------------------------------
.PHONY: all test clean help examples

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
	@echo "  make test       Run tests"
	@echo "  make examples   Build all examples"
	@echo "  make clean      Remove build artifacts"
	@echo "  make help       Show this help"
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
