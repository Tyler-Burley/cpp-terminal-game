# C++ Terminal Arcade

A simple terminal-based arcade built to gain experience writing in C++. This project currently features two classic grid-based games: **Collect** and **Snake**.

## The Games

### 1. Collect
A simple objective game.
* **Goal:** Move the Player (`P`) to the Goal (`X`) to increase your score.
* **Rules:** The board resets every time you collect a goal.

### 2. Snake
The classic arcade favorite.
* **Goal:** Guide the snake to eat the apple (`X`) to grow.
* **Rules:** Avoid hitting the walls or your own tail. The game ends if you crash.

## Controls
Both games use standard WASD movement.

| Key | Action |
| :---: | :--- |
| **W** | Move Up |
| **A** | Move Left |
| **S** | Move Down |
| **D** | Move Right |
| **Q** | Quit Game |

## Getting Started

### Prerequisites
You need a C++ compiler installed (e.g., `g++` or `clang`).

### Build and Run
Open your terminal in the project directory. Since there are multiple source files, compile them together:

```bash
# Compile the arcade (linking all cpp files)
g++ main.cpp games/snakeGame.cpp games/collectGame.cpp -o arcade

# Run the executable
./arcade

```

### Title
<img width="1090" height="967" alt="Screenshot 2026-01-06 140919" src="https://github.com/user-attachments/assets/5cdabec0-d78f-4315-93a1-b7634404b9db" />

### Snake
<img width="1072" height="893" alt="Screenshot 2026-02-03 115740" src="https://github.com/user-attachments/assets/27e1be50-9d3f-44b8-a550-2cad6c4b56c3" />

### You Lose
<img width="567" height="165" alt="Screenshot 2026-01-06 141102" src="https://github.com/user-attachments/assets/c5bee0ae-398d-4b58-aad9-5cfe6a5026c6" />

### Collect
<img width="1093" height="961" alt="Screenshot 2026-01-06 141141" src="https://github.com/user-attachments/assets/5d6b6c38-f1e1-4a95-881e-9566d6ed8b0e" />
