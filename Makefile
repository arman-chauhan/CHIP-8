CC = clang
CFLAGS = -I$(INCLUDE_DIR) -I$(EXTERNAL_INCLUDE_DIR) -Wall -Wextra -Werror -Wpedantic -g

SRCS_DIR = src
INCLUDE_DIR = src/include
EXTERNAL_INCLUDE_DIR = src/external/include
LIB_DIR = src/external/lib
OBJ_DIR = objs

SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = emu

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ -L$(LIB_DIR) -lraylib  -framework Cocoa  -framework IOKit 

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)  
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean