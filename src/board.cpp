#include "board.h"


board::board() {
    boardTexture.loadFromFile("../images/board.png");
    boardSprite.setTexture(boardTexture);
    fillBoard();
}
board::~board() {
    for(auto del : whiteFigure){
        delete del;
    }
    for (auto del : blackFigure){
        delete del;
    }
}

void board::fillBoard() {
    whiteFigure.clear();
    blackFigure.clear();
    figure *tmp;
    sf::Vector2i coord;
    for (int i = 0; i < 16; ++i) {
        if (i < 8){
            tmp = new blackPawn;
            coord.y = 1;
            coord.x = i;
            tmp->setCoordinate(coord);
            blackFigure.push_back(tmp);
            tmp = nullptr;
        } else{
            tmp = new whitePawn;
            coord.y = 6;
            coord.x = i - 8;
            tmp->setCoordinate(coord);
            whiteFigure.push_back(tmp);
            tmp = nullptr;
        }
    }
    // rook ====================================
    tmp = new rook(true);
    tmp->setX(0);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new rook(true);
    tmp->setX(7);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new rook(false);
    tmp->setX(0);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    tmp = new rook(false);
    tmp->setX(7);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    // kNight ====================================
    tmp = new kNight(true);
    tmp->setX(1);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new kNight(true);
    tmp->setX(6);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new kNight(false);
    tmp->setX(1);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    tmp = new kNight(false);
    tmp->setX(6);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    //bishop=======================================
    tmp = new bishop(true);
    tmp->setX(2);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new bishop(true);
    tmp->setX(5);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new bishop(false);
    tmp->setX(2);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    tmp = new bishop(false);
    tmp->setX(5);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    //Queen =====================================
    tmp = new queen(true);
    tmp->setX(3);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new queen(false);
    tmp->setX(3);
    tmp->setY(0);
    blackFigure.push_back(tmp);
    //King========================================
    tmp = new king(true);
    tmp->setX(4);
    tmp->setY(7);
    whiteFigure.push_back(tmp);
    tmp = new king(false);
    tmp->setX(4);
    tmp->setY(0);
    blackFigure.push_back(tmp);
}

void board::draw(sf::RenderWindow &window) {
    window.draw(boardSprite);
    for(auto & it : whiteFigure){
        it->chessFigureSprite.setPosition((float)it->getX() * (float)sizeCell + 27,
                                          (float)it->getY() * (float)sizeCell + 27);
        it->draw(window);
    }
    for (auto & it : blackFigure){
        it->chessFigureSprite.setPosition((float)it->getX() * (float)sizeCell + 27,
                                          (float)it->getY() * (float)sizeCell + 27);
        it->draw(window);
    }
}

std::vector<std::pair<int, int>> board::findAllMoves(figure *choosenFigure) {
    std::vector<std::pair<int,int>> possibleMoves;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (choosenFigure->getX() == j && choosenFigure->getY() == i){
                continue;
            }
            bool answ = choosenFigure->move(whiteFigure,blackFigure,sf::Vector2i(j,i), true);
            if (answ == 0){
                possibleMoves.emplace_back(j,i);
            }
        }
    }
    return possibleMoves;
}

