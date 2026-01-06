/**
 * @file main.cpp
 * @brief Entry point for a simple cpp termina games Arcade.
 * @author Tyler Burley
 * @version 1.0
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "games/collectGame.h"
#include "games/snakeGame.h"

#define BOARD_SZ 12

int main() {
    // 1. Global Setup (Seed random number generator once)
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::string game_name;

    std::cout << "Hello and welcome to my cpp arcade!" << std::endl;
    std::cout << "Would you like to play : Collect or Snake?" << std::endl;

    std::cin >> game_name;

    if (game_name == "Snake" || game_name == "snake")
    {
        SnakeGame game(BOARD_SZ);
        game.run();
    }
    else if(game_name == "Collect" || game_name == "collect")
    {
        CollectGame game(BOARD_SZ);
        game.run();
    }
    else
    {
        std::cout << "thats not one of the options pal; try again";
    }

    return 0;
}