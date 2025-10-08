# Space Invaders Clone (OpenGL/FreeGLUT)

This project is a modernized implementation of the classic "Space Invaders" game, originally developed for a C++ Object-Oriented Programming course (CSE165). It utilizes **OpenGL** and the **FreeGLUT** library for graphics rendering and game loop management.

---

## 🚀 Key Features

- **State-Based Input:** Player movement and shooting are simultaneously processed by checking the `keysHeld` map every frame (`updatePlayer()`), resolving the issue where one keypress would interrupt another.
- **Object-Oriented Design (OOD):** Core entities like the `Player` and `Bullet` are encapsulated in C++ classes, each managing its own state, drawing, and logic.
- **Modular Game Flow:** Game states (`START_SCREEN`, `PLAYING`, `END_SCREEN`) control what is rendered and processed, ensuring clean transitions.
- **Safe Memory Management:** Bullets are dynamically allocated and memory is correctly freed both during gameplay (when bullets go off-screen) and upon program termination (in the `Player` destructor).

---

## 🛠️ Build and Run Instructions

This project requires a C++ compiler (like g++ or clang) and the **FreeGLUT** library to be installed and configured on your system.

### 1. Build the Executable

Use your project's build shortcut to compile all source files:

```bash
# Use your project's custom build command:
CTRL + SHIFT + B

# Run the executable that is created from the above
./space-invaders
```
