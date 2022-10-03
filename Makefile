all: main

# compiler vars
CC := gcc
CFLAGS := -Wall -Werror

# special directories
BIN_DIR := ./bin
HDRS_DIR := ./headers
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(patsubst $(SRCS)/%,%.o,$(SRCS))

EXE := $(BIN_DIR)/main

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I$(HDRS_DIR)

clean:
	rm -f $(EXE) *.o