/**
 * @file SnakeGame.cpp
 * @brief Implementation of the Snake game logic.
 * @author Tyler Burley
 * @version 1.0
 */

#include "SnakeGame.h"
#include <iostream>
#include <cstdlib>
#include <conio.h> // Windows specific for _getch()

SnakeGame::SnakeGame(int size) : grid(size, size) {
    snake_score = 0;
    snake = { 0, 0 };

    spawnGoal();
    updateGrid();
}

void SnakeGame::spawnGoal() {
    int dim = grid.getWidth();
    do {
        apple.x = rand() % dim;
        apple.y = rand() % dim;
    } while ((apple.x == snake.x && apple.y == snake.y));
}

void SnakeGame::move(Direction dir) {
    Point* p = &snake;
    Point next = *p;

    switch (dir) {
    case Direction::UP:    next.y--; break;
    case Direction::DOWN:  next.y++; break;
    case Direction::LEFT:  next.x--; break;
    case Direction::RIGHT: next.x++; break;
    default: break;
    }

    if (grid.isInBounds(next.x, next.y)) {
        *p = next;
        checkGoal();
        updateGrid();
    }
}

void SnakeGame::checkGoal() {
    if (snake.x == apple.x && snake.y == apple.y) {
        snake_score++;
        spawnGoal();
    }
}

void SnakeGame::updateGrid() {
    grid.clear(); // Wipe board (using default 0 or EMPTY)
    grid.set(snake.x, snake.y, TileType::PLAYER);
    grid.set(apple.x, apple.y, TileType::GOAL);
}

void SnakeGame::render() {
    std::cout << "*** SNAKE ***" << std::endl;
    std::cout << "// ----------------------------------------------------" << std::endl;
    std::cout << "// YOUR SCORE    : " << snake_score << std::endl;
    std::cout << "// YOUR POSITION : (" << snake.x << "," << snake.y << ")" << std::endl;
    std::cout << "// ----------------------------------------------------" << std::endl;
    std::cout << std::endl;

    grid.displayMap();
}

void SnakeGame::run() {
    bool is_running = true;
    char input;

    while (is_running) {
        std::cout << "\033[2J\033[H"; // Clear screen

        render();

        std::cout << "\nUse WASD to move (Press 'q' to quit)..." << std::endl;
        input = _getch();

        switch (input) {
        case 'd': move(Direction::RIGHT); break;
        case 'a': move(Direction::LEFT); break;
        case 'w': move(Direction::UP); break;
        case 's': move(Direction::DOWN); break;
        case 'q': is_running = false; break;
        default: break;
        }
    }
}