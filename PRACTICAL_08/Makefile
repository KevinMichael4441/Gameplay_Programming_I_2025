# ----------------------------------------
# Silence command echoing
# ----------------------------------------
.SILENT:

# ----------------------------------------
# Default Compiler and Directories
# ----------------------------------------
CC						:= gcc

# ----------------------------------------
# General Configuration
# ----------------------------------------
# Directories
DEBUG_DIR 				:= ./debug
RELEASE_DIR 			:= ./release
OBJECTS_DIR				:= ./objects
SRC_DIR					:= ./src

GAME					:= game

# ----------------------------------------
# OS detection
# ----------------------------------------
UNAME_S					:= $(shell uname -s)
IS_WINDOWS				:= $(if $(findstring MINGW,$(UNAME_S)),TRUE,FALSE)
IS_LINUX				:= $(if $(findstring Linux,$(UNAME_S)),TRUE,FALSE)
IS_WSL					:= $(shell grep -qi Microsoft /proc/version 2>/dev/null && echo TRUE || echo FALSE)
IS_MACOS				:= $(if $(findstring Darwin,$(UNAME_S)),TRUE,FALSE)

# ----------------------------------------
# Include and Library Paths
# ----------------------------------------
INCLUDES				:= -Iinclude
LIBRARIES				:= -lraylib -lm -lpthread

# ----------------------------------------
# Configuration Compiler Flags
# ----------------------------------------
CONFIG					?= debug
OPTIMISATION_LEVEL		?= 2

ifeq ($(CONFIG), debug)
	BUILD_DIR := $(DEBUG_DIR)
	# See notes on CFLAGS options here: https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html
	# For cute_c2d we need may need to disable some warnings as the library uses some non-standard constructs
	# Below us standard see collision.c for details of specific CFLAGS for cute_c2
	CFLAGS := -std=c11 -Wall -Wextra -Werror -g -DDEBUG $(INCLUDES)
else ifeq ($(CONFIG), release)
	BUILD_DIR := $(RELEASE_DIR)
	CFLAGS := -std=c11 -O$(OPTIMISATION_LEVEL) -DNDEBUG $(INCLUDES)
else
	$(error Invalid CONFIG value: $(CONFIG))
endif

# ----------------------------------------
# Platform-specific variables
# ----------------------------------------
ifeq ($(IS_WINDOWS),TRUE)
	# Windows-specific settings
	LIBRARIES			+= -lglfw3 -lopengl32 -lgdi32 -lwinmm
	TARGET				:= $(BUILD_DIR)/$(GAME).exe
	TOOLCHAIN			:= ./Windows/.vscode/toolchain.sh

else ifeq ($(IS_MACOS),TRUE)
	# macOS-specific settings
	CC 					:= clang
	LIBRARIES			+= -framework IOKit -framework CoreFoundation -framework Cocoa -framework CoreGraphics
	TARGET				:= $(BUILD_DIR)/$(GAME)
	TOOLCHAIN			:= ./macos/.vscode/toolchain.sh

else ifeq ($(IS_WSL),TRUE)
	# WSL settings
	LIBRARIES			+= -lGL -ldl
	TARGET				:= $(BUILD_DIR)/$(GAME)
	TOOLCHAIN			:= ./linux/.vscode/toolchain.sh

else
	# Linux settings
	LIBRARIES			+= -lGL -ldl
	TARGET				:= $(BUILD_DIR)/$(GAME)
	TOOLCHAIN			:= ./linux/.vscode/toolchain.sh

endif


# ----------------------------------------
# Source files
# ----------------------------------------
SRC						:= $(wildcard $(SRC_DIR)/*.c)
OBJ						:= $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/$(OBJECTS_DIR)/%.o)

# ----------------------------------------
# Targets
# ----------------------------------------
# Default target
.PHONY: all
all: build run

# Build target
.PHONY: build
build: $(TARGET)

# Link target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBRARIES)
	@echo "Linking complete: $(TARGET)"

# Compile object files
$(BUILD_DIR)/$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)/$(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run target
.PHONY: run
run:
	./$(TARGET)

# Rebuild project
.PHONY: rebuild
rebuild: clean all
	@echo "Project rebuild complete"

# Clean target
.PHONY: clean
clean:
	rm -rf $(DEBUG_DIR) $(RELEASE_DIR)
	@echo "Project clean complete"

# Setup toolchain
.PHONY: toolchain
toolchain:
	bash $(TOOLCHAIN)