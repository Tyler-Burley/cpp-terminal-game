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

SnakeGame::SnakeGame(int size)
    : grid(size, size), snake{{0, 0}}
{
    snake_score = 0;

    spawnGoal();
    updateGrid();
}

void SnakeGame::spawnGoal() {
    int dim = grid.getWidth();
    bool on_snake = false;

    do {
        apple.x = rand() % dim;
        apple.y = rand() % dim;

        on_snake = false;
        for (const auto& segment : snake) {
            if (apple.x == segment.first && apple.y == segment.second) {
                on_snake = true;
                break;
            }
        }
    } while (on_snake);
}

bool SnakeGame::move(Direction dir) {
    auto head = snake[0];

    switch (dir) {
    case Direction::UP:    head.second--; break;
    case Direction::DOWN:  head.second++; break;
    case Direction::LEFT:  head.first--; break;
    case Direction::RIGHT: head.first++; break;
    default: break;
    }

    //check if you ran into yourself
    for (int i = 0; i < snake.size() - 1; i++)
    {
        if (head == snake[i])
        {
            return false; //for collision
        }
    }

    if (grid.isInBounds(head.first, head.second)) {

        auto prev_tail = snake[snake.size() - 1];

        //update the snake vector
        for (int i = snake.size() - 1; i > 0; i--)
        {
            snake[i] = snake[i - 1];
        }

        snake[0] = head;
        if (checkGoal())
        {
            snake.push_back(prev_tail);
        }
        updateGrid();
        return true;
    }
    else {
        return false;
    }
}

bool SnakeGame::checkGoal() {
    auto head = snake[0];
    if (head.first == apple.x && head.second == apple.y) {
        snake_score++;
        spawnGoal();
        return true;
    }
    return false;
}

void SnakeGame::updateGrid() {
    auto head = snake[0];
    grid.clear(); // Wipe board (using default 0 or EMPTY)

    // call on the whole snake
    for (int i = 0; i < snake.size(); i++)
    {
        grid.set(snake[i].first, snake[i].second, TileType::SNAKE);
    }
    grid.set(apple.x, apple.y, TileType::GOAL);
}

void SnakeGame::render() {
    std::cout << "*** SNAKE ***" << std::endl;
    std::cout << "// ----------------------------------------------------" << std::endl;
    std::cout << "// YOUR SCORE    : " << snake_score << std::endl;
    std::cout << "// YOUR POSITION : (" << snake[0].first << "," << snake[0].second << ")" << std::endl;
    std::cout << "// ----------------------------------------------------" << std::endl;
    std::cout << std::endl;

    grid.displayMap();
}

void lose() {
    std::cout << "\033[2J\033[H"; // Clear screen
    std::cout << "*** SNAKE ***" << std::endl;
    std::cout << "// -------------------------" << std::endl;
    std::cout << "// ------ YOU LOSE ---------" << std::endl;
    std::cout << "// -------------------------" << std::endl;
    std::cout << std::endl;
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
        case 'd': 
            if (!move(Direction::RIGHT))
            {
                is_running = false;
                lose();
            }
            break;
        case 'a': 
            if (!move(Direction::LEFT))
            {
                is_running = false;
                lose();
            }
            break;
        case 'w': 
            if (!move(Direction::UP))
            {
                is_running = false;
                lose();
            }
            break;
        case 's': 
            if (!move(Direction::DOWN))
            {
                is_running = false;
                lose();
            }
            break;
        case 'q': is_running = false; break;
        default: break;
        }
    }
}