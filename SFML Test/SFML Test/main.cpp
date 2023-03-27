#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Board.h"
using namespace std;

int main() {
    bool lose = false;
    bool win = false;
    Board board = Board();
    sf::RenderWindow window(sf::VideoMode(board._width, board._height), "Minesweeper");
    board.LoadMines();

    //Draw smiley face button
    sf::Sprite smileyButton(TextureManager::GetTexture("face_happy"));
    smileyButton.setPosition(window.getSize().x / 2 - 16, 32 * board._rows);
    sf::Sprite loseButton(TextureManager::GetTexture("face_lose"));
    loseButton.setPosition(window.getSize().x / 2 - 16, 32 * board._rows);
    sf::Sprite winButton(TextureManager::GetTexture("face_win"));
    winButton.setPosition(window.getSize().x / 2 - 16, 32 * board._rows);
    //Draw debug mines button
    sf::Sprite showMinesButton(TextureManager::GetTexture("debug"));
    showMinesButton.setPosition(window.getSize().x / 2 + 144, 32 * board._rows);
    //Draw test buttons
    sf::Sprite test1Button(TextureManager::GetTexture("test_1"));
    test1Button.setPosition(showMinesButton.getPosition().x + 64, showMinesButton.getPosition().y);
    sf::Sprite test2Button(TextureManager::GetTexture("test_2"));
    test2Button.setPosition(test1Button.getPosition().x + 64, test1Button.getPosition().y);
    sf::Sprite test3Button(TextureManager::GetTexture("test_3"));
    test3Button.setPosition(test2Button.getPosition().x + 64, test2Button.getPosition().y);

    while (window.isOpen())
    {
        win = board.AllTilesRevealed(); //Check for win condition
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {

                if (event.mouseButton.button == sf::Mouse::Left) { // If left mouse pressed
                    sf::Vector2i position = sf::Mouse::getPosition(window);

                    //Smiley reset button
                    if (smileyButton.getGlobalBounds().contains(position.x, position.y)) {
                        board = Board();
                        win = false;
                        lose = false;
                        board.showMines = false;
                        board._numberFlagged = 0;
                        board.LoadMines();
                        board._mineCounter = board._mineCount;
                    }
                    //Show mines button
                    if (showMinesButton.getGlobalBounds().contains(position.x, position.y) && !win && !lose) {
                        if (!board.showMines)
                            board.showMines = true;
                        else
                            board.showMines = false;
                    }
                    //Test1 button
                    if (test1Button.getGlobalBounds().contains(position.x, position.y)) {
                        board.showMines = false;
                        board.LoadMines("testboard1.brd");
                        board._mineCounter = board._mineCount;
                        win = false;
                        lose = false;
                    }
                    //Test2 button
                    if (test2Button.getGlobalBounds().contains(position.x, position.y)) {
                        board.showMines = false;
                        board.LoadMines("testboard2.brd");
                        board._mineCounter = board._mineCount;
                        win = false;
                        lose = false;
                    }
                    //Test3 button
                    if (test3Button.getGlobalBounds().contains(position.x, position.y)) {
                        board.showMines = false;
                        board.LoadMines("testboard3.brd");
                        board._mineCounter = board._mineCount;
                        win = false;
                        lose = false;
                    }
                    //Clicking and revealing tiles
                    for (unsigned int i = 0; i < board.tiles.size(); i++) {
                        if (board.tiles[i].GetSpriteRect().contains(sf::Vector2f(position.x, position.y))
                        && !board.tiles[i].isFlagged && !lose) {
                            board.tiles[i].isRevealed = true;
                            board.RecursiveReveal(board.tiles[i]);

                            //If clicked tile has a mine
                            if (board.tiles[i].hasMine) {
                                lose = true;
                                board.showMines = true;
                            }
                        }
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right) { // If right mouse pressed
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    //Adding flags
                    for (unsigned int i = 0; i < board.tiles.size(); i++) {
                        if (board.tiles[i].GetSpriteRect().contains(sf::Vector2f(position.x, position.y)) && !board.tiles[i].isFlagged
                        && !board.tiles[i].isRevealed) {
                            board.tiles[i].isFlagged = true;
                            board._numberFlagged++;
                            board._mineCounter--;
                        }
                        else if (board.tiles[i].GetSpriteRect().contains(sf::Vector2f(position.x, position.y)) && board.tiles[i].isFlagged
                        && !board.tiles[i].isRevealed) {
                            board.tiles[i].isFlagged = false;
                            board._numberFlagged--;
                            board._mineCounter++;
                        }
                    }
                }
            }
        }

        window.clear();
        board.DisplayTiles(window); //Draw tiles
        board.DisplayMineCounter(window); //Draw Mine Counter
        //Draw mines
        if (board.showMines) {
            board.DisplayMines(window);
        }
        if (!win && !lose)
            window.draw(smileyButton);
        else if (win) {
            window.draw(winButton);
            board.ReplaceMinesWithFlags(window);
        }
        else if (lose)
            window.draw(loseButton);
        window.draw(showMinesButton); //Draw debug mines
        window.draw(test1Button);
        window.draw(test2Button);
        window.draw(test3Button);


        window.display();
    }

    return 0;
}