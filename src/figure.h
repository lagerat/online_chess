#ifndef CHESSSFMLBOARD_FIGURE_H
#define CHESSSFMLBOARD_FIGURE_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class figure {
public:
    figure();
    virtual int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
                     sf::Vector2i newCoordinate,bool testCheck = false) = 0;
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setCoordinate(sf::Vector2i coordinate);
    void draw(sf::RenderWindow &window);
    sf::Sprite chessFigureSprite;
    bool takingOnAsileIsPossible = false;
protected:
    int x,y;
    sf::Texture figuresTextures;
    const int size = 56;
    bool isWhite;
    int finalMove(std::vector<figure*> &whiteFigure, std::vector<figure*> &blackFigure,
                  sf::Vector2i &newCoordinate,bool testCheck = false);
    void dropAsile(std::vector<figure*> &figure);
};

class whitePawn : public figure {
public:
    whitePawn();
    int move(std::vector<figure*> &whiteFigure, std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;
private:
    bool isFirstMove = true;
};
class blackPawn : public figure{
public:
    blackPawn();
    int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;

private:
    bool isFirstMove = true;
};

class bishop : public figure{
public:
    bishop(bool isWhite);
    int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;
};

class kNight : public figure{
public:
    kNight(bool isWhite);
    int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;
};

class rook : public figure{
public:
    bool isMoved = false;

    rook(bool isWhite);
    int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;

};

class king :public figure{
public:
    king(bool isWhite);
    int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;

private:
    bool isMoved = false;
};

class queen : public figure{
public:
    queen(bool isWhite);
    int move(std::vector<figure*> &whiteFigure,std::vector<figure*> &blackFigure,
             sf::Vector2i newCoordinate,bool testCheck = false) override;

private:
    bishop *bishopForCheckMove;
    rook *rookForMove;
};

#endif //CHESSSFMLBOARD_FIGURE_H
