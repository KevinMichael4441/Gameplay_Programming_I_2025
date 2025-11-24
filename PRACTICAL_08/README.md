# Command Pattern Starter Kit <a name="command-pattern-guide"></a>

A comprehensive implementation of the **Command design pattern** in C using Raylib, featuring **bitwise** command, mediator decoupling, and multi-input support. This StarterKit includes input handling with keyboard and controller support, enabling command combinations.

## Table of Contents

- [Overview](#overview)
- [Quick Start](#quick-start)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Tasks](#tasks)
- [Resources](#resources)
- [Support](#support)

## Overview <a name="overview"></a>

StarterKit provides an implementation of Command Pattern with:

- **Bitwise Command**: combine multiple commands using bitflags
- **Mediator Pattern**: Decoupling input handling from game logic
- **Command Combos**: Handle complex input sequences (jump + fire, move + shoot)
- **Extendable StarterKit**: Easy to add new commands and behaviors
- **Cross-Platform Support**: Works on Windows (MSYS2), Linux (Debian), and MacOS

## Input -> Game Action

[![](https://mermaid.ink/img/pako:eNqdlF1vmzAUhv-K5d60GknNZ4BFkZqPSvuIVrW72tiFA8cEzdiRMW2yJP99DhCW3kWDG3z8vC_nHDje41RmgGM8GAwSoQvNIf4kNrVGWqInTneg0BTW9LWQtUpEQ-WKbtbo-zwRyFwPPxP8BXYrSVWGvj2jmRRaSc5BJfhXi0wN0pouqaA5qPFK3U_GleFEPnkycLN7eze-72K9dGakS8gKqmWrup0Dh5xqqO56aG6gmSxLKjL0sqs0lC262EJaa0Dd3j_Bwgja4h5SXUjxLp-lfIWvwEw6H_t8GsBYvAM_1-XmEurtu8agwWByeKZvqKnugKZdN5r4tNDokdO8aixhmCNim5sc0KyrvMHOZX3oPsYBdW2ft9uU8wo91qIpozqgxWUGld5xMHmwgvP4BlzmsMw6Jfsb4hs7GgWZ0y0Hb0Wm17G72Vqp5FLFN4SQS5NpZ8IYc4H0JswfpYRcazI7m7jgM783Ga1sRq_OZH4uJ2Q-RL2JG4bgpteaLP63J9jCJaiSFpmZmf3JMsF6DSUkODaPGTBac53gRBwNSmstX3YixbFWNVhYyTpf45hRXplVvcnMfzwvqBmoso9uqPghZXmW5Or0qk4OIgM1k7XQOHZsu4FxvMdbHNueN4wCEo4CL_BCzx35Ft4ZikTDIAq9kU2CyHX9yDta-E_jT4Z-6PpO4DgR8T3H80MLm0kzg7Zsj4TmZDj-BWiHT38?type=png)](https://mermaid.live/edit#pako:eNqdlF1vmzAUhv-K5d60GknNZ4BFkZqPSvuIVrW72tiFA8cEzdiRMW2yJP99DhCW3kWDG3z8vC_nHDje41RmgGM8GAwSoQvNIf4kNrVGWqInTneg0BTW9LWQtUpEQ-WKbtbo-zwRyFwPPxP8BXYrSVWGvj2jmRRaSc5BJfhXi0wN0pouqaA5qPFK3U_GleFEPnkycLN7eze-72K9dGakS8gKqmWrup0Dh5xqqO56aG6gmSxLKjL0sqs0lC262EJaa0Dd3j_Bwgja4h5SXUjxLp-lfIWvwEw6H_t8GsBYvAM_1-XmEurtu8agwWByeKZvqKnugKZdN5r4tNDokdO8aixhmCNim5sc0KyrvMHOZX3oPsYBdW2ft9uU8wo91qIpozqgxWUGld5xMHmwgvP4BlzmsMw6Jfsb4hs7GgWZ0y0Hb0Wm17G72Vqp5FLFN4SQS5NpZ8IYc4H0JswfpYRcazI7m7jgM783Ga1sRq_OZH4uJ2Q-RL2JG4bgpteaLP63J9jCJaiSFpmZmf3JMsF6DSUkODaPGTBac53gRBwNSmstX3YixbFWNVhYyTpf45hRXplVvcnMfzwvqBmoso9uqPghZXmW5Or0qk4OIgM1k7XQOHZsu4FxvMdbHNueN4wCEo4CL_BCzx35Ft4ZikTDIAq9kU2CyHX9yDta-E_jT4Z-6PpO4DgR8T3H80MLm0kzg7Zsj4TmZDj-BWiHT38)


> **Flow:**
>
> 1. **Input Devices** -> Player presses keys/buttons
> 2. **Input Manager** -> Converts to bitwise command flags (e.g., `MOVE_UP | FIRE`)
> 3. **Mediator** -> Checks which bits are set and routes commands
> 4. **Player** -> Executes the appropriate action(s) / behaviour(s)


**Example**: Player moves **LEFT** AND **JUMPS** at the same time
```c

Command combo = MOVE_LEFT | JUMP;
// Binary: 000100 | 010000 = 010100
// Result: Both bits are set

// Checking if MOVE_LEFT is active:
if (IsCommandActive(command, MOVE_LEFT))
{
    // This is TRUE because bit 2 is set
    printf("Move Left is active!\n");
	MoveLeft(player);
}

// Checking if JUMP is active:
if (IsCommandActive(command, JUMP))
{
    // This is TRUE because bit 4 is set
    printf("Jump is active!\n");
	Jump(player);
}
```

**Visual Example:**

[![](https://mermaid.ink/img/pako:eNqtlFtvmzAYhv-K69xsEmk5mYMVVcqBVKqaJWq7XWxMk4GPBA1wZMyaLOt_nyE0TTJN6kW5QLyfv_d5fRDe4ZgngCleCrZeocdJWCL1DL-FeCGgqigahvj7vjh6LT4shuPgMLB_j9XwbP4l-HEXTB8Hkbi6HmUlE1uKdF03dL0tTSDOCpZTZB_cE-W7_TxbnFqU4dxiOGeJgXKOMvmUVYDm92i-BsFkxsvWtg9FfzrUmXWqrPdQ1blss_6ZnrnXIy5XKMpkhZgAVIG8OOPcNFNomljcJFcINhDXEi5a-6CSgpfL6xn_BXeQyg8fB1ddqR0ffpqc9N3Wxfqo5yxriPr9azTuDqMV3XGNWxF0-3ksglZMu0W34uaYWcltDoqcZnlOe1GUQBppTfxPoD3Dd53E7GT_KUvkilrrjRbznAvaa3b1CDJ6D8i4g6Rp6sf2AZISNzXcU4j5X8jkPSDBC8QCkpIDxI2MlL15OdMOEhMw2CuEEC8y07dCbjoII4nD3APEBDexzmZin0CwhgsQBcsS9YPvGmSI5QoKCDFVn-qYmPoBQhyWz6qV1ZI_bMsYUylq0LDg9XKFacrySql6nTAJk4ypi6I4VNes_Mp58WJZiiaqs0OZgBjzupSYmqbRNmO6wxtMDdu-9B3dcx3bsT3bcomGt6pL9y8d37NdQ3d8yyK-_azh3y1fvySeRUzHND1fJ45HXA1DkkkuZvv7q73Gnv8CVgR0WA?type=png)](https://mermaid.live/edit#pako:eNqtlFtvmzAYhv-K69xsEmk5mYMVVcqBVKqaJWq7XWxMk4GPBA1wZMyaLOt_nyE0TTJN6kW5QLyfv_d5fRDe4ZgngCleCrZeocdJWCL1DL-FeCGgqigahvj7vjh6LT4shuPgMLB_j9XwbP4l-HEXTB8Hkbi6HmUlE1uKdF03dL0tTSDOCpZTZB_cE-W7_TxbnFqU4dxiOGeJgXKOMvmUVYDm92i-BsFkxsvWtg9FfzrUmXWqrPdQ1blss_6ZnrnXIy5XKMpkhZgAVIG8OOPcNFNomljcJFcINhDXEi5a-6CSgpfL6xn_BXeQyg8fB1ddqR0ffpqc9N3Wxfqo5yxriPr9azTuDqMV3XGNWxF0-3ksglZMu0W34uaYWcltDoqcZnlOe1GUQBppTfxPoD3Dd53E7GT_KUvkilrrjRbznAvaa3b1CDJ6D8i4g6Rp6sf2AZISNzXcU4j5X8jkPSDBC8QCkpIDxI2MlL15OdMOEhMw2CuEEC8y07dCbjoII4nD3APEBDexzmZin0CwhgsQBcsS9YPvGmSI5QoKCDFVn-qYmPoBQhyWz6qV1ZI_bMsYUylq0LDg9XKFacrySql6nTAJk4ypi6I4VNes_Mp58WJZiiaqs0OZgBjzupSYmqbRNmO6wxtMDdu-9B3dcx3bsT3bcomGt6pL9y8d37NdQ3d8yyK-_azh3y1fvySeRUzHND1fJ45HXA1DkkkuZvv7q73Gnv8CVgR0WA)

> **What's happening?**
>
> 1. Player presses **A** (MOVE_LEFT) and **SPACE** (JUMP) simultaneously
> 2. Each key maps to a unique bit position
> 3. The `|` (OR) operator combines both bits: `000100 | 010000 = 010100`
> 4. Result has **both bits set**, so both actions execute in the same frame


**Implemented Commands:**

- [x] MOVE_UP
- [x] MOVE_DOWN
- [x] MOVE_LEFT
- [x] MOVE_RIGHT
- [x] JUMP
- [x] FIRE
- [ ] DODGE (task)
- [ ] DASH (task)

## Quick Start <a name="quick-start"></a>

### 1. Clone the Repository

```bash
git clone https://MuddyGames@bitbucket.org/MuddyGames/raylib_project_command.git raylib_practical_command
cd raylib_practical_command
```

### 2. Install Toolchain (if needed)

```bash
make toolchain
```

### 3. Build and Run

```bash
make build
make run
```

## Architecture <a name="architecture"></a>

The system consists of four main components:

1. **Command System**

   - Uses bit flags
   - Supports multiple simultaneous commands
   - Command function pointers (to be implemented)
   - Command type enumeration

2. **Mediator**

   - Decouples player from command execution
   - Manages communication between Input System and Command System
   - Handles command routing
   - Prevents direct dependencies between INPUT | Game

3. **Input Manager**

   - Keyboard input handling
   - Controller support
   - Keyboard Support
   - Polls input device
   - Converts raw input into bitwise command flags

4. **Game System**

   - Initialisation
   - Update loop
   - Rendering
   - Player (Command) updates via mediator

## Project Structure <a name="project-structure"></a>

```
raylib_project_command/
├── include/
│   ├── command.h           # Command bit flags
│   ├── mediator.h          # Mediator pattern
│   ├── input_manager.h     # Input polling
│   ├── player.h            # Player struct and actions
│   ├── game.h              # Game system
│   └── constants.h         # Screen dimensions, FPS, game constants
├── src/
│   ├── command.c           # Command execution logic
│   ├── mediator.c          # Mediator (command routing)
│   ├── input_manager.c     # Keyboard / controller input handling
│   ├── player.c            # Player action implementations
│   ├── game.c              # Game loop and rendering
│   └── main.c              # Entry point
├── Makefile                # Build configuration
└── README.md               # Project ReadME.md (this file)
```

## Command System <a name="command-system-deep-dive"></a>

Command uses bit flags:

```c
typedef enum
{
	NONE		 	= 0,		// No command
	MOVE_UP 		= 1 << 0,	// Binary: 000001
	MOVE_DOWN 		= 1 << 1,	// Binary: 000010
	MOVE_LEFT 		= 1 << 2,	// Binary: 000100
	MOVE_RIGHT 		= 1 << 3,	// Binary: 001000
	JUMP 			= 1 << 4,	// Binary: 010000
	FIRE 			= 1 << 5,	// Binary: 100000
	// Add new commands here.... e.g. DODGE, DASH
	COUNT			= 6 // Total number of commands
} Command;
```

_Example:_

`MOVE_LEFT | JUMP` -> perform both actions in the same frame.

## Implementation Guide <a name="implementation-guide"></a>

### Command System

```c
// Command type enumeration
typedef enum {
    // ..
    MOVE_UP 		= 1 << 0,	// Binary: 000001
	MOVE_DOWN 		= 1 << 1,	// Binary: 000010
	MOVE_LEFT 		= 1 << 2,	// Binary: 000100
	MOVE_RIGHT 		= 1 << 3,	// Binary: 001000
    // Add more commands as needed
    // ..
} Command;
```

### Mediator Usage

```c
// Mediator structure
typedef struct {
    Player* player;
} Mediator;

// Mediator functions
void CreateMediator(Mediator* mediator);
void MediatorHandleCommand(Mediator* mediator, Command* command, float deltaTime);
```

### Input System Setup

```c
// Input manager
Command PollInput();
```

## Input System <a name="input-system"></a>

The input system supports:

- Keyboard mapping through key mappings
- Controller integration via button mappings

## Usage Examples <a name="usage-examples"></a>

Basic implementation example:

```c

// Initialise systems
GameData gameData;
Mediator* CreateMediator(Player* player);

// Game loop
while (!WindowShouldClose()) {
    ...
    Command command = PollInput();
    MediatorHandleCommand(gameData.mediator, &command, deltaTime);
    UpdateGame(&gameData, deltaTime);
    DrawGame(&gameData);
    ...
}
```

## Tasks <a name="tasks"></a>

### Task 1: Add a New Player Action (e.g. DODGE)

1. Add a new command flag in `command.h`:

```c
DODGE = 1 << 6,
```

2. Create the new player behaviour in `player.c`:

```c
void Dodge(Player* p);
```

### Task 2: Route the new Command

```c
if (IsCommandActive(command, DODGE)) {
    Dodge(player);
}
```

### Task 3: Add Input Binding for the New Action

```c
if (IsKeyPressed(KEY_LEFT_SHIFT))
	command |= DODGE;
```

### Task 4: Combine Commands

Experiment with combinations such as:

- MOVE_RIGHT + FIRE
- MOVE_LEFT + JUMP
- MOVE_UP + DODGE

### Task 5: Create a Simple Command Combo

Examples:

- Double‑tap D -> perform DODGE
- JUMP -> FIRE -> "Jump shot"

### Task 6: Stretch Goals

- Command recording + replay
- Configurable controls from file (Keymappings)

## Resources <a name="resources"></a>

### Design Pattern References

- [Command Pattern in C](https://www.geeksforgeeks.org/command-pattern/) - with examples
- [Game Programming Patterns](http://gameprogrammingpatterns.com/command.html) - with examples
- [Mediator Pattern Explained](https://refactoring.guru/design-patterns/mediator)

### Raylib Documentation

- [Raylib Website](https://www.raylib.com/)
- [Raylib Github](https://github.com/raysan5/raylib)
- [Input Handling in C Raylib](https://www.raylib.com/examples.html)

## Support <a name="support"></a>

For questions and support, contact:

- MuddyGames

[Back to top](#command-pattern-guide)
