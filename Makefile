# Library Name (Outputs libexample.a and libexample.so)
LIB_NAME  := biscuit

# Tools
CC        = gcc
AR        ?= ar
ARFLAGS   ?= rcs
LDFLAGS   ?= -shared

# Flags: -fPIC is enabled so object files work in both .a and .so
CFLAGS    ?= -Wall -Wextra -Wpedantic -std=c11 -O2 -fPIC -MMD -MP -ffreestanding -nostdlib

# Directories & Files
BUILD_DIR := build
SRCS      := $(wildcard *.c) $(wildcard src/*.c)
OBJS      := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS      := $(OBJS:.o=.d)

STATIC    := $(BUILD_DIR)/lib$(LIB_NAME).a
SHARED    := $(BUILD_DIR)/lib$(LIB_NAME).so

.PHONY: all static shared clean

# Default rule builds both libraries
all: static shared

static: $(STATIC)
shared: $(SHARED)

# Link static archive (.a)
$(STATIC): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Link shared object (.so)
$(SHARED): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# Compile source files to object files inside build/
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $@

# Automatically include header dependency files
-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)
