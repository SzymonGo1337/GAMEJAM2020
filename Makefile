CC=g++
INCLUDE_PATH=include/
OBJ_DIR=obj
SRC_DIR=src
BUILD_DIR=bin
PREPROCESSOR=-Ddebug
LIB_NAME=sfml-graphics sfml-window sfml-system sfml-network sfml-audio
LIB_DIR_PATH=lib/linux
EXEC=a.out
RM_CMD=rm -f

ifeq ($(OS),Windows_NT)
EXEC=a.exe
LIB_DIR_PATH=lib/win
RM_CMD=rm
endif

INCLUDE=$(patsubst %,-I%,$(INCLUDE_PATH))
LIBS=$(patsubst %,-l%,$(LIB_NAME))
LIB_DIR=$(patsubst %,-L%,$(LIB_DIR_PATH))
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DIR=dirlinux
ifeq ($(OS),Windows_NT)
	DIR=dirwin
endif

all: $(DIR) proj

dirwin:
	#if not exist bin mkdir bin
	#if not exist obj mkdir obj

dirlinux:
	mkdir -p bin/
	mkdir -p obj/


proj:$(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(OBJ_FILES)
	$(CC) -g $(INCLUDE) $^ -o $@ $(LIB_DIR) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -g $(PREPROCESSOR) $(INCLUDE) -c -o $@ $< 

clean:
	$(RM_CMD) $(OBJ_DIR)/*.o
	$(RM_CMD) $(BUILD_DIR)/$(EXEC)

.PHONY: all clean
