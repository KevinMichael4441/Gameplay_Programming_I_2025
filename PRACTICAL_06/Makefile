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
RAYLIB_STARTER_DIR		:= raylib_starter
DEBUG_DIR 				:= ./debug
RELEASE_DIR 			:= ./release
OBJECTS_DIR				:= ./objects
SRC_DIR					:= ./src
WEB_DIR					:= ./web

RAYLIB_INCLUDE			:= $(RAYLIB_STARTER_DIR)/raylib/build/raylib/include
RAYLIB_LIBRARY			:= $(RAYLIB_STARTER_DIR)/raylib/build/raylib
RAYLIB_LIBRARY_WEB		:= $(RAYLIB_STARTER_DIR)/raylib/build_web/raylib

EMSDK_DIR				:= $(RAYLIB_STARTER_DIR)/emsdk

# Game HTML Template
HTML_TEMPLATE			:= ./template/template.html

# ----------------------------------------
# OS detection
# ----------------------------------------
UNAME_S					:= $(shell uname -s)
IS_WINDOWS				:= $(if $(findstring MINGW,$(UNAME_S)),TRUE,FALSE)
IS_LINUX				:= $(if $(findstring Linux,$(UNAME_S)),TRUE,FALSE)
IS_WSL					:= $(shell grep -qi Microsoft /proc/version && echo TRUE || echo FALSE)
IS_MACOS				:= $(if $(findstring Darwin,$(UNAME_S)),TRUE,FALSE)

# ----------------------------------------
# OS detection
# ----------------------------------------
INCLUDES				:= -I. -I$(RAYLIB_INCLUDE)
LIBS					:= -L$(RAYLIB_LIBRARY)
LIBRARIES				:= -lraylib -lm -lpthread

# ----------------------------------------
# Configuration Compiler Flags
# ----------------------------------------
CONFIG					?= debug
OPTIMISATION_LEVEL		?= 2

ifeq ($(CONFIG), debug)
	BUILD_DIR := $(DEBUG_DIR)
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
	TOOLCHAIN			:= ./toolchain/toolchain_windows.sh
	LIBRARIES			+= -lglfw3 -lopengl32 -lgdi32 -lwinmm
	TARGET				:= $(BUILD_DIR)/game.exe
	WEB_APP				:= start http://localhost:8000/

else ifeq ($(IS_MACOS),TRUE)
	# macOS-specific settings
	TOOLCHAIN			:= ./toolchain/toolchain_macos.sh
	CC 					:= clang
	LIBRARIES			+= -framework IOKit -framework CoreFoundation -framework Cocoa -framework CoreGraphics
	TARGET				:= $(BUILD_DIR)/game.bin
	WEB_APP				:= open http://localhost:8000/

else ifeq ($(IS_WSL),TRUE)
	# WSL settings
	TOOLCHAIN			:= ./toolchain/toolchain_linux.sh
	LIBRARIES			+= -lGL -ldl
	TARGET				:= $(BUILD_DIR)/game.bin
	WEB_APP				:= wslview http://localhost:8000/

else
	# Linux settings
	TOOLCHAIN			:= ./toolchain/toolchain_linux.sh
	LIBRARIES			+= -lGL -ldl
	TARGET				:= $(BUILD_DIR)/game.bin
	WEB_APP				:= xdg-open http://localhost:8000/
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
all: update_submodule build run

# Compile object files
$(BUILD_DIR)/$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)/$(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Update submodule target
update_submodule:
	git submodule update --init --remote $(RAYLIB_STARTER_DIR) || true

# Conditionally include messages.mk and resources.mk if messages.mk exists
ifneq ("$(wildcard $(RAYLIB_STARTER_DIR)/toolchain/messages.mk)","")
    $(info Including messages.mk from $(RAYLIB_STARTER_DIR)/toolchain/)
    include $(RAYLIB_STARTER_DIR)/toolchain/messages.mk
    include $(RAYLIB_STARTER_DIR)/toolchain/resources.mk
else
    $(info messages.mk not found at $(RAYLIB_STARTER_DIR)/toolchain/)
endif

# Install toolchain for build
install_toolchain: update_submodule
	if [ -d "$(RAYLIB_STARTER_DIR)" ]; then \
		$(MAKE) -C $(RAYLIB_STARTER_DIR) install_toolchain BUILD_TYPE=build; \
	fi

# Install toolchain for web build
install_toolchain_web: update_submodule
	if [ -d "$(RAYLIB_STARTER_DIR)" ]; then \
		$(MAKE) -C $(RAYLIB_STARTER_DIR) install_toolchain BUILD_TYPE=build_web; \
	fi

# Build target
.PHONY: build
build: BUILD_TYPE := build
build: update_submodule install_toolchain
	$(call INFO_MSG,$(MSG_BUILD_START))
	$(MAKE) $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS) $(LIBRARIES)
	$(call SUCCESS_MSG,$(MSG_BUILD_END))

# Run target
.PHONY: run
run:
	$(call INFO_MSG,$(MSG_RUN_BINARY))
	./$(TARGET)

# Build target for web
.PHONY: build_web
build: BUILD_TYPE := build_web
build_web: update_submodule install_toolchain_web

	$(info RAYLIB_INCLUDE: $(RAYLIB_INCLUDE))
	$(info RAYLIB_LIBRARY_WEB: $(RAYLIB_LIBRARY_WEB))
	$(info EMSDK_DIR: $(EMSDK_DIR))
	$(info HTML_TEMPLATE: $(HTML_TEMPLATE))

	$(call INFO_MSG,$(MSG_BUILD_WEB_START))

	rm -rf $(WEB_DIR)
	mkdir -p $(WEB_DIR)

	if [ -f "$(EMSDK_DIR)/emsdk_env.sh" ]; then \
		$(call INFO_MSG, $(MSG_BUILD_WEB_EMSDK)); \
		bash -i -c "source $(EMSDK_DIR)/emsdk_env.sh && \
		emcc $(SRC_DIR)/*.c -o ./$(WEB_DIR)/index.html \
			-I. -I$(RAYLIB_INCLUDE) \
			-L$(RAYLIB_LIBRARY_WEB) \
			-lraylib \
			-s USE_GLFW=3 -s FULL_ES2=1 -s ASYNCIFY \
			--shell-file $(HTML_TEMPLATE) \
			-D WEB_BUILD"; \
		if [ $$? -eq 0 ]; then \
			$(call SUCCESS_MSG, $(MSG_BUILD_WEB_END)); \
		else \
			$(call ERROR_MSG, $(MSG_BUILD_WEB_FAIL)); \
		fi \
	else \
		$(call ERROR_MSG, $(MSG_BUILD_WEB_EMSDK_FAIL)); \
	fi


# Stop Web Server target
stop_web_server:
	$(MAKE) -C $(RAYLIB_STARTER_DIR) stop_web_server

# Start Web Server target
start_web_server:
	$(call INFO_MSG,$(WEB_DIR))
	$(info WEB_DIR: $(WEB_DIR))

	python3 -m http.server --directory $(WEB_DIR) &
	sleep 3

# Run Web target
.PHONY: run_web
run_web: build_web stop_web_server start_web_server
	$(WEB_APP)

# Clean target
.PHONY: clean
clean:
	$(call INFO_MSG,"Cleaning...")
	$(MAKE) -C $(RAYLIB_STARTER_DIR) clean
	rm -f $(TARGET_DEBUG) $(TARGET_RELEASE)
	rm -rf $(DEBUG_DIR) $(RELEASE_DIR)
	$(call SUCCESS_MSG,"Clean complete")

# Clean target
.PHONY: clean_toolchain
clean_toolchain: clean
	$(call INFO_MSG,"Cleaning toolchain...")
	$(MAKE) -C $(RAYLIB_STARTER_DIR) clean_toolchain
	$(call SUCCESS_MSG,"Clean toolchain complete")