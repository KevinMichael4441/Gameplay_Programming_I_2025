# Message Color Codes
BLUE := \033[0;34m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RED := \033[0;31m
RESET := \033[0m

# Platform detection
ifeq ($(OS),Windows_NT)
    IS_WINDOWS := TRUE
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        IS_MACOS := TRUE
    else
        IS_LINUX := TRUE
    endif
endif

# Color output function for macOS (does not require -e flag)
define PRINT_MSG_MACOS
	echo "$(1)$(2)$(RESET)"
endef

# Color output function for Linux (uses /bin/echo -e)
define PRINT_MSG_LINUX
	/bin/echo -e "$(1)$(2)$(RESET)"
endef

# Color output function for Windows
define PRINT_MSG_WIN
	/bin/echo -e "$(1)$(2)$(RESET)"
endef

# Platform-specific message printing logic
ifeq ($(IS_WINDOWS),TRUE)
  PRINT_MSG = $(PRINT_MSG_WIN)
else ifeq ($(IS_MACOS),TRUE)
  PRINT_MSG = $(PRINT_MSG_MACOS)
else ifeq ($(IS_LINUX),TRUE)
  PRINT_MSG = $(PRINT_MSG_LINUX)
endif

# Message macros
define INFO_MSG
	$(call PRINT_MSG,$(BLUE),INFO: $(1))
endef
define SUCCESS_MSG
	$(call PRINT_MSG,$(GREEN),SUCCESS: $(1))
endef
define WARNING_MSG
	$(call PRINT_MSG,$(YELLOW),WARNING: $(1))
endef
define ERROR_MSG
	$(call PRINT_MSG,$(RED),ERROR: $(1))
endef
