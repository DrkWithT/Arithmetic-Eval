# Makefile for "Basic Math Evaluator"
# By: Derek Tan

# compiler vars
CC := gcc -std=c11
CFLAGS := -Wall -Werror

# special directories
BIN_DIR := ./bin
HDRS_DIR := headers
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,%.o,$(SRCS))

EXE := $(BIN_DIR)/main

# directive for non-target rules
.PHONY: all listdeps clean

# directive to avoid folder prefix on c file names
vpath %.c $(SRC_DIR)

all: $(EXE)

listdeps:
	@echo $(SRCS)
	@echo $(OBJS)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I$(HDRS_DIR)

clean:
	rm -f $(EXE) *.o