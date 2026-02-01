# Sindarin SDK - Makefile
#
# Simple Makefile for running SDK tests.
# Dependencies are managed via sn.yaml package references.

#------------------------------------------------------------------------------
# Phony targets
#------------------------------------------------------------------------------
.PHONY: all test clean help examples-html

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

# Sindarin scripts
SCRIPTS_DIR := scripts
RUN_TESTS_SN := $(SCRIPTS_DIR)/run_tests.sn

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
	@echo "Compiling run_tests.sn..."
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
	@echo "  make test           Run tests"
	@echo "  make examples-html  Run HTML static file server example"
	@echo "  make clean          Remove build artifacts"
	@echo "  make help           Show this help"
	@echo ""
	@echo "Dependencies are managed via sn.yaml package references."
	@echo ""
	@echo "Platform: $(PLATFORM)"

#------------------------------------------------------------------------------
# examples-html - Run the HTML static file server example
#------------------------------------------------------------------------------
EXAMPLES_DIR := examples
HTML_SERVER_SN := $(EXAMPLES_DIR)/html/server.sn
HTML_SERVER_BIN := $(BIN_DIR)/html_server$(EXE_EXT)

$(HTML_SERVER_BIN): $(HTML_SERVER_SN) | $(BIN_DIR)
	@echo "Compiling html/server.sn..."
	@$(SN) $(HTML_SERVER_SN) -o $(HTML_SERVER_BIN) -l 1

examples-html: $(HTML_SERVER_BIN)
	@$(HTML_SERVER_BIN)
