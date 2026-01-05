/**
 * @file main.cpp
 * @brief A simple terminal-based grid game.
 * @author Tyler Burley
 * @version 1.0
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

 /**
  * @class Grid
  * @brief Manages the game board, player movement, and goal generation.
  */
class Grid
{
public:
    int player_x;
    int player_y;

    int goal_x;
    int goal_y;
    int score;

    std::vector<std::vector<int>> grid;

    /**
     * @brief Constructs the grid and initializes the game state.
     * * Sets the player at (0,0), initializes score to 0,
     * and spawns the first goal.
     * * @param dimensions The width and height of the square grid.
     */
    Grid(int dimensions)
    {
        score = 0;
        player_x = 0;
        player_y = 0;

        std::vector<int> row(dimensions, 0);
        for (int i = 0; i < dimensions; i++)
        {
            grid.push_back(row);
        }

        grid[player_y][player_x] = 1;

        spawnGoal();
    }

    /**
     * @brief randomly places a goal (2) on the grid.
     * * Ensures the goal does not overlap with the player's
     * current position.
     */
    void spawnGoal()
    {
        int dim = grid.size();

        do {
            goal_x = rand() % dim;
            goal_y = rand() % dim;
        } while (goal_x == player_x && goal_y == player_y);

        grid[goal_y][goal_x] = 2;
    }

    /**
     * @brief checks if the players position overlaps with the goal.
     */
    void checkGoal()
    {
        if (player_x == goal_x && player_y == goal_y)
        {
            score++;
            spawnGoal();
        }
    }

    /**
     * @brief shows the grid and score to the user.
     */
    void displayGrid()
    {
        std::cout << "SCORE: " << score << std::endl;
        std::cout << "----------------" << std::endl;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 0) std::cout << ". "; 
                else if (grid[i][j] == 1) std::cout << "P ";
                else if (grid[i][j] == 2) std::cout << "X ";
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief updates player position 1 value to the right and checks goal.
     */
    void moveRight()
    {
        if ((player_x + 1) < grid[0].size())
        {
            grid[player_y][player_x] = 0;
            player_x++;                  
            checkGoal();                 
            grid[player_y][player_x] = 1;
        }
    }

    /**
     * @brief updates player position 1 value to the left and checks goal.
     */
    void moveLeft()
    {
        if ((player_x - 1) >= 0)
        {
            grid[player_y][player_x] = 0;
            player_x--;
            checkGoal();
            grid[player_y][player_x] = 1;
        }
    }

    /**
     * @brief updates player position 1 value up and checks goal.
     */
    void moveUp()
    {
        if ((player_y - 1) >= 0)
        {
            grid[player_y][player_x] = 0;
            player_y--;
            checkGoal();
            grid[player_y][player_x] = 1;
        }
    }

    /**
     * @brief updates player position 1 value down and checks goal.
     */
    void moveDown()
    {
        if ((player_y + 1) < grid.size())
        {
            grid[player_y][player_x] = 0;
            player_y++;
            checkGoal();
            grid[player_y][player_x] = 1;
        }
    }
};

/**
* @brief Game loop.
* * Generates random seed, clears the terminal every user input
*/
int main()
{
    std::srand(std::time(0));

    Grid grid(10);
    char input;

    while (true)
    {
        // Clear screen (Platform independent trick)
        std::cout << "\033[2J\033[H";

        grid.displayGrid();
        std::cout << "\nQuit with q, Move (w/a/s/d): ";
        std::cin >> input;

        if (input == 'd') grid.moveRight();
        else if (input == 'a') grid.moveLeft();
        else if (input == 'w') grid.moveUp();
        else if (input == 's') grid.moveDown();
        else if (input == 'q') break;
    }
}