/**
 * @file CollectGame.cpp
 * @brief Implementation of the Collect game logic.
 * @author Tyler Burley
 * @version 1.0
 */

#include "CollectGame.h"
#include <iostream>
#include <cstdlib>
#include <conio.h> // Windows specific for _getch()

CollectGame::CollectGame(int size) : grid(size, size) {
    player_score = 0;
    comp_score = 0;

    player = { 0, 0 };
    computer = { size - 1, size - 1 };

    spawnGoal();
    updateGrid();
}

void CollectGame::spawnGoal() {
    int dim = grid.getWidth();
    do {
        goal.x = rand() % dim;
        goal.y = rand() % dim;
    } while ((goal.x == player.x && goal.y == player.y)
        || (goal.x == computer.x && goal.y == computer.y));
}

void CollectGame::move(User user, Direction dir) {
    Point* p = (user == User::PLAYER) ? &player : &computer;
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

void CollectGame::moveComputer() {
    if (computer.x < goal.x) move(User::COMPUTER, Direction::RIGHT);
    else if (computer.x > goal.x) move(User::COMPUTER, Direction::LEFT);
    else if (computer.y < goal.y) move(User::COMPUTER, Direction::DOWN);
    else if (computer.y > goal.y) move(User::COMPUTER, Direction::UP);
}

void CollectGame::checkGoal() {
    if (player.x == goal.x && player.y == goal.y) {
        player_score++;
        spawnGoal();
    }
    else if (computer.x == goal.x && computer.y == goal.y) {
        comp_score++;
        spawnGoal();
    }
}

void CollectGame::updateGrid() {
    grid.clear(); // Wipe board (using default 0 or EMPTY)
    grid.set(player.x, player.y, TileType::PLAYER);
    grid.set(computer.x, computer.y, TileType::ENEMY);
    grid.set(goal.x, goal.y, TileType::GOAL);
}

void CollectGame::render() {
    std::cout << "*** COLLECT ***" << std::endl;
    std::cout << "// ----------------------------------------------------" << std::endl;
    std::cout << "// YOUR SCORE    : " << player_score << "     || COMPUTER SCORE    : " << comp_score << std::endl;
    std::cout << "// YOUR POSITION : (" << player.x << "," << player.y << ")" << " || ";
    std::cout << "COMPUTER POSITION : (" << computer.x << "," << computer.y << ")" << std::endl;
    std::cout << "// ----------------------------------------------------" << std::endl;
    std::cout << std::endl;

    grid.displayMap();
}

void CollectGame::run() {
    bool is_running = true;
    char input;

    while (is_running) {
        std::cout << "\033[2J\033[H"; // Clear screen

        render();

        std::cout << "\nUse WASD to move (Press 'q' to quit)..." << std::endl;
        input = _getch();

        switch (input) {
        case 'd': move(User::PLAYER, Direction::RIGHT); break;
        case 'a': move(User::PLAYER, Direction::LEFT); break;
        case 'w': move(User::PLAYER, Direction::UP); break;
        case 's': move(User::PLAYER, Direction::DOWN); break;
        case 'q': is_running = false; break;
        default: break;
        }

        if (is_running) {
            moveComputer();
        }
    }
}