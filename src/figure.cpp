#include "figure.h"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

figure::figure() {
    figuresTextures.loadFromFile("../images/figures.png");
}

int figure::getX() {
    return this->x;
}

int figure::getY() {
    return this->y;
}

void figure::setX(int x) {
    this->x = x;
    return;
}

void figure::setY(int y) {
    this->y = y;
    return;
}

void figure::setCoordinate(sf::Vector2i coordinate) {
    this->x = coordinate.x;
    this->y = coordinate.y;
}

void figure::draw(sf::RenderWindow &window) {
    window.draw(chessFigureSprite);
    return;
}

int
figure::finalMove(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i &newCoordinate,
                  bool testCheck) {
    auto whiteEnemy = whiteFigure.begin();
    auto blackEnemy = blackFigure.begin();
    bool blackEnemyFind = false;
    bool whiteEnemyFind = false;
    for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
        if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
            whiteEnemy = it;
            whiteEnemyFind = true;
            break;
        }
    }
    for(auto it = blackFigure.begin(); it != blackFigure.end(); it++){
        if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
            blackEnemy = it;
            blackEnemyFind = true;
            break;
        }
    }
    if (!blackEnemyFind && !whiteEnemyFind){
        return 0;
    }
    if ((isWhite && !blackEnemyFind) || (!isWhite && !whiteEnemyFind)){
        return 1;
    } else {
        figure* enemyFigure = nullptr;
        if (testCheck){
            return 0;
        }
        if (isWhite){
            enemyFigure = (*blackEnemy);
            blackFigure.erase(blackEnemy);
            delete enemyFigure;
            return 0;
        } else {
            enemyFigure = (*whiteEnemy);
            whiteFigure.erase(whiteEnemy);
            delete enemyFigure;
            return 0;
        }
    }
}

void figure::dropAsile(std::vector<figure *> &figure) {
    for (auto it = figure.begin(); it != figure.end(); it++){
        (*it)->takingOnAsileIsPossible = false;
    }
}

whitePawn::whitePawn() {
    chessFigureSprite.setTexture(figuresTextures);
    chessFigureSprite.setTextureRect(sf::IntRect(56 * 5,56 * 1,56,56));
    isWhite = true;
}

int whitePawn::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
                    bool testCheck) {
    bool ceilIsEmpty = true;
    if ((this->y - newCoordinate.y == 2 || this->y - newCoordinate.y == 1)  && newCoordinate.x == this->x){
        for (int i = 0; i < this->y - newCoordinate.y ; i++) {
            for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
                if ((*it)->getY() == newCoordinate.y + i && (*it)->getX() == newCoordinate.x){
                    ceilIsEmpty = false;
                    break;
                }
            }
            for (auto it = blackFigure.begin(); it != blackFigure.end(); it++){
                if ((*it)->getY() == newCoordinate.y + i && (*it)->getX() == newCoordinate.x){
                    ceilIsEmpty = false;
                    break;
                }
            }
        }
        if (!ceilIsEmpty){
            return 1;
        }
        if (!isFirstMove && this->y - newCoordinate.y == 2){
            return 1;
        }
        if (!testCheck){
            isFirstMove = false;
        }
        if (this->y - newCoordinate.y == 2 && !testCheck){
            takingOnAsileIsPossible = true;
        }
        if (!testCheck){
            dropAsile(blackFigure);
        }
        return 0;
    } else if (this->y - newCoordinate.y == 1 && abs(this->x - newCoordinate.x) == 1){
        figure* enemyFigure = nullptr;
        for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
            if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
                return 1;
            }
        }
        for (auto it = blackFigure.begin(); it != blackFigure.end(); it++){
            if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
                if(testCheck){
                    return 0;
                }
                enemyFigure = (*it);
                blackFigure.erase(it);
                delete enemyFigure;
                dropAsile(blackFigure);
                return 0;
            } else if((*it)->getY() == newCoordinate.y + 1 && (*it)->getX() == newCoordinate.x){
                if ((*it)->takingOnAsileIsPossible){
                    if(testCheck){
                        return 0;
                    }
                    enemyFigure = (*it);
                    blackFigure.erase(it);
                    delete enemyFigure;
                    dropAsile(blackFigure);
                    return 0;
                }
            }
        }
        return 1;
    } else {
        return 1;
    }
}


blackPawn::blackPawn() {
    chessFigureSprite.setTexture(figuresTextures);
    chessFigureSprite.setTextureRect(sf::IntRect(56 * 5,0,56,56));
    isWhite = false;
}

int blackPawn::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
                    bool testCheck) {
    bool ceilIsEmpty = true;
    if ((newCoordinate.y - this->y == 2 || newCoordinate.y - this->y == 1)  && newCoordinate.x == this->x){
        for (int i = 0; i < newCoordinate.y - this->y ; i++) {
            for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
                if ((*it)->getY() == newCoordinate.y - i && (*it)->getX() == newCoordinate.x){
                    ceilIsEmpty = false;
                    break;
                }
            }
            for (auto it = blackFigure.begin(); it != blackFigure.end(); it++){
                if ((*it)->getY() == newCoordinate.y - i && (*it)->getX() == newCoordinate.x){
                    ceilIsEmpty = false;
                    break;
                }
            }
        }
        if (!ceilIsEmpty){
            return 1;
        }
        if (!isFirstMove && newCoordinate.y - this->y == 2){
            return 1;
        }
        if (!testCheck){
            isFirstMove = false;
        }
        if (newCoordinate.y - this->y == 2 && !testCheck){
            takingOnAsileIsPossible = true;
        }
        if (!testCheck){
            dropAsile(whiteFigure);
        }
        return 0;
    } else if (newCoordinate.y - this->y == 1 && abs(newCoordinate.x - this->x) == 1){
        figure* enemyFigure = nullptr;
        for(auto it = blackFigure.begin(); it != blackFigure.end(); it++){
            if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
                return 1;
            }
        }
        for (auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
            if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
                if(testCheck){
                    return 0;
                }
                enemyFigure = (*it);
                whiteFigure.erase(it);
                delete enemyFigure;
                dropAsile(whiteFigure);
                return 0;
            } else if((*it)->getY() == newCoordinate.y - 1 && (*it)->getX() == newCoordinate.x){
                if ((*it)->takingOnAsileIsPossible){
                    if(testCheck){
                        return 0;
                    }
                    enemyFigure = (*it);
                    whiteFigure.erase(it);
                    delete enemyFigure;
                    dropAsile(whiteFigure);
                    return 0;
                }
            }
        }
        return 1;
    } else {
        return 1;
    }
    return 0;
}

bishop::bishop(bool isWhite) {
    this->isWhite = isWhite;
    chessFigureSprite.setTexture(figuresTextures);
    if (!isWhite){
        chessFigureSprite.setTextureRect(sf::IntRect(56 * 2,0,56,56));
    } else{
        chessFigureSprite.setTextureRect(sf::IntRect(56 * 2,56,56,56));
    }
}

int bishop::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
                 bool testCheck) {
    if (isWhite){
        dropAsile(blackFigure);
    } else{
        dropAsile(whiteFigure);
    }
    if (abs(newCoordinate.x - this->x) != abs(newCoordinate.y - this->y)){
        return 1;
    }
    int abciss = this->x;
    int ordinate = this->y;
    while (abciss != newCoordinate.x && ordinate != newCoordinate.y){
        for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
            if ((*it)->getY() == ordinate && (*it)->getX() == abciss){
                return 1;
            }
        }
        for(auto it = blackFigure.begin(); it != blackFigure.end(); it++){
            if ((*it)->getY() == ordinate && (*it)->getX() == abciss){
                return 1;
            }
        }
        if (newCoordinate.x - this->x > 0){
            abciss++;
        } else{
            abciss--;
        }
        if (newCoordinate.y - this->y > 0){
            ordinate++;
        } else{
            ordinate--;
        }
    }
    return finalMove(whiteFigure, blackFigure, newCoordinate,testCheck);
}

kNight::kNight(bool isWhite) {
    this->isWhite = isWhite;
    chessFigureSprite.setTexture(figuresTextures);
    if (!isWhite){
        chessFigureSprite.setTextureRect(sf::IntRect(56,0,56,56));
    } else{
        chessFigureSprite.setTextureRect(sf::IntRect(56,56,56,56));
    }
}

int kNight::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
                 bool testCheck) {
    if (isWhite){
        dropAsile(blackFigure);
    } else{
        dropAsile(whiteFigure);
    }
    bool correctMove = false;
    if((abs(newCoordinate.x - this->x) == 1 && abs(newCoordinate.y - this->y) == 2 ) ||
       abs(newCoordinate.y - this->y) == 1 && abs(newCoordinate.x - this->x) == 2){
        correctMove = true;
    }
    if (!correctMove){
        return 1;
    }
    return finalMove(whiteFigure, blackFigure, newCoordinate,testCheck);
}

rook::rook(bool isWhite) {
    this->isWhite = isWhite;
    chessFigureSprite.setTexture(figuresTextures);
    if (!isWhite){
        chessFigureSprite.setTextureRect(sf::IntRect(0,0,56,56));
    } else{
        chessFigureSprite.setTextureRect(sf::IntRect(0,56,56,56));
    }
}

int rook::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
               bool testCheck) {
    if (isWhite){
        dropAsile(whiteFigure);
    } else{
        dropAsile(blackFigure);
    }
    bool correctMove = false;
    if ((abs(newCoordinate.x - this->x) != 0 && newCoordinate.y == this->y)
        || (abs(newCoordinate.y - this->y) != 0 && newCoordinate.x == this->x)){
        correctMove = true;
    }
    if (!correctMove){
        return 1;
    }
    int i = this->x;
    while (i != newCoordinate.x){
        for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
            if ((*it)->getY() == newCoordinate.y && (*it)->getX() == i){
                return 1;
            }
        }
        for(auto it = blackFigure.begin(); it != blackFigure.end(); it++){
            if ((*it)->getY() == newCoordinate.y && (*it)->getX() == i){
                return 1;
            }
        }
        if (newCoordinate.x - this->x > 0){
            i++;
        } else{
            i--;
        }
    }
    i = this->y;
    while (i != newCoordinate.y){
        for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
            if ((*it)->getX() == newCoordinate.x && (*it)->getY() == i){
                return 1;
            }
        }
        for(auto it = blackFigure.begin(); it != blackFigure.end(); it++){
            if ((*it)->getX() == newCoordinate.x && (*it)->getY() == i){
                return 1;
            }
        }
        if (newCoordinate.y - this->y > 0){
            i++;
        } else{
            i--;
        }
    }
    if (!testCheck){
        isMoved = true;
    }
    return finalMove(whiteFigure, blackFigure, newCoordinate,testCheck);
}

king::king(bool isWhite) {
    chessFigureSprite.setTexture(figuresTextures);
    this->isWhite = isWhite;
    if (!isWhite){
        chessFigureSprite.setTextureRect(sf::IntRect(56 * 4,0,56,56));
    } else{
        chessFigureSprite.setTextureRect(sf::IntRect(56 * 4,56,56,56));
    }
}

int king::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
               bool testCheck) {
    if (isWhite){
        dropAsile(blackFigure);
    } else{
        dropAsile(whiteFigure);
    }


    auto whiteEnemy = whiteFigure.begin();
    auto blackEnemy = blackFigure.begin();
    bool blackEnemyFind = false;
    bool whiteEnemyFind = false;
    for(auto it = whiteFigure.begin(); it != whiteFigure.end(); it++){
        if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
            whiteEnemy = it;
            whiteEnemyFind = true;
            break;
        }
    }
    for(auto it = blackFigure.begin(); it != blackFigure.end(); it++){
        if ((*it)->getY() == newCoordinate.y && (*it)->getX() == newCoordinate.x){
            blackEnemy = it;
            blackEnemyFind = true;
            break;
        }
    }
    //Castiling
    if (isWhite && whiteEnemyFind && !isMoved){
        rook * isRook = dynamic_cast<rook*>((*whiteEnemy));
        if (isRook && !isRook->isMoved){
            int checkX = this->x;
            while (checkX != isRook->getX()){
                for (auto & it : whiteFigure) {
                    if (it->getX() == checkX && it->getY() == this->y){
//                            delete isRook;
                        return 1;
                    }
                }
                for (auto & it : blackFigure) {
                    if (it->getX() == checkX && it->getY() == this->y){
//                            delete isRook;
                        return 1;
                    }
                }
                if (checkX - isRook->getX() < 0){
                    checkX++;
                }else if(checkX - isRook->getX() > 0){
                    checkX--;
                }
            }
            if (testCheck){
                return 0;
            }
            if (this->x - isRook->getX() < 0){
                this->setCoordinate(sf::Vector2i(6, this->y));
                isRook->setCoordinate(sf::Vector2i(5,isRook->getY()));
                this->isMoved = true;
                isRook->isMoved = true;
                return 2;
            } else{
                this->setCoordinate(sf::Vector2i(2, this->y));
                isRook->setCoordinate(sf::Vector2i(3,isRook->getY()));
                this->isMoved = true;
                isRook->isMoved = true;
                return 2;
            }
        } else{
            return 1;
        }
    }else if(!isWhite && blackEnemyFind && !isMoved){
        rook * isRook = dynamic_cast<rook*>((*blackEnemy));
        if (isRook && !isRook->isMoved){
            int checkX = this->x;
            while (checkX != isRook->getX()){
                for (auto & it : whiteFigure) {
                    if (it->getX() == checkX && it->getY() == this->y){
                        return 1;
                    }
                }
                for (auto & it : blackFigure) {
                    if (it->getX() == checkX && it->getY() == this->y){
                        return 1;
                    }
                }
                if (checkX - isRook->getX() < 0){
                    checkX++;
                }else if(checkX - isRook->getX() > 0){
                    checkX--;
                }
            }
            if (testCheck){
                return 0;
            }
            if (this->x - isRook->getX() < 0){
                this->setCoordinate(sf::Vector2i(6, this->y));
                isRook->setCoordinate(sf::Vector2i(5,isRook->getY()));
                this->isMoved = true;
                isRook->isMoved = true;
                return 2;
            } else{
                this->setCoordinate(sf::Vector2i(2, this->y));
                isRook->setCoordinate(sf::Vector2i(3,isRook->getY()));
                this->isMoved = true;
                isRook->isMoved = true;
                return 2;
            }
        } else{
            return 1;
        }
    }
    if (abs(newCoordinate.x - this->x) > 1 || abs(newCoordinate.y - this->y) > 1){
        return 1;
    }
    if ((isWhite && whiteEnemyFind) || (!isWhite && blackEnemyFind)){
        return 1;
    }
    sf::Vector2i oldPosition(this->x, this->y);
    this->setCoordinate(newCoordinate);
    if (isWhite && blackEnemyFind){
        whiteFigure.push_back(this);
        figure* blackEnemyPointer = (*blackEnemy);
        blackFigure.erase(blackEnemy);
        for(int i = 0; i < blackFigure.size(); i++){
            figure *checkingFigure = blackFigure[0];
            blackFigure.erase(blackFigure.begin());
            if(!checkingFigure->move(whiteFigure,blackFigure,newCoordinate, true)){
//                   blackFigure.push_back((*blackEnemy));
                blackFigure.push_back(blackEnemyPointer);
                whiteFigure.pop_back();
                this->setCoordinate(oldPosition);
                blackFigure.push_back(checkingFigure);
                return 1;
            }
            blackFigure.push_back(checkingFigure);
        }
        whiteFigure.pop_back();
    } else if (!isWhite && whiteEnemyFind){
        blackFigure.push_back(this);
        whiteFigure.erase(whiteEnemy);
        for(int i = 0; i < whiteFigure.size(); i++){
            figure *checkingFigure = whiteFigure[0];
            whiteFigure.erase(whiteFigure.begin());
            if(!checkingFigure->move(whiteFigure,blackFigure,newCoordinate, true)){
                whiteFigure.push_back((*blackEnemy));
                blackFigure.pop_back();
                this->setCoordinate(oldPosition);
                whiteFigure.push_back(checkingFigure);
                return 1;
            }
            whiteFigure.push_back(checkingFigure);
        }
        blackFigure.pop_back();
    } else if (!blackEnemyFind && !whiteEnemyFind){
        if (isWhite){
            whiteFigure.push_back(this);
            for(int i = 0; i < blackFigure.size(); i++){
                figure *checkingFigure = blackFigure[0];
                blackFigure.erase(blackFigure.begin());
                if(!checkingFigure->move(whiteFigure,blackFigure,newCoordinate, true)){
                    whiteFigure.pop_back();
                    blackFigure.push_back(checkingFigure);
                    this->setCoordinate(oldPosition);
                    return 1;
                }
                blackFigure.push_back(checkingFigure);
            }
            whiteFigure.pop_back();
        } else{
            blackFigure.push_back(this);
            for(int i = 0; i < whiteFigure.size(); i++){
                figure *checkingFigure = whiteFigure[0];
                whiteFigure.erase(whiteFigure.begin());
                if(!checkingFigure->move(whiteFigure,blackFigure,newCoordinate, true)){
                    blackFigure.pop_back();
                    this->setCoordinate(oldPosition);
                    whiteFigure.push_back(checkingFigure);
                    return 1;
                }
                whiteFigure.push_back(checkingFigure);
            }
            blackFigure.pop_back();
        }
    }

    this->setCoordinate(oldPosition);
    if (!testCheck){
        isMoved = true;
    }
    return finalMove(whiteFigure,blackFigure,newCoordinate);
}

queen::queen(bool isWhite) {
    chessFigureSprite.setTexture(figuresTextures);
    this->isWhite = isWhite;
    if (!isWhite){
        chessFigureSprite.setTextureRect(sf::IntRect(56 * 3,0,56,56));
    } else{
        chessFigureSprite.setTextureRect(sf::IntRect(56 * 3,56,56,56));
    }
    bishopForCheckMove = new bishop(isWhite);
    rookForMove = new rook(isWhite);
}

int queen::move(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, sf::Vector2i newCoordinate,
                bool testCheck) {
    if (isWhite){
        dropAsile(blackFigure);
    } else{
        dropAsile(whiteFigure);
    }
    bishopForCheckMove->setX(this->x);
    bishopForCheckMove->setY(this->y);
    rookForMove->setX(this->x);
    rookForMove->setY(this->y);
    if (!bishopForCheckMove->move(whiteFigure,blackFigure,newCoordinate,testCheck)){
        return 0;
    }else if (!rookForMove->move(whiteFigure,blackFigure,newCoordinate,testCheck)){
        return 0;
    } else{
        return 1;
    }
}


