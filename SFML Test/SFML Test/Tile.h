#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TextureManager.h"

struct Tile {
    bool hasMine;
    bool isFlagged;
    bool isRevealed;
    float x;
    float y;
    int _minesAround;
    std::vector<Tile*> adjacentTiles;
    sf::Sprite tile_hidden;
    sf::Sprite tile_revealed;
    sf::Sprite flag;
    sf::Sprite number_1;
    sf::Sprite number_2;
    sf::Sprite number_3;
    sf::Sprite number_4;
    sf::Sprite number_5;
    sf::Sprite number_6;
    sf::Sprite number_7;
    sf::Sprite number_8;

    Tile();
    void DisplayUnrevealed(sf::RenderWindow& window);
    sf::FloatRect GetSpriteRect();
};



