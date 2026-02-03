/**
 * @file grid.cpp
 * @brief Grid Object Implementation
 * @author Tyler Burley
 * @version 1.0
 */

#include "Grid.h"

/**
* @brief Constructer for the Grid.
*/
Grid::Grid(int width, int height) : cols(width), rows(height) {
    for (int i = 0; i < rows; ++i) {
        std::vector<TileType> row(cols, TileType::EMPTY);
        map.push_back(row);
    }
}

/**
* @brief Update the grid at the passed position to the passed Tile type value.
*/
void Grid::set(int x, int y, TileType value) {
    if (isInBounds(x, y)) {
        map[y][x] = value;
    }
}


//TileType Grid::get(int x, int y) const {
//    if (isInBounds(x, y)) {
//        return map[y][x];
//    }
//    return TileType::INVALID;
//}

/**
* @brief bounds check for our points.
*/
bool Grid::isInBounds(int x, int y) const {
    return (x > 0 && x < cols - 1 && y > 0 && y < rows - 1);
}

/**
* @brief reset the board.
*/
void Grid::clear(TileType value) {
    for (auto& row : map) {
        std::fill(row.begin(), row.end(), value);
    }
}

/**
* @brief Convert all of our tiles into strings to be displayed in the terminal.
*/
void Grid::displayMap() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                std::cout << "# ";
                continue;
            }

            TileType tile = map[i][j];

            switch (tile) {
            case TileType::EMPTY:  std::cout << "  "; break;
            case TileType::PLAYER: std::cout << "P "; break;
            case TileType::SNAKE:  std::cout << "0 "; break;
            case TileType::GOAL:   std::cout << "X "; break;
            case TileType::ENEMY:  std::cout << "C "; break;
            default:               std::cout << "? "; break;
            }
        }
        std::cout << std::endl;
    }
}