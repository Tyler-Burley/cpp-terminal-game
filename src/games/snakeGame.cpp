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
#include <chrono>
#include <thread>

SnakeGame::SnakeGame(int size)
    : grid(size, size), snake{{1, 1}}
{
    snake_score = 0;

    spawnGoal();
    updateGrid();
}

void SnakeGame::spawnGoal() {
    int dim = grid.getWidth();
    bool on_snake = false;

    do {
        apple.x = (rand() % (dim - 2)) + 1;
        apple.y = (rand() % (dim - 2)) + 1;

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

void SnakeGame::gameLoop() {
    while (is_running.load()) {
        std::cout << "\033[2J\033[H"; // Clear screen


        // display the time
        /*auto end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Time: " << elapsed_seconds.count() << '/n';*/

        render();

        /*std::cout << "\nUse WASD to move (Press 'q' to quit)..." << std::endl;
        input = _getch();*/

        Direction currentDir = dir.load();

        switch (currentDir) {
        case Direction::RIGHT:
            if (!move(Direction::RIGHT))
            {
                is_running = false;
                lose();
            }
            break;
        case Direction::LEFT:
            if (!move(Direction::LEFT))
            {
                is_running = false;
                lose();
            }
            break;
        case Direction::UP:
            if (!move(Direction::UP))
            {
                is_running = false;
                lose();
            }
            break;
        case Direction::DOWN:
            if (!move(Direction::DOWN))
            {
                is_running = false;
                lose();
            }
            break;
        default: break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void SnakeGame::run() {
    char input;

    /*auto start = std::chrono::system_clock::now();*/

    std::thread t1 = std::thread(&SnakeGame::gameLoop, this);

    // get input from the user
    while (is_running.load()) {
        input = _getch();

        switch (input) {
        case 'w':
            dir = Direction::UP;
            break;
        case 'a':
            dir = Direction::LEFT;
            break;
        case 's':
            dir = Direction::DOWN;
            break;
        case 'd':
            dir = Direction::RIGHT;
            break;
        case 'q':
            is_running = false;
            break;
        }
    }

    if (t1.joinable()) {
        t1.join();
    }
    
}