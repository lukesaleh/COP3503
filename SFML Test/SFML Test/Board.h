#pragma once
#include <iostream>
#include <fstream>
#include "Tile.h"
#include "Random.h"

class Board {
public:
    int _width;
    int _height;
    int _mineCount;
    int _tileCount;
    int _columns;
    int _rows;
    bool showMines;
    int _mineCounter;
    int _numberFlagged;
    std::vector<Tile> tiles;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite digits;

    Board();
    void SetTileMineCount();
    void LoadMines();
    void LoadMines(std::string fileName);
    void DisplayTiles(sf::RenderWindow& window);
    void DisplayMines(sf::RenderWindow& window);
    bool AllTilesRevealed();
    void DisplayMineCounter(sf::RenderWindow& window);
    void RecursiveReveal(Tile& clicked);
    void ReplaceMinesWithFlags(sf::RenderWindow& window);
};

