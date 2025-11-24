# README #

This project is a Makefile starter kit for a console-based turn-based game titled **Player vs NPC**. It serves as a foundation for learning object-oriented programming concepts in C++ through a simple game structure.

## Project Overview
**Player vs NPC** is a console-based turn-based game where players can engage in strategic battles against non-player characters (NPCs). The game emphasizes object-oriented programming concepts in C++, allowing players to develop their skills while enjoying gameplay.

## Table of Contents
- [Project Overview](#project-overview)
- [Code Structure](#code-structure)
- [Classes Diagram](#classes-diagram)
- [Prerequisites](#prerequisites)
- [Instructions for Linux](#instructions-for-linux)
- [Instructions for Windows using MSYS2](#instructions-for-windows-using-msys2)
- [Set Up Your Environment](#set-up-your-environment)
- [Clone the Repository](#clone-the-repository)
- [Build the Project](#build-the-project)
- [Running the Game](#running-the-game)
- [Useful Resources](#useful-resources)

## Code Structure

- **GameObject**: An abstract class that defines common properties and methods for all game objects, including:
    - **Health**: Represents the current health of the game object.
    - **Methods**: Includes pure virtual methods for `attack` and `walk`, as well as a virtual method for `defend`.

- **Player**: Inherits from `GameObject` and represents the player character in the game. It includes:
    - **Methods**: Specific implementations for `walk`, `attack`, and `defend`, as well as a unique method for `charge`.

- **NPC**: Also inherits from `GameObject` and represents the non-player character. It includes:
    - **Methods**: Specific implementations for `walk`, `attack`, and `defend`, as well as a unique method for `taunt`.

### Classes Diagram
[![](https://mermaid.ink/img/pako:eNrdVE2P0zAQ_Ssjn1q0y5ZrgQMUBAgtrdQ95jJrTxqzjh0546Jq2f_OOOm2abOiB25YkeKPN2_evDjzqHQwpOZKO2zbTxY3EevC-8AEhVouYRF8GxzBF6zpNdxVtgV5ENaMkcl8twwcYBWDSZpk_y5FDx-xJXMSWqg9aRlit7G8_0maJceH-5YjynSRFWRc4TsxA1jhQcYg7N3v62tYOdxRfPnsx2pxfjAfzCfWM1TwHt7MZtMxMJ9uiL8SOq4mU9BSCY9hWxs5oYNtsAaQGfXDZCDklVgkLFNJM7sQbKgkbyZjKSeoX-geMuZoUW_BYx92SUbYUozWUMbe3MC3unFUk2dkGzyEEpoU6aCrJ4KauApmkOBZ6gndeEiCZZOJ0bndEdtHj1n70i5wdqzrhrQtrQY70v_sz4FVV7l04f37ENbbTlB3O3tP863uw4Er6u_T09F4Wf8HrjMmzxftOfNHSs_mdLGdN83gP3zpY779548p1qsrVVOs0RppVp31hZLkubPMZSoVYnKc20eGYuKw3nmt5hwTXakY0qZS8xJdK6vUGGTaN7uz3c_GcoiHTeqWt_semV9PfwDTXKYh?type=png)](https://mermaid-js.github.io/mermaid-live-editor/edit#pako:eNrdVE2P0zAQ_Ssjn1q0y5ZrgQMUBAgtrdQ95jJrTxqzjh0546Jq2f_OOOm2abOiB25YkeKPN2_evDjzqHQwpOZKO2zbTxY3EevC-8AEhVouYRF8GxzBF6zpNdxVtgV5ENaMkcl8twwcYBWDSZpk_y5FDx-xJXMSWqg9aRlit7G8_0maJceH-5YjynSRFWRc4TsxA1jhQcYg7N3v62tYOdxRfPnsx2pxfjAfzCfWM1TwHt7MZtMxMJ9uiL8SOq4mU9BSCY9hWxs5oYNtsAaQGfXDZCDklVgkLFNJM7sQbKgkbyZjKSeoX-geMuZoUW_BYx92SUbYUozWUMbe3MC3unFUk2dkGzyEEpoU6aCrJ4KauApmkOBZ6gndeEiCZZOJ0bndEdtHj1n70i5wdqzrhrQtrQY70v_sz4FVV7l04f37ENbbTlB3O3tP863uw4Er6u_T09F4Wf8HrjMmzxftOfNHSs_mdLGdN83gP3zpY779548p1qsrVVOs0RppVp31hZLkubPMZSoVYnKc20eGYuKw3nmt5hwTXakY0qZS8xJdK6vUGGTaN7uz3c_GcoiHTeqWt_semV9PfwDTXKYh)

### Gameplay Flow
[![](https://mermaid.ink/img/pako:eNp9k1FvmzAUhf_KlR_2RCIggQS0bkohTVJtXatWmxLIgwVOQAM7MqZdSvLfawwkPGzjAcG955zP5uIKRSwmyEW7jL1FCeYCXvyQhhTkNQsWOCfwLGR5C4PBF7gNVjQVKc7SdwJ104UfPIJP8MJZlkFRK-EtFQkYug5LgjORbJuwWxXgNZHfGDu0uR3MU30_eMzwkXCYRSJlFFyYCYGj38A4-GRHaNzG-Uo-rzp5lr6Sr-emN697pwd2gk3wK6VU9m-aFW77gjUpTnAXPDx6_6U1ljvFW1RK3YctLrD1FSY_yrbfVqhl4CVEhjefBX7irCTFBbBUgFW3oVb0-Qb0jrS6Rm36lZp9rxb2F9P91bTuV2qT17HXQT1FufqiGfNTMKexmm-7i03QDPgfEqShnPAcp7H8k6raEiKRkJyEyJWPMdnhMhMhCulZSnEp2PORRsgVvCQa4qzcJ8jd4ayQb-UhxoL4Kd5znF-qB0w3jOWdZc9rVGuXYyLcYyUVyLVMW4mRW6E_yDV1azjWLXvk2OPpeDSxNHRE7mDkWEPDkHfTHtkTYzqxzhp6V_nm0J6Op4ZtO6ZpGs7E0RCJU8H49-acqONy_gC4JvmT?type=png)](https://mermaid.live/edit#pako:eNp9k1FvmzAUhf_KlR_2RCIggQS0bkohTVJtXatWmxLIgwVOQAM7MqZdSvLfawwkPGzjAcG955zP5uIKRSwmyEW7jL1FCeYCXvyQhhTkNQsWOCfwLGR5C4PBF7gNVjQVKc7SdwJ104UfPIJP8MJZlkFRK-EtFQkYug5LgjORbJuwWxXgNZHfGDu0uR3MU30_eMzwkXCYRSJlFFyYCYGj38A4-GRHaNzG-Uo-rzp5lr6Sr-emN697pwd2gk3wK6VU9m-aFW77gjUpTnAXPDx6_6U1ljvFW1RK3YctLrD1FSY_yrbfVqhl4CVEhjefBX7irCTFBbBUgFW3oVb0-Qb0jrS6Rm36lZp9rxb2F9P91bTuV2qT17HXQT1FufqiGfNTMKexmm-7i03QDPgfEqShnPAcp7H8k6raEiKRkJyEyJWPMdnhMhMhCulZSnEp2PORRsgVvCQa4qzcJ8jd4ayQb-UhxoL4Kd5znF-qB0w3jOWdZc9rVGuXYyLcYyUVyLVMW4mRW6E_yDV1azjWLXvk2OPpeDSxNHRE7mDkWEPDkHfTHtkTYzqxzhp6V_nm0J6Op4ZtO6ZpGs7E0RCJU8H49-acqONy_gC4JvmT)


### Sequence
[![](https://mermaid.ink/img/pako:eNqVkk1vwjAMhv-K5RNIBZV-jmhDQkXaDhugjdPEJWoNVLQJC8kEQ_z3pS3dmDgth8h2Hr924pwwlRkhwz19GBIpTXK-VrxcCrBrx5XO03zHhYZHXtJtdF7wIynge5ipFDqN273lpvOkghZKFgV0rHdhmn0qNYH8tEJVFcces9qCZyl3DBIpdC4M7cFYo2iLPhEv9AbuH8CF2Wtd4ip0rV9p9UajJo-B5ltaGCU63RZoTnqWqVAG41TnUgAdKDWaMuiMtebpFqSCCa1IZN0_wnXDv6qXS82T_wiigyWpkueZncapklii3pB9dGTWzGjFTaGXuBRni3Kj5dtRpMi0MuSgkma9Qbbixd56Zpdx3Y7yJ2oH8S5l2aasVVXqkm47IJVI-77IgrBmkZ3wgMwPgr7vDb0wGISuP3QjB4_IPDeuotEwisLQiy10dvCrVnf7sRd7XhB6gyi4C-PYd5CyXEv10ny1-sedvwFw5MZ6?type=png)](https://mermaid.live/edit#pako:eNqVkk1vwjAMhv-K5RNIBZV-jmhDQkXaDhugjdPEJWoNVLQJC8kEQ_z3pS3dmDgth8h2Hr924pwwlRkhwz19GBIpTXK-VrxcCrBrx5XO03zHhYZHXtJtdF7wIynge5ipFDqN273lpvOkghZKFgV0rHdhmn0qNYH8tEJVFcces9qCZyl3DBIpdC4M7cFYo2iLPhEv9AbuH8CF2Wtd4ip0rV9p9UajJo-B5ltaGCU63RZoTnqWqVAG41TnUgAdKDWaMuiMtebpFqSCCa1IZN0_wnXDv6qXS82T_wiigyWpkueZncapklii3pB9dGTWzGjFTaGXuBRni3Kj5dtRpMi0MuSgkma9Qbbixd56Zpdx3Y7yJ2oH8S5l2aasVVXqkm47IJVI-77IgrBmkZ3wgMwPgr7vDb0wGISuP3QjB4_IPDeuotEwisLQiy10dvCrVnf7sRd7XhB6gyi4C-PYd5CyXEv10ny1-sedvwFw5MZ6)

---

### Prerequisites

## Getting Started

Getting up and running with OO Console Game

1. **Visual Studio Code**
   - Download and install [Visual Studio Code](https://code.visualstudio.com/).

2. **C/C++ Extension for Visual Studio Code**
   - Install the C/C++ extension by searching for `@ext:ms-vscode.cpptools` in the Extensions view (`Ctrl+Shift+X`).

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
git clone https://MuddyGames@bitbucket.org/MuddyGames/oo-console-game.git
cd oo-console-game
```

### 4. Build & Run
```bash
make
```
This will:

- Compile the project (`src/main.cpp`).
- Output the binary into the `bin/` directory.
- Run the executable automatically.

To clean build artifacts:
```bash
make clean
```
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

## Useful Resources ##
* [GNU Make Manual](http://www.gnu.org/software/make/manual/make.html)
* [Makefile Tutorial](https://makefiletutorial.com/)
* [GDB GNU Debugger Project](https://www.gnu.org/software/gdb/)
* [Enabling build and debugging in Visual Studio Code](https://dev.to/talhabalaj/setup-visual-studio-code-for-multi-file-c-projects-1jpi)
* Debugging with VSC beyond return point may result in the following error message being displayed [pop up](https://github.com/Microsoft/vscode-cpptools/issues/1123)