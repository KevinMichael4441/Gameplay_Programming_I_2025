# Missile Defence (Mini Project)

## Project Overview
The **Missile Defence** mini project is a **console-based C game** simulating missile targeting and defence strategies.  

You'll use **structs**, **enums**, and **functions** to implement linear gameplay mechanics: from selecting a warhead to updating missile positions and checking if a target is hit.  

This project builds skills in:

- **C programming fundamentals** (structs, enums, pointers, function pointers).
- **Makefile build systems** for cross-platform compilation.
- **Debugging with GDB**.
- **Strategic game logic design**.

By the end, you will have a working terminal-based game and a solid foundation for game development in C.

---

## Getting Started

Getting up and running with Missile Defence

### Windows Setup

#### 1. Install MSYS2
Download and install: [https://www.msys2.org](https://www.msys2.org)

#### 2. Install required tools
In the MSYS2 terminal, run:
```bash
pacman -S make git mingw-w64-ucrt-x86_64-gcc
```

### Linux Setup

#### 1. Installed by Default
Most Linux distributions already have the required tools installed by default:
- `gcc` (GNU Compiler Collection)
- `make` (Build automation tool)
- `git` (Version control)

If any are missing, install them using your distribution's package manager:

#### 2. Install required tools
**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential git
```

**Fedora/RHEL:**
```bash
sudo dnf install gcc make git
```

**Arch Linux:**
```bash
sudo pacman -S gcc make git
```

### 3. Clone the StarterKit
```bash
git clone https://MuddyGames@bitbucket.org/MuddyGames/missiledefencegame.git
cd missiledefencegame
```

### 4. Build & Run
```bash
make
```
This will:

- Compile the project (`src/main.c`).
- Output the binary into the `bin/` directory.
- Run the executable automatically.

To clean build artifacts:
```bash
make clean
```

---

## 🕹️ Missile Defence Game Features

- **Menu System**: 
    - Simple text menu to launch missiles or quit.

- **Password Check**:
    - A password must be entered to arm a missile. (Default: `DEFCON1`)

- **Missile Mechanics**:
    - Explosive Warhead: Hits only the direct grid square.
    - Nuclear Warhead: Damages a 3x3 area.

- **Targeting**:
    - Enemy target coordinates stored in `Target`.
    - Missile tracks its own position and updates with each move.

- **Gameplay Loop**:
    - Player chooses a warhead.
    - Enters password to arm missile.
    - Missile launches and updates its trajectory.
    - Game checks for a hit based on warhead type.
    - Results are displayed in the console.

---

## 💥 Warhead Mechanics (Damage Spread)

Different warheads have different impact radii:

- **Explosive Warhead** → Affects 1×1 grid square (direct hit only).
- **Nuclear Warhead** → Affects 3×3 grid area (impact square + all adjacent squares).

[![](https://mermaid.ink/img/pako:eNp1ks1u4jAURl_FuuuAIAkxZDFVSzrQRbuhUtUSFlZ8SaxJbMZxZmAS3r2OCdMuWi8s_5z7-dhyC5niCDHsS_U3K5g25DlJJbHtdvso6lqUSB6qA8vMjoxGP8hd-1KIrCAvTBfI-M05lRf8rt_u7o-HUtXiD3ZkuV0WmP0iGyFzG7LSgpPN74Zp3F0qli4waZ-ZztEQZoaDBqqP7rHEBb9i3ZH77cAmWButTsh3n5kn1ZGfztptfPZ6arISme7IarAKjgG51chspxrJr3e81Kyc2fpqJqRDr0LrD6GH74TWXwmBBxXqigluH7ztwRRMgRWmENshxz1rSpNCKs8WZY1Rm5PMIDa6QQ-sZ15AvGdlbWfNgTODiWC5ZtX_1QOTb0pV15Jc90cN5Sg56qW9rIHYnzoW4haOdjYJx-GEziMaBtMonES-ByeIR_NxOF1EQUT9KKCLYDE7e_DPxU_Gc9-PfEqpP6NzOltEHiAXRunHy3dyv-r8DjTUvl4?type=png)](https://mermaid.live/edit#pako:eNp1ks1u4jAURl_FuuuAIAkxZDFVSzrQRbuhUtUSFlZ8SaxJbMZxZmAS3r2OCdMuWi8s_5z7-dhyC5niCDHsS_U3K5g25DlJJbHtdvso6lqUSB6qA8vMjoxGP8hd-1KIrCAvTBfI-M05lRf8rt_u7o-HUtXiD3ZkuV0WmP0iGyFzG7LSgpPN74Zp3F0qli4waZ-ZztEQZoaDBqqP7rHEBb9i3ZH77cAmWButTsh3n5kn1ZGfztptfPZ6arISme7IarAKjgG51chspxrJr3e81Kyc2fpqJqRDr0LrD6GH74TWXwmBBxXqigluH7ztwRRMgRWmENshxz1rSpNCKs8WZY1Rm5PMIDa6QQ-sZ15AvGdlbWfNgTODiWC5ZtX_1QOTb0pV15Jc90cN5Sg56qW9rIHYnzoW4haOdjYJx-GEziMaBtMonES-ByeIR_NxOF1EQUT9KKCLYDE7e_DPxU_Gc9-PfEqpP6NzOltEHiAXRunHy3dyv-r8DjTUvl4)

### 🎯 Explosive Warhead (1×1 Impact)

```
. . . . .
. . . . .
. . X . .   ← Only the direct hit square is damaged
. . . . .
. . . . .
```

### ☢️ Nuclear Warhead (3×3 Impact)

```
. . . . . .
. . # # # .
. . # X # .   ← Center hit + all adjacent squares
. . # # # .
. . . . . .
```

**Legend:**
- `.` = Undamaged area
- `X` = Impact point
- `#` = Damage area

---

## Code Structure

### Main Components
- **`Coordinates` struct** → Holds X/Y positions.  
- **`WarHead` enum** → Defines `EXPLOSIVE` or `NUCLEAR`.  
- **`Target` struct** → Stores enemy position.  
- **`Missile` struct** → Stores payload, coordinates, target, armed status, and function pointers (`arm`, `update`).  

### Functions
- `armMissile(Missile *missile)` → Toggle armed status with password check.  
- `updateMissile(Missile *missile)` → Move missile position forward.  
- `printCoordinates(Coordinates c)` → Print position to console.  

- Future functions (see specification):
    - `initializeGame()`  
    - `displayMenu()`  
    - `selectWarhead()`  
    - `updateMissilePosition()`  
    - `checkHit()`  

---

## Gameplay Flow (Flowchart)

[![](https://mermaid.ink/img/pako:eNp1UEtPAjEQ_ivNHDwhIi9xDxrcRcCoMQFjtMuh2Q5s425L2m4UWf673S74SuxpvvkeM9MtJIojBLDM1FuSMm3JPIolcW9IZ7bCY5bjghwfX5ArOpXCCpaJD6zbtfLKsyGNhFlnbEPuUBZ7KqyocoYZJpY8MZ0i4yWJ6Eha1OSBGfOmNCdHZKhzcieMERn-so7ehS3JizPww8iajvzQEZ2hPRjJgzJuPyX3CSMvuaa3rJBJ-if-2pNj-rjmzOJ_EWOvmmzDFJNXMhH2clcTE7_dM5qSTOmc6ZVbI0JjtdogX_zU3KuS3NBDfqikFbJAc-IuMl_XTOsvrMFNDaABKy04BFYX2IAcdc4qCNtKFoNNMccYAldyXLIiszHEcudsayZflMoPTq2KVQrBkmXGocIfHAm20uxbgpKjDlUhLQQ9nwDBFt4h6PT7zXZ3cNofnHd7ndO2IzcQdAdNV7ZaZ_32eacidg348CNbzcFZb_cJCy-5Fw?type=png)](https://mermaid.live/edit#pako:eNp1UEtPAjEQ_ivNHDwhIi9xDxrcRcCoMQFjtMuh2Q5s425L2m4UWf673S74SuxpvvkeM9MtJIojBLDM1FuSMm3JPIolcW9IZ7bCY5bjghwfX5ArOpXCCpaJD6zbtfLKsyGNhFlnbEPuUBZ7KqyocoYZJpY8MZ0i4yWJ6Eha1OSBGfOmNCdHZKhzcieMERn-so7ehS3JizPww8iajvzQEZ2hPRjJgzJuPyX3CSMvuaa3rJBJ-if-2pNj-rjmzOJ_EWOvmmzDFJNXMhH2clcTE7_dM5qSTOmc6ZVbI0JjtdogX_zU3KuS3NBDfqikFbJAc-IuMl_XTOsvrMFNDaABKy04BFYX2IAcdc4qCNtKFoNNMccYAldyXLIiszHEcudsayZflMoPTq2KVQrBkmXGocIfHAm20uxbgpKjDlUhLQQ9nwDBFt4h6PT7zXZ3cNofnHd7ndO2IzcQdAdNV7ZaZ_32eacidg348CNbzcFZb_cJCy-5Fw)

---

## Testing

Compile with make (ensures code follows conventions, no syntax errors).

Use GDB to debug:

- `gdb ./bin/missiledefence.bin` Linux / MacOS | `gdb ./bin/missiledefence.exe` on Windows
- Run (`r`), step through (`n`, `s`), set breakpoints (`b`).

Confirm:

- Missile only arms with correct password.
- Missile positions update correctly.
- Explosive and nuclear warheads apply correct damage radii.
- Menu navigation works without crashes.

---

## Future Enhancements

Once the game is complete, you can extend it with additional features for more depth and challenge:

### Multiple Targets

- Place multiple enemy targets on the grid.
- Game continues until all targets are destroyed.

### Scoring System

- Award points for each successful hit.
- Deduct points for missed missiles.

### Different Target Types

- Small targets: only vulnerable to explosive warheads.
- Large or shielded targets: require nuclear warheads.

### Moving Targets

- Enemy targets shift position after each turn.
- Forces the player to anticipate movement.

---

## GDB Commands

| Command | Description |
|---------|-------------|
| `run` or `r` | Executes the program from start to end. |
| `break` or `b` | Sets a breakpoint on a particular line. |
| `disable` | Disables a breakpoint |
| `enable` | Enables a disabled breakpoint. |
| `next` or `n` | Executes the next line of code without diving into functions. |
| `step` | Goes to the next instruction, diving into the function. |
| `list` or `l` | Displays the code. |
| `print` or `p` | Displays the value of a variable. |
| `quit` or `q` | Exits out of GDB. |
| `clear` | Clears all breakpoints. |
| `continue` | Continues normal execution |