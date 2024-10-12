CC = clang
CFLAGS = -Wall -Wextra -Werror -g -O3 -march=native -flto
LDFLAGS = -I$(INCLUDE_DIR) -I$(EXTERNAL_INCLUDE_DIR)
SRCS_DIR = src
INCLUDE_DIR = src/include
EXTERNAL_INCLUDE_DIR = src/external/include
LIB_DIR = src/external/lib
OBJ_DIR = build/objs
BIN_DIR = build

PLATFORM = $(shell uname)

ifeq ($(PLATFORM), Darwin)
	LDFLAGS += -framework Cocoa -framework IOKit
endif

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/emu

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ $(CFLAGS) -L$(LIB_DIR) -lraylib $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
