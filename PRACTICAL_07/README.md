# Raylib Collision Kit <a name="raylib-collision-kit"></a>

A cross-platform collision detection toolkit built with Raylib and the cute_c2 library, providing ready-to-use collision detection implementations for 2D games. This toolkit enables developers to quickly implement and visualise various collision detection techniques in their games. The sample project opens a simple Raylib window showing a player circle that moves with the mouse and changes colour when colliding with NPC shapes.

## Table of Contents

- [Overview](#overview)
- [Quick Start](#quick-start)
- [Project Structure](#project-structure)
- [Building and Running](#building-and-running)
- [Collision Implementation Guide](#collision-implementation-guide)
- [Testing and Visualisation](#testing-and-visualisation)
- [Toolchain Installation](#toolchain-installation)
- [Development Workflow](#development-workflow)
- [Resources](#resources)
- [Support](#support)

## Overview <a name="overview"></a>

This collision kit provides:

- **cute_c2 Integration**: Lightweight, efficient collision detection library
- **Multiple Shape Support**: Circle, Capsule, AABB (Rectangle), and Ray collision detection
- **Visual Debugging**: Real-time collision visualization with color-coded feedback
- **Ready-to-Use StarterKit**: Pre-configured project with example implementations
- **Cross-Platform Support**: Works on Windows (MSYS2), Linux (Debian), and MacOS

**Implemented Collision Types:**

- [x] Circle to Circle
- [x] AABB to AABB, Circle, Capsule
- [ ] Capsule to AABB (To be implemented)
- [ ] Ray to Circle, AABB, Capsule (To be implemented)

## Quick Start <a name="quick-start"></a>

### 1. Clone the Repository

```bash
git clone https://MuddyGames@bitbucket.org/MuddyGames/raylib_project_collision.git raylib_practical_collision
cd raylib_practical_collision
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

## Project Structure <a name="project-structure"></a>

```
raylib_collision/
├── include/
│   ├── constants.h        # Constants such as screen width
│   ├── cute_c2.h          # cute_c2 collision detection library
│   ├── game_object.h      # Player and NPC
│   ├── game.h             # Game update methods and collision logic
│   └── tests.h            # Sample tests
├── src/
│   ├── cute_c2_impl.c     # define CUTE_C2_IMPLEMENTATION
│   ├── game.c             # Game loop and collision implementation
│   ├── main.c             # Main entry point and demo application
│   └── tests.c            # Sample tests implementation
├── resources/             # Game assets (sprites, textures)
│   └── player.png
├── Makefile               # Build configuration
└── README.md              # Project ReadME.md (this file)
```

[![](https://mermaid.ink/img/pako:eNqNVduO2jAQ_RXLT60EKCRc88Zmq6pqWaGl-1JAK5MYYimxI9tBUODf13bu2bTCD048Pmfm2DOTXKHPAgxd2O_3t1QSGWHXY1FEBGEUrCXiEvOfRAKPxQkTRGrzK46QfhEhSQTYUsPF_JmgI0fxlgI1vqMYPyOJwO3W799uYBWhC-bABT6jEhEqOmDsCl5WnsJsYYHavLwt35VxvdvCjJHNGpd7NnIDzH9fEmy4IRJAqkXBqGF9e4koObAo-KSkQDGN8gj3o8xbSvWRYxzvMW97NNjF4unpMaSHEpH-x2025zdVKi61NPVmc7ldwk_lHSRf8oR9LQLkYjuwMaEPgNC5AhWH6cChh1D75rFrqclroQ42Z_fle8IIlWJj76oQDVorBmU8RhEwZ2sV3DVb66FcgsxxZcuzkJhHZdb5pIkvNs6uyfeLpvFYSmWd4oeIq0QLgY54Y1tWTrx35LymqUysbx7Vhip3xnU4xjscaX3XBrjqDdMT__ajx56xCBCR0Qg91vWU9xznL9VmVsx-HqxDVkNHTR-maQy8H6_er28to67BNm6xWr8VwHtnFzQu8ASSanmIGJKAd5JNvbeouiGaBlX8nZHzCm_xUXO5f0xJecfXdnWpomq7CHAiQ9MLjVCfW6WxTTsDn-oRM_fntuGSM2EPHjkJoCt5inswxqrH9BIaF1soQxyrj6_uwQAfUBpJ3X6aliD6h7G4YHKWHkPoHlAk1CpNAiRx_hMpIZiqsjE9BV1nZBkf0L3CM3SH9nQwt0bjiTO3nJk1m_TgBbrT4cCeDmeq0SYzZzx3Zvce_GuCWoP5yHKcseWMR7PJZGQPexAHRDK-zP6B5ld4_wCLMhex?type=png)](https://mermaid.live/edit#pako:eNqNVduO2jAQ_RXLT60EKCRc88Zmq6pqWaGl-1JAK5MYYimxI9tBUODf13bu2bTCD048Pmfm2DOTXKHPAgxd2O_3t1QSGWHXY1FEBGEUrCXiEvOfRAKPxQkTRGrzK46QfhEhSQTYUsPF_JmgI0fxlgI1vqMYPyOJwO3W799uYBWhC-bABT6jEhEqOmDsCl5WnsJsYYHavLwt35VxvdvCjJHNGpd7NnIDzH9fEmy4IRJAqkXBqGF9e4koObAo-KSkQDGN8gj3o8xbSvWRYxzvMW97NNjF4unpMaSHEpH-x2025zdVKi61NPVmc7ldwk_lHSRf8oR9LQLkYjuwMaEPgNC5AhWH6cChh1D75rFrqclroQ42Z_fle8IIlWJj76oQDVorBmU8RhEwZ2sV3DVb66FcgsxxZcuzkJhHZdb5pIkvNs6uyfeLpvFYSmWd4oeIq0QLgY54Y1tWTrx35LymqUysbx7Vhip3xnU4xjscaX3XBrjqDdMT__ajx56xCBCR0Qg91vWU9xznL9VmVsx-HqxDVkNHTR-maQy8H6_er28to67BNm6xWr8VwHtnFzQu8ASSanmIGJKAd5JNvbeouiGaBlX8nZHzCm_xUXO5f0xJecfXdnWpomq7CHAiQ9MLjVCfW6WxTTsDn-oRM_fntuGSM2EPHjkJoCt5inswxqrH9BIaF1soQxyrj6_uwQAfUBpJ3X6aliD6h7G4YHKWHkPoHlAk1CpNAiRx_hMpIZiqsjE9BV1nZBkf0L3CM3SH9nQwt0bjiTO3nJk1m_TgBbrT4cCeDmeq0SYzZzx3Zvce_GuCWoP5yHKcseWMR7PJZGQPexAHRDK-zP6B5ld4_wCLMhex)

**Guidelines:**

- Collision detection logic goes in `src/game.c` and `include/game.h`
- Shape definitions and collision functions use cute_c2 types
- Visual debugging and rendering in `src/main.c`
- Test different collision scenarios in the update loop

## Building and Running <a name="building-and-running"></a>

Use these make commands to build and run:

```bash
# Build desktop version
make build

# Run desktop version
make run

# Rebuild (clean + build)
make rebuild

# Clean build files
make clean

# Build Configurations
make CONFIG=debug          # Debug build (Default)
make CONFIG=release        # Release build

# Install Toolchain
make toolchain
```

## Collision Implementation Guide <a name="collision-implementation-guide"></a>

### Shape Definitions (cute_c2) understanding Collision Types

The cute_c2 library provides the following shape types:

```c
// Circle
c2Circle circle = {
    .p = {x, y},    // Position
    .r = radius     // Radius
};

// AABB (Axis-Aligned Bounding Box / Rectangle)
c2AABB aabb = {
    .min = {x, y},  // Bottom-left corner
    .max = {x, y}   // Top-right corner
};

// Capsule
c2Capsule capsule = {
    .a = {x1, y1},  // Start point
    .b = {x2, y2},  // End point
    .r = radius     // Radius
};

// Ray
c2Ray ray = {
    .p = {x, y},    // Origin
    .d = {dx, dy},  // Direction (normalized)
    .t = length     // Maximum distance
};

```
> Note: Normalize direction with: `c2Norm(c2V(dx, dy))`

### Understanding Collision Manifolds

A collision manifold is the detailed result of a collision, it tells you more than just whether two shapes overlap. The manifold includes a normal (the direction to move the shapes apart), one or two contact points, and a depth value (how far they overlap). In cute_c2, you can create a manifold with functions like `c2CircletoAABBManifold()` or `c2CircletoCapsuleManifold()`.

When a collision occurs `(m.count > 0)`, you can use this information to prevent shapes from sinking into each other. For example, if the player collides with an obstacle, move the player in the **opposite direction** of the normal by the penetration depth:

```c
player.p = c2Sub(player.p, c2Mulvs(m.n, m.depths[0]));
```
In short, the manifold provides all the details needed for proper collision response and smooth, realistic movement after impact. This behaviour is implemented in `game.c` within the StarterKit, where the `Player` interacts with `NPC` objects defined as `c2Circle` shapes.

### Implementing Collision Detection

#### Example 1: Circle to Circle (Pre-implemented)

```c
#include "cute_c2.h"

// Check collision between two circles
int CheckCircleCollision(c2Circle circle1, c2Circle circle2) {
    return c2CircletoCircle(circle1, circle2);
}
```

#### Example 2: AABB to AABB (Pre-implemented)

```c
// Check collision between two AABBs
int CheckAABBCollision(c2AABB aabb1, c2AABB aabb2) {
    return c2AABBtoAABB(aabb1, aabb2);
}
```

#### Example 3: Ray to Circle (To Implement)

```c
// TODO: Implement ray to circle collision
int CheckRayToCircle(c2Ray ray, c2Circle circle, c2Raycast* out) {
    return c2RaytoCircle(ray, circle, out);
}
```

### Collision Flow

[![](https://mermaid.ink/img/pako:eNp1VNty2jAQ_RWN-goUSIzB06YD5hLCJQSSh9bmwdgLaGpLHlmelBr-vZJsEzPT8CAknbO7R0drZdhnAWAL1-t1lwoiQrCQzcKQJIRRNAQBvlCzccjeXapZLj1wLz6i16FLkfz1nbc48ARMvAiQ7YUhBFtUrz-ggTMBgRYsTQCtWEJUom0eM9AEu4hEceidgDdiJBiKFL-g2Zo2dDYyj1-qykVBgL6jvRdeuUPNHTlzxmSeI2fp4YiWKzsp8HwcadY4kwB6PcXw41JFxwo929O1PR-d0cTx2zbhfgiC5f_bKq3fHwzO6LFCUjs3FLu_2rypVNNqKi9O0muufJxoWU_Z1fpS12MO5ItpdZGPT7rOT0jOaFbaxLi0Zj0abquUJTuj-Q1jMH8b3YiY6fSLbEx4UvH7245_fXgn4ihdJYmytBS3-Ci-dKbU5xABVZEpFcB1XD8IUMwIFeU1LK5qnp3NbxIjUsbdaFlqLSstmCTaloDQg5QteFp695yT8sVcL17-E1Htknxcae46WzAOukfKE73kQJW7_jjkqLqjjrApGziCJPEOgBLBZc2i1kYne3XWIFJOVW8f1CcSyga9UZOIUwiyBfYkDK0vfhc6fq-KPH6KTD9FZgWy3_tB0K4i8wLZ7QLY76rI8hqz7_n3uIYj4JFHAvk8ZIrnYnGUN-ViS05lsJeGwsUuvUiqlwq2OVEfW-p-alh_ftjS1tdwql0aEk--HNF1N_boL8aiMuTAVakiHGgA3FaNhK1W1-hqNrYy_Adb7Z7R6DZbpmF2W22jhk_Yqt_1eo2W0TYM8868a953epca_quTtxpm12w3my3jvmPKidmpYQiIYHyRP336Bbz8A3xkhyk?type=png)](https://mermaid.live/edit#pako:eNp1VNty2jAQ_RWN-goUSIzB06YD5hLCJQSSh9bmwdgLaGpLHlmelBr-vZJsEzPT8CAknbO7R0drZdhnAWAL1-t1lwoiQrCQzcKQJIRRNAQBvlCzccjeXapZLj1wLz6i16FLkfz1nbc48ARMvAiQ7YUhBFtUrz-ggTMBgRYsTQCtWEJUom0eM9AEu4hEceidgDdiJBiKFL-g2Zo2dDYyj1-qykVBgL6jvRdeuUPNHTlzxmSeI2fp4YiWKzsp8HwcadY4kwB6PcXw41JFxwo929O1PR-d0cTx2zbhfgiC5f_bKq3fHwzO6LFCUjs3FLu_2rypVNNqKi9O0muufJxoWU_Z1fpS12MO5ItpdZGPT7rOT0jOaFbaxLi0Zj0abquUJTuj-Q1jMH8b3YiY6fSLbEx4UvH7245_fXgn4ihdJYmytBS3-Ci-dKbU5xABVZEpFcB1XD8IUMwIFeU1LK5qnp3NbxIjUsbdaFlqLSstmCTaloDQg5QteFp695yT8sVcL17-E1Htknxcae46WzAOukfKE73kQJW7_jjkqLqjjrApGziCJPEOgBLBZc2i1kYne3XWIFJOVW8f1CcSyga9UZOIUwiyBfYkDK0vfhc6fq-KPH6KTD9FZgWy3_tB0K4i8wLZ7QLY76rI8hqz7_n3uIYj4JFHAvk8ZIrnYnGUN-ViS05lsJeGwsUuvUiqlwq2OVEfW-p-alh_ftjS1tdwql0aEk--HNF1N_boL8aiMuTAVakiHGgA3FaNhK1W1-hqNrYy_Adb7Z7R6DZbpmF2W22jhk_Yqt_1eo2W0TYM8868a953epca_quTtxpm12w3my3jvmPKidmpYQiIYHyRP336Bbz8A3xkhyk)

### Required Implementations

You must implement the following collision types:

1. **Capsule Collisions**

   - `c2CapsuletoAABB()` - Capsule vs AABB
   - `c2CapsuletoCapsule()` - Capsule vs Capsule

2. **Ray Collisions**

   - `c2RaytoCircle()` - Ray vs Circle
   - `c2RaytoAABB()` - Ray vs AABB
   - `c2RaytoCapsule()` - Ray vs Capsule

3. **Additional AABB Collisions**

   - `c2AABBtoCircle()` - AABB vs Circle (if not pre-implemented)
   - `c2AABBtoCapsule()` - AABB vs Capsule

[![](https://mermaid.ink/img/pako:eNp9lM-OmzAQxl_Fml4hCv9K8KFSYC89rFQ1eyrk4IJJLBkbGSNtGuXaa6W2p6qHPkafJy_QV6iBbJIViLl47O8334wlzBFyWVDAYNt2JjTTnGKUSM5Zw6RAD1TTXHfZB8JUk4key8ROkXqPnuJMIBNN-3k4yOB9VXNaUaFJX7Uxa9tkMHBdrNPNntR08Nsi236H4vRaRQt0_v1je4f3RJI-SXSF0PnXn39_v91RtyweHJ00YSrnFJ2__kRDuh1B7j20XsfxGPFe-ZC6aaeM_LSrnrK5ZclwETPY4DJFXxj3FTPuesG89CM5GOT7-IIXwr8S042Cm8OoyS1r9MGMEjuoZJzjN_mKvs2jkezOy9687M_KyUvvssyLwh3J7rzszcv-vBxMyFQUYMFOsQKwVi21oKKqIt0Wjh2Sgd6bbzUDbNKClqTlunsFJ1NWE_FJyuqlUsl2twdcEt6YXVsXRNMHRsyDqq6nyjSkKpGt0IAdd9mbAD7CM2A3WC78MAgDL1z5ThiFFhwAe9HCC4OTBV_6VsvFKvQjE6swcrxg6ToW0IJpqR6H59__BSwgrZabg8iH4U7_AUnCN_k?type=png)](https://mermaid.live/edit#pako:eNp9lM-OmzAQxl_Fml4hCv9K8KFSYC89rFQ1eyrk4IJJLBkbGSNtGuXaa6W2p6qHPkafJy_QV6iBbJIViLl47O8334wlzBFyWVDAYNt2JjTTnGKUSM5Zw6RAD1TTXHfZB8JUk4key8ROkXqPnuJMIBNN-3k4yOB9VXNaUaFJX7Uxa9tkMHBdrNPNntR08Nsi236H4vRaRQt0_v1je4f3RJI-SXSF0PnXn39_v91RtyweHJ00YSrnFJ2__kRDuh1B7j20XsfxGPFe-ZC6aaeM_LSrnrK5ZclwETPY4DJFXxj3FTPuesG89CM5GOT7-IIXwr8S042Cm8OoyS1r9MGMEjuoZJzjN_mKvs2jkezOy9687M_KyUvvssyLwh3J7rzszcv-vBxMyFQUYMFOsQKwVi21oKKqIt0Wjh2Sgd6bbzUDbNKClqTlunsFJ1NWE_FJyuqlUsl2twdcEt6YXVsXRNMHRsyDqq6nyjSkKpGt0IAdd9mbAD7CM2A3WC78MAgDL1z5ThiFFhwAe9HCC4OTBV_6VsvFKvQjE6swcrxg6ToW0IJpqR6H59__BSwgrZabg8iH4U7_AUnCN_k)


[![](https://mermaid.ink/img/pako:eNp1lF1vmzAUhv-K5Um9SqoEQhq4mERIP9I2_QjdJg1y4cIhWAMbwWFrVvW_zzGkc7Q1F47t9znnPeYYXmkiU6AeHQ6HsUCOBXhkWVYFlCCQIZeCPDDMY6GBbc2qnDzNY0HUz49CZDWSXxxzoqdQ33DckOHwM5lH61aQE_IEDZLzF94gF1sSKLdNFz3XWBB9ESnUDTKRkoDXSQEKKgreKOueDDS5iN7rIgGrmtYkmx7txoUOOI8SqwdR-v58vjHVC1PtJ0dJzjV2GekD_GPYoxcdZMZd6q0ro9o1231U6ZWGl6oWBak69APYmNr1QTNO0Ck371H_qX6pkdvIT1Ptj5JcshIWDFnPXXdEt7gxF914q7dWxjn2CapCJVtBkjPBkyPHlebvovtK3xrf075hLuW-8xsTuj9Ac4_4PyVPmUhApz_CHg5Y4JGwqjkCWQoEdQnxbwe68U4HPOrjfuVNywpyAZA-s-RHz913RLd4MBfd-Ki31tE37dM3vYFDu9ZaDqOFTFr9ME5I2D6X6rabSRrcqUvik4wXhfcJ7MzKUlMJeiWZwTRxTWXRK1mW2TAylasPldVBscHJHFMJj3zogJZQl4yn6kV_3XMxxVz1NKaemqaQsbbAmMbiTaGsRRnuREI9rFsY0Fq225x6GSsatWqrlCEsOFNdKN93Kya-S1keQrb13qoPh_37HchWIPUsy55omnqv9IV6tu2eutPZ1DpzLfV_5gzojnrDsT0-HTm2O3Mc1zkb2WPrbUB_awMlTCbOeGpPpq47UunsAYWUo6xX3YdMf8_e_gD_w3QP?type=png)](https://mermaid.live/edit#pako:eNp1lF1vmzAUhv-K5Um9SqoEQhq4mERIP9I2_QjdJg1y4cIhWAMbwWFrVvW_zzGkc7Q1F47t9znnPeYYXmkiU6AeHQ6HsUCOBXhkWVYFlCCQIZeCPDDMY6GBbc2qnDzNY0HUz49CZDWSXxxzoqdQ33DckOHwM5lH61aQE_IEDZLzF94gF1sSKLdNFz3XWBB9ESnUDTKRkoDXSQEKKgreKOueDDS5iN7rIgGrmtYkmx7txoUOOI8SqwdR-v58vjHVC1PtJ0dJzjV2GekD_GPYoxcdZMZd6q0ro9o1231U6ZWGl6oWBak69APYmNr1QTNO0Ck371H_qX6pkdvIT1Ptj5JcshIWDFnPXXdEt7gxF914q7dWxjn2CapCJVtBkjPBkyPHlebvovtK3xrf075hLuW-8xsTuj9Ac4_4PyVPmUhApz_CHg5Y4JGwqjkCWQoEdQnxbwe68U4HPOrjfuVNywpyAZA-s-RHz913RLd4MBfd-Ki31tE37dM3vYFDu9ZaDqOFTFr9ME5I2D6X6rabSRrcqUvik4wXhfcJ7MzKUlMJeiWZwTRxTWXRK1mW2TAylasPldVBscHJHFMJj3zogJZQl4yn6kV_3XMxxVz1NKaemqaQsbbAmMbiTaGsRRnuREI9rFsY0Fq225x6GSsatWqrlCEsOFNdKN93Kya-S1keQrb13qoPh_37HchWIPUsy55omnqv9IV6tu2eutPZ1DpzLfV_5gzojnrDsT0-HTm2O3Mc1zkb2WPrbUB_awMlTCbOeGpPpq47UunsAYWUo6xX3YdMf8_e_gD_w3QP)


## Testing and Visualisation <a name="testing-and-visualisation"></a>

### Visual Debugging

Modify `src/main.c` to visualise collisions:

```c
// Example: Draw collision detection
if (CheckCircleCollision(circle1, circle2)) {
    // Draw with collision color (red)
    DrawCircleV(circle1.p, circle1.r, RED);
    DrawCircleV(circle2.p, circle2.r, RED);
} else {
    // Draw normal color (blue)
    DrawCircleV(circle1.p, circle1.r, BLUE);
    DrawCircleV(circle2.p, circle2.r, BLUE);
}
```

### Testing Strategies

1. **Boundary Testing**: Test shapes at exact collision boundaries
2. **Overlap Testing**: Test various degrees of shape overlap
3. **Movement Testing**: Test collisions with moving objects

### Example Test Implementation

```c
void TestCollisions(void) {
    // Test 1: Circle to Circle
    c2Circle c1 = {{100, 100}, 50};
    c2Circle c2 = {{200, 100}, 50};

    if (c2CircletoCircle(c1, c2)) {
        printf("Circle collision detected!\n");
    }

    // Test 2: AABB to AABB
    c2AABB aabb1 = {{50, 50}, {150, 150}};
    c2AABB aabb2 = {{100, 100}, {200, 200}};

    if (c2AABBtoAABB(aabb1, aabb2)) {
        printf("AABB collision detected!\n");
    }

    // Add more tests for other collision types...
}
```

## Toolchain Installation <a name="toolchain-installation"></a>

### Windows MSYS2: UCRT64 <a name="toolchain-windows"></a>

```bash
make toolchain
```

> **NOTE:** You may need to run this command twice if the package manager is out of date. After updating, restart MSYS2 before running it again.

> **IMPORTANT:** Always use the UCRT64 terminal in MSYS2, not MINGW64 or MSYS terminals.

### Linux Debian: APT Installation <a name="toolchain-linux"></a>

```bash
# Run toolchain script
make toolchain
```

> For general Raylib project setup and configuration, refer to:
> [Raylib Project Template](https://bitbucket.org/MuddyGames/raylib_project/src/main/)

## Development Workflow <a name="development-workflow"></a>

### Using Visual Studio Code

1. **Setup**: Open the project folder in VS Code
2. **Debugging**: Press `F5` to start debugging
3. **Build Tasks**: Access via `Terminal > Run Task`
4. **Breakpoints**: Set breakpoints to inspect collision logic

### Recommended Workflow

1. Implement one collision type at a time
2. Create test cases for each collision type
3. Add visual debugging to verify correctness
4. Test edge cases and boundary conditions (such as zero dimension objects i.e. if player grows or shrinks)
5. Integrate into your game loop

## Resources <a name="resources"></a>

### Raylib Documentation

- [Raylib Website](https://www.raylib.com/)
- [Raylib GitHub](https://github.com/raysan5/raylib)
- [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [Raylib Examples](https://www.raylib.com/examples.html)

### Collision Detection Resources

- [cute_c2 GitHub](https://github.com/RandyGaul/cute_headers)
- [2D Collision Detection Tutorial](https://www.jeffreythompson.org/collision-detection/)
- [Game Physics Tutorial](https://gafferongames.com/post/integration_basics/)

## Support <a name="support"></a>

For questions and support, contact:

- MuddyGames

[Back to top](#raylib-collision-kit)
