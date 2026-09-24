# Change this value when reusing this Makefile for another project.
PROJECT_NAME := equip-check

# Toolchain settings. Override them on the command line if needed, for example:
# make CXX=clang++ build
CXX ?= g++
CPPFLAGS := -I src -I tests
CXXFLAGS := -std=c++23 -Wall -Wextra -Wpedantic
LDFLAGS :=

SRC_DIR := src
APP_DIR := app
TEST_DIR := tests
BUILD_ROOT := build
BUILD_TYPE ?= debug
BUILD_DIR := $(BUILD_ROOT)/$(BUILD_TYPE)
BIN_DIR := $(BUILD_DIR)/bin

ifeq ($(BUILD_TYPE),debug)
CXXFLAGS += -g3 -O0
else ifeq ($(BUILD_TYPE),release)
CXXFLAGS += -O2 -DNDEBUG
else
$(error BUILD_TYPE must be either debug or release)
endif

SOURCES := $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/**/*.cpp)
OBJECTS := $(patsubst %.cpp,$(BIN_DIR)/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:.o=.d)

APP_SOURCES := $(wildcard $(APP_DIR)/*.cpp $(APP_DIR)/**/*.cpp)
APP_OBJECTS := $(patsubst %.cpp,$(BIN_DIR)/%.o,$(APP_SOURCES))
APP_DEPENDENCIES := $(APP_OBJECTS:.o=.d)

TEST_SOURCES := $(wildcard $(TEST_DIR)/*Test.cpp $(TEST_DIR)/**/*Test.cpp)
TEST_BINS := $(patsubst $(TEST_DIR)/%.cpp,$(BIN_DIR)/tests/%,$(TEST_SOURCES))

LIBRARY := $(BUILD_DIR)/lib$(PROJECT_NAME).a
APP := $(BUILD_DIR)/$(PROJECT_NAME)
FORMAT_SOURCES := $(SOURCES) $(APP_SOURCES) $(TEST_SOURCES) $(TEST_DIR)/*.hpp

.DEFAULT_GOAL := build

all: build test

build: $(APP)

run: $(APP)
	@$(APP)

test: $(TEST_BINS)
	@sh ./run_tests.sh $(TEST_BINS)

debug:
	@$(MAKE) BUILD_TYPE=debug all

release:
	@$(MAKE) BUILD_TYPE=release all

$(APP): $(APP_OBJECTS) $(LIBRARY)
	@mkdir -p $(dir $@)
	$(CXX) $(LDFLAGS) $^ -o $@

$(LIBRARY): $(OBJECTS)
	@mkdir -p $(dir $@)
	ar rcs $@ $^

$(BIN_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BIN_DIR)/tests/%: $(TEST_DIR)/%.cpp $(LIBRARY)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< $(LIBRARY) $(LDFLAGS) -o $@

tidy:
	clang-tidy $(SOURCES) $(APP_SOURCES) -- $(CPPFLAGS) -std=c++23

format:
	clang-format -i $(FORMAT_SOURCES)

format-check:
	clang-format --dry-run --Werror $(FORMAT_SOURCES)

clean:
	@rm -rf $(BUILD_ROOT)
	@echo "Cleaned build files."

.PHONY: all build run test debug release tidy format format-check clean

-include $(DEPENDENCIES) $(APP_DEPENDENCIES)
