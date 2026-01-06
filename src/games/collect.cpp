/**
 * @file collect.cpp
 * @brief Simple terminal game where the player "collect"s Xs. Try to beat the Computer!
 * @author Tyler Burley
 * @version 1.0
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // Windows specific
#include "../engine/grid.h"

#define BOARD_SZ 12

enum class User { PLAYER, COMPUTER };

/**
 * @class CollectGame
 * @brief Holds all of the game state. Provided methods for modifying state. Renders the state.
 */
class CollectGame {
private:
    Grid grid;
    Point player;
    Point computer;
    Point goal;

    int player_score = 0;
    int comp_score = 0;

public:
    /**
     * @brief Constructer for the collection game!.
     */
    CollectGame(int size) : grid(size, size) {
        player = { 0, 0 };
        computer = { size - 1, size - 1 };

        spawnGoal();
        updateGrid();
    }

    /**
     * @brief Make sure the goal position doesn't overlap player/computer
     */
    void spawnGoal() {
        int dim = grid.getWidth();
        do {
            goal.x = rand() % dim;
            goal.y = rand() % dim;
        } while ((goal.x == player.x && goal.y == player.y)
            || (goal.x == computer.x && goal.y == computer.y));
    }

    /**
     * @brief Updates the position of the player/computer if the move is valid.
     */
    void move(User user, Direction dir) {
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

    /**
     * @brief wrapper of move so computer makes "smart" moves.
     */
    void moveComputer() {
        if (computer.x < goal.x) move(User::COMPUTER, Direction::RIGHT);
        else if (computer.x > goal.x) move(User::COMPUTER, Direction::LEFT);
        else if (computer.y < goal.y) move(User::COMPUTER, Direction::DOWN);
        else if (computer.y > goal.y) move(User::COMPUTER, Direction::UP);
    }

    /**
     * @brief increment scores if player/computer reaches goal.
     */
    void checkGoal() {
        if (player.x == goal.x && player.y == goal.y) {
            player_score++;
            spawnGoal();
        }
        else if (computer.x == goal.x && computer.y == goal.y) {
            comp_score++;
            spawnGoal();
        }
    }

    /**
     * @brief Empties the Grid, then draws the player, enemy, and goal.
     */
    void updateGrid() {
        grid.clear(); // Wipe board
        grid.set(player.x, player.y, TileType::PLAYER);
        grid.set(computer.x, computer.y, TileType::ENEMY);
        grid.set(goal.x, goal.y, TileType::GOAL);
    }

    /**
     * @brief Creates a nice visual to show game state during execution.
     */
    void render() {
        std::cout << "// ----------------------------------------------------" << std::endl;
        std::cout << "// YOUR SCORE    : " << player_score << "      || COMPUTER SCORE    : " << comp_score << std::endl;
        std::cout << "// YOUR POSITION : (" << player.x << "," << player.y << ")" << " || ";
        std::cout << "COMPUTER POSITION : (" << computer.x << "," << computer.y << ")" << std::endl;
        std::cout << "// ----------------------------------------------------" << std::endl;
        std::cout << std::endl;

        grid.displayMap();
    }
};

/**
* @brief Game loop.
* * Generates random seed, clears the terminal every user input
*/
int main() {
    std::srand(std::time(0));
    CollectGame game(BOARD_SZ);
    bool is_running = true;
    char input;

    while (is_running) {
        std::cout << "\033[2J\033[H"; // Clear screen

        game.render();

        std::cout << "\nUse WASD to move (Press 'q' to quit)..." << std::endl;
        input = _getch();

        switch (input) {
        case 'd': game.move(User::PLAYER, Direction::RIGHT); break;
        case 'a': game.move(User::PLAYER, Direction::LEFT); break;
        case 'w': game.move(User::PLAYER, Direction::UP); break;
        case 's': game.move(User::PLAYER, Direction::DOWN); break;
        case 'q': is_running = false; break;
        }

        game.moveComputer();
    }
    return 0;
}