#include "Tile.h"

Tile::Tile() {
    hasMine = false;
    isFlagged = false;
    isRevealed = false;
    x = 0;
    y = 0;
    _minesAround = 0;
    tile_hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
    tile_revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    number_1.setTexture(TextureManager::GetTexture("number_1"));
    number_2.setTexture(TextureManager::GetTexture("number_2"));
    number_3.setTexture(TextureManager::GetTexture("number_3"));
    number_4.setTexture(TextureManager::GetTexture("number_4"));
    number_5.setTexture(TextureManager::GetTexture("number_5"));
    number_6.setTexture(TextureManager::GetTexture("number_6"));
    number_7.setTexture(TextureManager::GetTexture("number_7"));
    number_8.setTexture(TextureManager::GetTexture("number_8"));
}

void Tile::DisplayUnrevealed(sf::RenderWindow& window) {
    if (!isRevealed) {
        tile_hidden.setPosition(x, y);
        window.draw(tile_hidden);
        if (isFlagged) {
            flag.setPosition(x, y);
            window.draw(flag);
        }
    }
    else if (isRevealed) {
        tile_revealed.setPosition(x, y);
        window.draw(tile_revealed);
        if (_minesAround > 0 && !hasMine) { //Show numbers of adjacent mines
            if (_minesAround == 1) {
                number_1.setPosition(x, y);
                window.draw(number_1);
            }
            else if (_minesAround == 2) {
                number_2.setPosition(x, y);
                window.draw(number_2);
            }
            else if (_minesAround == 3) {
                number_3.setPosition(x, y);
                window.draw(number_3);
            }
            else if (_minesAround == 4) {
                number_4.setPosition(x, y);
                window.draw(number_4);
            }
            else if (_minesAround == 5) {
                number_5.setPosition(x, y);
                window.draw(number_5);
            }
            else if (_minesAround == 6) {
                number_6.setPosition(x, y);
                window.draw(number_6);
            }
            else if (_minesAround == 7) {
                number_7.setPosition(x, y);
                window.draw(number_7);
            }
            else if (_minesAround == 8) {
                number_8.setPosition(x, y);
                window.draw(number_8);
            }
        }
        isFlagged = false;
    }
}

sf::FloatRect Tile::GetSpriteRect() {
    return tile_hidden.getGlobalBounds();
}





