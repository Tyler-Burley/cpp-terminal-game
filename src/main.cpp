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

#define GRID_SIZE 12

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

enum class User {
    PLAYER,
    COMPUTER
};

struct Player
{
    int x_pos;
    int y_pos;
};

 /**
  * @class Grid
  * @brief Manages the game board, player movement, and goal generation.
  */
class Grid
{
private:
    Player player;
    Player computer;

    int goal_x;
    int goal_y;

    int player_score;
    int comp_score;

    std::vector<std::vector<int>> grid;
public:

    /**
     * @brief Constructs the grid and initializes the game state.
     * * Sets the player at (0,0), initializes score to 0,
     * and spawns the first goal.
     * * @param dimensions The width and height of the square grid.
     */
    Grid(int dimensions)
    {
        player_score = 0;
        comp_score = 0;

        player = Player{ 0, 0 };
        computer = Player{ dimensions - 1, dimensions - 1 };

        std::vector<int> row(dimensions, 0);
        for (int i = 0; i < dimensions; i++)
        {
            grid.push_back(row);
        }

        grid[player.y_pos][player.x_pos] = 1;
        grid[computer.y_pos][computer.x_pos] = 3;

        spawnGoal();
    }

    /**
     * @brief randomly places a goal (2) on the grid.
     * * Ensures the goal does not overlap with the player's or comps
     * current position.
     */
    void spawnGoal()
    {
        int dim = grid.size();

        do {
            goal_x = rand() % dim;
            goal_y = rand() % dim;
        } while ((goal_x == player.x_pos && goal_y == player.y_pos) 
              || (goal_x == computer.x_pos && goal_y == computer.y_pos));

        grid[goal_y][goal_x] = 2;
    }

    /**
     * @brief checks if the players position overlaps with the goal.
     */
    void checkGoal()
    {
        if (player.x_pos == goal_x && player.y_pos == goal_y)
        {
            player_score++;
            spawnGoal();
            return;
        }
        if (computer.x_pos == goal_x && computer.y_pos == goal_y)
        {
            comp_score++;
            spawnGoal();
            return;
        }
    }

    /**
     * @brief shows the grid and score to the user.
     */
    void displayGrid()
    {
        std::cout << "// ----------------------------------------------------" << std::endl;
        std::cout << "// YOUR SCORE    : " << player_score << "     || COMPUTER SCORE    : "<< comp_score << std::endl;
        std::cout << "// YOUR POSITION : (" << this->player.x_pos << "," << this->player.y_pos << ")" << " || ";
        std::cout << "COMPUTER POSITION : (" << this->computer.x_pos << "," << this->computer.y_pos << ")" << std::endl;
        std::cout << "// ----------------------------------------------------" << std::endl;
        std::cout << std::endl;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 0) std::cout << ". ";
                else if (grid[i][j] == 1) std::cout << "P ";
                else if (grid[i][j] == 3) std::cout << "C ";
                else if (grid[i][j] == 2) std::cout << "X ";
            }
            std::cout << std::endl;
        }
    }

    /**
     * @brief responsible for moving the player/computer object in the grid.
     */
    void move(User user, Direction dir)
    {
        Player* p = (user == User::PLAYER) ? &this->player : &this->computer;
        int id = (user == User::PLAYER) ? 1 : 3;
        grid[p->y_pos][p->x_pos] = 0;

        switch (dir) {
        case Direction::UP:
            if (p->y_pos - 1 >= 0) {
                p->y_pos--;
            }
            break;

        case Direction::DOWN:
            if (p->y_pos + 1 < grid.size()) {
                p->y_pos++;
            }
            break;

        case Direction::LEFT:
            if (p->x_pos - 1 >= 0) {
                p->x_pos--;
            }
            break;

        case Direction::RIGHT:
            if (p->x_pos + 1 < grid[0].size()) {
                p->x_pos++;
            }
            break;

        default:
            break;
        }

        checkGoal();

        grid[p->y_pos][p->x_pos] = id;
    }

    /**
     * @brief wrapper of move so computer makes "smart" moves.
     */
    void moveComputer()
    {
        bool try_horizontal_first = (std::rand() % 2 == 0);

        if (try_horizontal_first)
        {
            if (this->computer.x_pos < this->goal_x)
            {
                move(User::COMPUTER, Direction::RIGHT);
                return;
            }
            if (this->computer.x_pos > this->goal_x)
            {
                move(User::COMPUTER, Direction::LEFT);
                return;
            }
            if (this->computer.y_pos < this->goal_y)
            {
                move(User::COMPUTER, Direction::DOWN);
                return;
            }
            if (this->computer.y_pos > this->goal_y)
            {
                move(User::COMPUTER, Direction::UP);
                return;
            }
        }
        else
        {
            if (this->computer.y_pos < this->goal_y)
            {
                move(User::COMPUTER, Direction::DOWN);
                return;
            }
            if (this->computer.y_pos > this->goal_y)
            {
                move(User::COMPUTER, Direction::UP);
                return;
            }
            if (this->computer.x_pos < this->goal_x)
            {
                move(User::COMPUTER, Direction::RIGHT);
                return;
            }
            if (this->computer.x_pos > this->goal_x)
            {
                move(User::COMPUTER, Direction::LEFT);
                return;
            }
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

    Grid grid(GRID_SIZE);
    char input;

    bool is_running = true;

    while (is_running)
    {
        // Clear screen (Platform independent trick)
        std::cout << "\033[2J\033[H";

        grid.displayGrid();
        std::cout << "\nQuit with q, Move (w/a/s/d): ";
        std::cin >> input;

        // Player moves
        switch (input)
        {
        case 'd':
            grid.move(User::PLAYER, Direction::RIGHT);
            break;
        case 'a':
            grid.move(User::PLAYER, Direction::LEFT);
            break;
        case 'w':
            grid.move(User::PLAYER, Direction::UP);
            break;
        case 's':
            grid.move(User::PLAYER, Direction::DOWN);
            break;
        case 'q':
            is_running = false;
            break;
        default:
            break;
        }

        // Computer moves
        grid.moveComputer();
    }
}