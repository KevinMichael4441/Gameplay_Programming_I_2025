# Command Pattern Starter Kit Guide <a name="command-pattern-guide"></a>

A comprehensive *StarterKit* for implementing the *Command design pattern* in C using Raylib, featuring a mediator for decoupling, input management, and game system integration. This kit provides a structured approach to handling commands and input in game development.

## Table of Contents
- [Overview](#overview)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Implementation Guide](#implementation-guide)
- [Input System](#input-system)
- [Usage Examples](#usage-examples)
- [Build Configuration](#build-configuration)
- [Resources](#resources)
- [Support](#support)

## Overview <a name="overview"></a>
This starter kit provides:
- Complete Command pattern implementation in C
- Mediator pattern for component decoupling
- Flexible input handling system
- Game loop integration
- Extensible command structure

## Architecture <a name="architecture"></a>
The system consists of four main components:

1. **Command System**

	- Command function pointers
	- Command type enumeration

2. **Mediator**

	- Decouples player from command execution
	- Manages communication between components
	- Handles command routing

3. **Input Manager**

	- Keyboard input handling
	- Controller support

4. **Game System**

	- Initialization
	- Update loop
	- Rendering

## Project Structure <a name="project-structure"></a>

```
command_pattern_starter/
├── include/
│   ├── command.h       # Command structures and function declarations
│   ├── mediator.h      # Mediator pattern implementation
│   ├── input_manager.h # Input handling system
│   ├── player.h        # Player struct
│   └── game.h          # Game system header
├── src/
│   ├── command.c       # Command implementations
│   ├── mediator.c      # Mediator implementation
│   ├── input_manager.c # Input system implementation
│   ├── player.c        # Player implementation
│   ├── game.c          # Game system implementation
│   └── main.c          # Entry point
├── Makefile            # Build configuration
└── README.md           # This documentation
```

## Implementation Guide <a name="implementation-guide"></a>

### Command System
```c
// Command type enumeration
typedef enum {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT
    // Add more commands as needed
} Command;
```

### Mediator Usage
```c
// Mediator structure
typedef struct {
    Player* player;
} Mediator;

// Mediator functions
void create_mediator(Mediator* mediator);
void mediator_execute_command(Mediator* mediator, Command* command);
```

### Input System Setup
```c
// Input manager
Command poll_input();
```

## Input System <a name="input-system"></a>
The input system supports:
- Keyboard mapping through key mappings
- Controller integration via button mappings

## Usage Examples <a name="usage-examples"></a>
Basic implementation example:
```c
// Initialize systems
GameData gameData;
Mediator* create_mediator(Player* player);

// Game loop
while (game_is_running()) {
    Command poll_input();
    mediator_execute_command(gameData->mediator, command);
    ...
}
```

## Build Configuration <a name="build-configuration"></a>
Build the project using the provided Makefile:
```bash
# Build all targets
make all

# Clean build files
make clean
```

## Resources <a name="resources"></a>
- [Command Pattern in C](https://www.geeksforgeeks.org/command-pattern/)
- [Game Programming Patterns](http://gameprogrammingpatterns.com/command.html)
- [Input Handling in C](https://www.raylib.com/examples.html)
- [Mediator Pattern Explained](https://refactoring.guru/design-patterns/mediator)
- [Design Patterns in C: Mediator](https://www.codeproject.com/Articles/5274704/Design-Patterns-in-C-The-Mediator-Pattern) - In-depth explanation of implementing Mediator pattern in C
- [Example: Event System Using Mediator](https://www.embedded.com/event-handling-with-the-mediator-pattern/) - Practical implementation of Mediator for event handling in embedded systems

## Support <a name="support"></a>
For questions and support:

- muddygames

[Back to top](#command-pattern-guide)