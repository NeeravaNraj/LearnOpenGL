CPP:=g++
CC:=gcc
CFLAGS:=-c -Wall -Wextra -m64 -I inc
SRC_FILES = $(shell find -type f -name "*.cpp")
CSRC_FILES = $(shell find -type f -name "*.c")
COBJ_FILES = $(abspath $(addprefix $(BUILD_DIR)/, $(CSRC_FILES:.c=.o)))
OBJ_FILES = $(abspath $(addprefix $(BUILD_DIR)/, $(SRC_FILES:.cpp=.o)))
BUILD_DIR=$(abspath ../build/o)
H_FILES = $(shell find -type f -name "*.h")


compile: compileC $(OBJ_FILES)
$(BUILD_DIR)/%.o: %.cpp $(H_FILES)
	@mkdir -p $(@D)
	$(CPP) $(CFLAGS) $< -o $@

compileC: $(COBJ_FILES)
$(BUILD_DIR)/%.o: %.c $(H_FILES)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@