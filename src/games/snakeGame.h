/**
 * @file SnakeGame.h
 * @brief Class definition for the 'Snake' game.
 * @author Tyler Burley
 * @version 1.0
 */

#pragma once
#include "../engine/Grid.h"

/**
 * @class SnakeGame
 * @brief Holds all of the game state. Provided methods for modifying state. Renders the state.
 */
class SnakeGame {
private:
    Grid grid;
    Point snake;
    Point apple;

    int snake_score;

    /**
     * @brief Internal helper to increment scores if player reaches apple.
     */
    void checkGoal();

    /**
     * @brief Internal helper to ensure goal position doesn't overlap snake body.
     */
    void spawnGoal();

    /**
     * @brief Empties the Grid, then draws the snake and apple.
     */
    void updateGrid();

public:
    /**
     * @brief Constructer for the collection game!
     * @param size The width/height of the board.
     */
    SnakeGame(int size);

    /**
     * @brief Main Game Loop. Takes control of the screen until user quits.
     */
    void run();

    /**
     * @brief Updates the position of the player/computer if the move is valid.
     */
    void move(Direction dir);

    /**
     * @brief Creates a nice visual to show game state during execution.
     */
    void render();
};

