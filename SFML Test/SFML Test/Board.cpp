#include "Board.h"
void Board::SetTileMineCount() {
    for (unsigned int tileIndex = 0; tileIndex < _tileCount; tileIndex++) {
        int adjacentMines = 0;
        if (tileIndex == 0) { //Top left corner
            tiles[tileIndex].adjacentTiles.push_back(&tiles[1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_columns + 1]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if (tileIndex == (_columns - 1)) { //Top right corner
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_columns - 2]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_columns - 1 + _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_columns - 2 + _columns]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if (tileIndex == (_rows * _columns - _columns)) { //Bottom left corner
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_tileCount - (_columns * 2)]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[(_tileCount - (_columns * 2)) + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[_tileCount - _columns + 1]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if (tileIndex == (_rows * _columns - 1)) { //Bottom right corner
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns - 1]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if (tileIndex > 0 && tileIndex < _columns) { //Top row
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns + 1]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if (tileIndex > (_rows * _columns - _columns) && tileIndex < _tileCount) { //Bottom row
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns + 1]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if ((tileIndex % _columns) == 0 ) { //Left Column
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else if (((tileIndex + 1 ) % _columns) == 0) { //Right Column
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }
        else {
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - _columns - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex - 1]);

            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns - 1]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns]);
            tiles[tileIndex].adjacentTiles.push_back(&tiles[tileIndex + _columns + 1]);
            for (unsigned int i = 0; i < tiles[tileIndex].adjacentTiles.size(); i++) {
                if (tiles[tileIndex].adjacentTiles[i]->hasMine)
                    adjacentMines++;
            }
        }

        //Set mine count
        tiles[tileIndex]._minesAround = adjacentMines;
    }
}

Board::Board() {
    mine.setTexture(TextureManager::GetTexture("mine"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    digits.setTexture(TextureManager::GetTexture("digits"));
    std::string filePath = "boards/config.cfg";
    std::ifstream inFile(filePath);
    if (inFile.is_open()) {
        std::string entry;
        getline(inFile, entry);
        _columns = stoi(entry);
        getline(inFile, entry);
        _rows = stoi(entry);
        getline(inFile, entry);
        _mineCount= stoi(entry);
    }
    else {
        std::cout << "Could not open " << filePath << std::endl;
    }
    _width = _columns * 32;
    _height = (_rows * 32) + 88;
    _tileCount = _columns * _rows;
    _mineCounter = _mineCount;
    _numberFlagged = 0;
    showMines = false;
    inFile.close();
}

void Board::LoadMines() {
    tiles.clear();
    for (unsigned int c = 0; c < _tileCount; c++) {
        Tile tileToAdd = Tile();
        tiles.push_back(tileToAdd);
    }

    float yPos = 0;
    float xPos = 0;
    int tileCount = 0;
    for (unsigned int i = 0; i < _rows; i++) {
        for (unsigned int j = 0; j < _columns; j++) {
            tiles[tileCount].y = yPos;
            tiles[tileCount].x = xPos;
            xPos += 32;
            tileCount++;
        }
        xPos = 0;
        yPos += 32;
    }

    for (unsigned int mineCount = 0; mineCount < _mineCount; mineCount++) {
        int randomInt = Random::Int(0, _tileCount - 1);
        while (tiles[randomInt].hasMine) {
            randomInt = Random::Int(0, _tileCount - 1);
        }
        tiles[randomInt].hasMine = true;
    }
    SetTileMineCount();
}

void Board::LoadMines(std::string fileName) {
    _mineCount = 0;
    _mineCounter = 0;
    tiles.clear();
    _columns = 25;
    _rows = 16;
    _tileCount = 400;
    std::string filePath = "boards/" + fileName;
    std::ifstream inFile(filePath);
    if (inFile.is_open()) {
        char entry;
        while (inFile >> entry) {
            if (entry != '0' and entry != '1') {
                continue;
            }
            Tile tile = Tile();
            if (entry == '1') {
                tile.hasMine = true;
                _mineCount++;
            }
            tiles.push_back(tile);
            _mineCounter++;
        }
        // Set positions of the tiles
        float yPos = 0;
        float xPos = 0;
        int tileCount = 0;
        for (unsigned int i = 0; i < _rows; i++) {
            for (unsigned int j = 0; j < _columns; j++) {
                tiles[tileCount].y = yPos;
                tiles[tileCount].x = xPos;
                xPos += 32;
                tileCount++;
            }
            xPos = 0;
            yPos += 32;
        }
        SetTileMineCount(); //Set the number of adjacent mines
    }
    else {
        std::cout << "Could not open " << filePath << std::endl;
    }
    inFile.close();
}

void Board::DisplayTiles(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        tiles[i].DisplayUnrevealed(window);
    }
}

void Board::DisplayMines(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (tiles[i].hasMine) {
            mine.setPosition(tiles[i].x, tiles[i].y);
            window.draw(mine);
        }
    }
}

bool Board::AllTilesRevealed() {
    bool win = false;
    int numberRevealed = 0;
    int allRevealed = _tileCount - _mineCount;
    for (unsigned int i = 0; i < _tileCount; i++) {
        if (!tiles[i].hasMine && tiles[i].isRevealed) {
            numberRevealed++;
        }
    }
    if (numberRevealed == allRevealed) {
        win = true;
    }
    return win;
} // win condition



void Board::DisplayMineCounter(sf::RenderWindow &window) {
    int absMineCounter = abs(_mineCounter);
    int onesPlace =  absMineCounter % 10;
    int tensPlace = (absMineCounter % 100 - onesPlace) / 10;
    int hundPlace = (absMineCounter - (tensPlace * 10) - onesPlace) / 100;
    int xPosition = 32;
    if (_mineCounter < 0) {
        digits.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
        digits.setPosition(xPosition, _rows * 32);
        window.draw(digits);
        xPosition += 21;
    }
    if (hundPlace > 0) {
        digits.setTextureRect(sf::IntRect(hundPlace * 21, 0, 21, 32));
        digits.setPosition(xPosition, _rows * 32);
        window.draw(digits);
        xPosition += 21;
        if (tensPlace == 0) {
            digits.setTextureRect(sf::IntRect(tensPlace * 21, 0, 21, 32));
            digits.setPosition(xPosition, _rows * 32);
            window.draw(digits);
            xPosition += 21;
        }
    }
    if (tensPlace > 0) {
        digits.setTextureRect(sf::IntRect(tensPlace * 21, 0, 21, 32));
        digits.setPosition(xPosition, _rows * 32);
        window.draw(digits);
        xPosition += 21;
    }
    digits.setTextureRect(sf::IntRect(onesPlace * 21, 0, 21, 32));
    digits.setPosition(xPosition, _rows * 32);
    window.draw(digits);
}

void Board::RecursiveReveal(Tile& clicked) {
    if (clicked._minesAround == 0 && !clicked.hasMine) {
        for (unsigned int i = 0; i < clicked.adjacentTiles.size(); i++) {
            if (!clicked.adjacentTiles[i]->hasMine && !clicked.adjacentTiles[i]->isFlagged
                && !clicked.adjacentTiles[i]->isRevealed) {
                if (clicked.adjacentTiles[i] == &tiles[0]) {
                    tiles[0].isRevealed = true;
                }
                clicked.adjacentTiles[i]->isRevealed = true;
                RecursiveReveal(*clicked.adjacentTiles[i]);
            }
        }
    }
}

void Board::ReplaceMinesWithFlags(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < tiles.size(); i++) {
        if (tiles[i].hasMine) {
            tiles[i].isFlagged = true;
//            flag.setPosition(tiles[i].x, tiles[i].y);
//            window.draw(flag);
        }
        _mineCounter = 0;
    }
}
