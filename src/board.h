#ifndef CHESSSFMLBOARD_BOARD_H
#define CHESSSFMLBOARD_BOARD_H

#include "figure.h"
#include <vector>

class board {
public:
    sf::Texture boardTexture;
    sf::Sprite boardSprite;
    std::vector<figure*> whiteFigure;
    std::vector<figure*> blackFigure;
    board();
    ~board();
    void fillBoard();
    void draw(sf::RenderWindow &window);
    std::vector<std::pair<int,int>> findAllMoves(figure* choosenFigure);
private:
    const int sizeCell = 56;
};


#endif //CHESSSFMLBOARD_BOARD_H
