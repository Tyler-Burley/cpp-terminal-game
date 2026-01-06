/**
 * @file CollectGame.h
 * @brief Class definition for the 'Collect' game.
 * @author Tyler Burley
 * @version 1.0
 */

#pragma once
#include "../engine/Grid.h"

 // Enum specific to this game logic
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

    int player_score;
    int comp_score;

    /**
     * @brief Internal helper to increment scores if player/computer reaches goal.
     */
    void checkGoal();

    /**
     * @brief Internal helper to ensure goal position doesn't overlap player/computer.
     */
    void spawnGoal();

    /**
     * @brief Empties the Grid, then draws the player, enemy, and goal.
     */
    void updateGrid();

public:
    /**
     * @brief Constructer for the collection game!
     * @param size The width/height of the board.
     */
    CollectGame(int size);

    /**
     * @brief Main Game Loop. Takes control of the screen until user quits.
     */
    void run();

    /**
     * @brief Updates the position of the player/computer if the move is valid.
     */
    void move(User user, Direction dir);

    /**
     * @brief Wrapper of move so computer makes "smart" moves.
     */
    void moveComputer();

    /**
     * @brief Creates a nice visual to show game state during execution.
     */
    void render();
};
