/**
 * @file grid.h
 * @brief Interface header file for our grid Object
 * @author Tyler Burley
 * @version 1.0
 */

#pragma once
#include <vector>
#include <iostream>
#include <cstdint>

enum class TileType : uint8_t {
    EMPTY,
    PLAYER,  
    GOAL,    
    ENEMY,   
    INVALID
};

enum class Direction {
    UP, DOWN, LEFT, RIGHT, NONE
};

struct Point {
    int x, y;
};

class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<TileType>> map;

public:
    Grid(int width, int height);

    void set(int x, int y, TileType value);
    /*TileType get(int x, int y) const;*/
    bool isInBounds(int x, int y) const;
    void clear(TileType value = TileType::EMPTY);
    void displayMap();
    int getWidth() const { return cols; }
    int getHeight() const { return rows; }
};