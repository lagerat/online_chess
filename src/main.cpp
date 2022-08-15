#include "board.h"


std::vector<sf::CircleShape> createCircleShapes(std::vector<std::pair<int, int>> &possibleMoves) {
    std::vector<sf::CircleShape> shapesForPossibleMoves;
    for (auto it: possibleMoves) {
        sf::CircleShape tmp(20.f);
        tmp.setOrigin(-10.f, -10.f);
        tmp.setFillColor(sf::Color(153, 255, 51, 150));
        tmp.setPosition((float) it.first * 56 + 27, (float) it.second * 56 + 27);
        shapesForPossibleMoves.push_back(tmp);
    }
    return shapesForPossibleMoves;
}

enum boardStatements {
    clear,
    check,
    mat,
    stalemate
};


boardStatements checkOnCheckMate(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, figure *king,
                                 bool isWhite) {
//    int enemyFiguresAttackingKing = 0;
    std::vector<figure *> enemyFiguresAttackingKing;
    if (isWhite) {
        for (auto &figure: blackFigure) {
            if (!figure->move(whiteFigure, blackFigure, sf::Vector2i(king->getX(), king->getY()), true)) {
                enemyFiguresAttackingKing.push_back(figure);

            }
        }
        if (enemyFiguresAttackingKing.empty()) {
            return boardStatements::clear;
        }
    } else {
        for (auto &figure: whiteFigure) {
            if (!figure->move(whiteFigure, blackFigure, sf::Vector2i(king->getX(), king->getY()), true)) {
                enemyFiguresAttackingKing.push_back(figure);
            }
        }
        if (enemyFiguresAttackingKing.empty()) {
            return boardStatements::clear;
        }
    }

    if (!enemyFiguresAttackingKing.empty()) {
        bool possibleSaveMoveForKing = false;
        if (isWhite) {
            auto it = whiteFigure.begin();
            for (; it != whiteFigure.end(); it++) {
                if ((*it) == king) {
                    whiteFigure.erase(it);
                    break;
                }
            }
        } else {
            auto it = blackFigure.begin();
            for (; it != blackFigure.end(); it++) {
                if ((*it) == king) {
                    blackFigure.erase(it);
                    break;
                }
            }
        }
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                int newX = king->getX() + i;
                int newY = king->getY() + j;
                if (newX == king->getX() && newY == king->getY()) {
                    continue;
                }
                if (!king->move(whiteFigure, blackFigure, sf::Vector2i(newX, newY), true)) {
                    possibleSaveMoveForKing = true;
                    break;
                }
            }
        }
        if (isWhite) {
            whiteFigure.push_back(king);
        } else {
            blackFigure.push_back(king);
        }
        if (!possibleSaveMoveForKing && enemyFiguresAttackingKing.size() == 2) {
            return boardStatements::mat;
        }
        if (possibleSaveMoveForKing) {
            return boardStatements::check;
        }

        int countForFigures = 0;
        for (auto &figure: isWhite ? whiteFigure : blackFigure) {
            int currentX = enemyFiguresAttackingKing[0]->getX();
            int currentY = enemyFiguresAttackingKing[0]->getY();
            while (currentX != king->getX() && currentY != king->getY()) {
                if (!figure->move(whiteFigure, blackFigure, sf::Vector2i(currentX, currentY), true)) {
                    return boardStatements::check;
                }
                if (currentX - king->getX() > 0) {
                    currentX--;
                } else if (currentX - king->getX() < 0) {
                    currentX++;
                }
                if (currentY - king->getY() > 0) {
                    currentY--;
                } else if (currentY - king->getY() < 0) {
                    currentY++;
                }
            }
            countForFigures++;
        }
        return boardStatements::mat;

    }
}


figure *findKing(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, bool isWhite) {
    if (isWhite) {
        for (auto &figure: whiteFigure) {
            king *isKing = dynamic_cast<king *>(figure);
            if (isKing) {
                return isKing;
            }
        }
    } else {
        for (auto &figure: blackFigure) {
            king *isKing = dynamic_cast<king *>(figure);
            if (isKing) {
                return isKing;
            }
        }
    }
}

void moveUnderCheck(std::vector<figure *> &whiteFigure, std::vector<figure *> &blackFigure, bool isWhite,
                    std::vector<std::pair<int, int>> &possibleMoves, figure *movingFigure) {
    figure *king = findKing(whiteFigure, blackFigure, isWhite);
    figure *enemyFigure = nullptr;
    isWhite ? whiteFigure.push_back(movingFigure) : blackFigure.push_back(movingFigure);
    for (int i = 0; i < possibleMoves.size(); i++) {
        auto coordMoves = possibleMoves[i];
        for (auto enemy: isWhite ? blackFigure : whiteFigure) {
            if (enemy->getX() == coordMoves.first && enemy->getY() == coordMoves.second) {
                enemyFigure = enemy;
                break;
            }
        }
        if (enemyFigure) {
            isWhite ? blackFigure.erase(
                    std::remove(blackFigure.begin(), blackFigure.end(), enemyFigure), blackFigure.end()) :
            whiteFigure.erase(std::remove(whiteFigure.begin(), whiteFigure.end(), enemyFigure), whiteFigure.end());
        }
        std::pair<int, int> oldCoords{movingFigure->getX(), movingFigure->getY()};
        movingFigure->setCoordinate(sf::Vector2i(coordMoves.first, coordMoves.second));
        boardStatements stateAfterMove = checkOnCheckMate(whiteFigure, blackFigure, king, isWhite);
        if (stateAfterMove == boardStatements::check || stateAfterMove == boardStatements::mat) {
            possibleMoves.erase(std::remove(possibleMoves.begin(), possibleMoves.end(), coordMoves),
                                possibleMoves.end());
            i--;
        }
        movingFigure->setCoordinate(sf::Vector2i(oldCoords.first, oldCoords.second));
        if (enemyFigure) {
            isWhite ? blackFigure.push_back(enemyFigure) : whiteFigure.push_back(enemyFigure);
            enemyFigure = nullptr;
        }
    }
    isWhite ? whiteFigure.erase(std::remove(whiteFigure.begin(), whiteFigure.end(), movingFigure),
                                whiteFigure.end()) :
    blackFigure.erase(std::remove(blackFigure.begin(), blackFigure.end(), movingFigure),
                      blackFigure.end());

    // Проверять возможные ходы, которые мы до этого делаем, разрешать ходить, только если мы ходим на одну из клеток, полученных ранее
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(64);
    board board;
    boardStatements currentStateOfBoard = boardStatements::clear;
    bool isMove = false;
    bool whiteMove = true;
    sf::Font font;
    font.loadFromFile("../fonts/Psilent.otf");
    sf::Text whoMove("", font, 30);
    whoMove.setFillColor(sf::Color::White);
    whoMove.setString("White move");
    whoMove.setPosition(600, 30);
    figure *choosenFigure = nullptr;
    std::vector<figure *> x;
    std::vector<std::pair<int, int>> possibleMoves;
    std::vector<sf::CircleShape> shapesForPossibleMoves;

    while (window.isOpen()) {
        sf::Vector2i pos = sf::Mouse::getPosition(window) - sf::Vector2i(28, 28);
        sf::Event event{};
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (currentStateOfBoard == boardStatements::mat) {
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (whiteMove) {
                        for (int i = 0; i < board.whiteFigure.size(); ++i) {
                            if (board.whiteFigure[i]->chessFigureSprite.getGlobalBounds().contains((float) pos.x + 28,
                                                                                                   (float) pos.y +
                                                                                                   28)) {
                                shapesForPossibleMoves.clear();
                                possibleMoves.clear();
                                isMove = true;
                                choosenFigure = board.whiteFigure[i];
                                board.whiteFigure.erase(board.whiteFigure.cbegin() + i);
                                possibleMoves = board.findAllMoves(choosenFigure);
                                moveUnderCheck(board.whiteFigure, board.blackFigure, whiteMove, possibleMoves,
                                               choosenFigure);
                                shapesForPossibleMoves = createCircleShapes(possibleMoves);
                                break;
                            }
                        }
                    } else {
                        for (int i = 0; i < board.blackFigure.size(); ++i) {
                            if (board.blackFigure[i]->chessFigureSprite.getGlobalBounds().contains((float) pos.x + 28,
                                                                                                   (float) pos.y +
                                                                                                   28)) {
                                shapesForPossibleMoves.clear();
                                possibleMoves.clear();
                                isMove = true;
                                choosenFigure = board.blackFigure[i];
                                board.blackFigure.erase(board.blackFigure.cbegin() + i);
                                possibleMoves = board.findAllMoves(choosenFigure);
                                moveUnderCheck(board.whiteFigure, board.blackFigure, whiteMove, possibleMoves,
                                               choosenFigure);
                                shapesForPossibleMoves = createCircleShapes(possibleMoves);
                                break;
                            }
                        }
                    }
                }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    shapesForPossibleMoves.clear();
                    if (choosenFigure) {
                        if (whiteMove) {
                            isMove = false;
                            sf::Vector2i newPos = sf::Vector2i((int) (pos.x / 56), (int) (pos.y / 56));
                            auto it = std::find(possibleMoves.begin(), possibleMoves.end(),
                                                std::pair<int, int>(newPos.x, newPos.y));
                            if (it == possibleMoves.end() ||
                                (newPos.x == choosenFigure->getX() && newPos.y == choosenFigure->getY())) {
                                whiteMove = !whiteMove;
                                board.whiteFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                            } else if (newPos.x <= 7 && newPos.x >= 0 && newPos.y <= 7 && newPos.y >= 0) {
                                int resultCodeOfMove = choosenFigure->move(board.whiteFigure, board.blackFigure,
                                                                           newPos);
                                if (resultCodeOfMove) {
                                    if (resultCodeOfMove == 2) {
                                        board.whiteFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    } else {
                                        whiteMove = !whiteMove;
                                        board.whiteFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    }
                                } else {
                                    choosenFigure->setCoordinate(newPos);
                                    board.whiteFigure.push_back(choosenFigure);
                                    choosenFigure = nullptr;
                                    figure *king = findKing(board.whiteFigure, board.blackFigure, false);
                                    currentStateOfBoard = checkOnCheckMate(board.whiteFigure, board.blackFigure, king,
                                                                           false);
                                }
                            } else {
                                board.whiteFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                                whiteMove = !whiteMove;
                            }
                        } else {
                            isMove = false;
                            sf::Vector2i newPos = sf::Vector2i((int) (pos.x / 56), (int) (pos.y / 56));
                            auto it = std::find(possibleMoves.begin(), possibleMoves.end(),
                                                std::pair<int, int>(newPos.x, newPos.y));
                            if (it == possibleMoves.end() ||
                                (newPos.x == choosenFigure->getX() && newPos.y == choosenFigure->getY())) {
                                whiteMove = !whiteMove;
                                board.blackFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                            } else if (newPos.x <= 7 && newPos.x >= 0 && newPos.y <= 7 && newPos.y >= 0) {
                                int resultCodeMove = choosenFigure->move(board.whiteFigure, board.blackFigure, newPos);
                                if (resultCodeMove > 0) {
                                    if (resultCodeMove == 2) {
                                        board.blackFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    } else {
                                        whiteMove = !whiteMove;
                                        board.blackFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    }
                                } else {
                                    choosenFigure->setCoordinate(newPos);
                                    board.blackFigure.push_back(choosenFigure);
                                    choosenFigure = nullptr;
                                    figure *king = findKing(board.whiteFigure, board.blackFigure, true);
                                    currentStateOfBoard = checkOnCheckMate(board.whiteFigure, board.blackFigure, king,
                                                                           true);
                                }
                            } else {
                                whiteMove = !whiteMove;
                                board.blackFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                            }
                        }
                        whiteMove = !whiteMove;
                    }
                }
        }

        switch (currentStateOfBoard) {
            case clear:
                if (whiteMove) {
                    whoMove.setString("White move");
                    break;
                } else {
                    whoMove.setString("Black move");
                }
                break;
            case check:
                if (whiteMove) {
                    whoMove.setString("White move\nUnder check");
                    break;
                } else {
                    whoMove.setString("Black move\nUnder check");
                }
                break;
            case mat:
                if (whiteMove) {
                    whoMove.setString("Black Wins\nGame End");
                    break;
                } else {
                    whoMove.setString("White Wins\nGame End");
                }
                break;
            case stalemate:
                break;
        }
        window.clear();
        board.draw(window);
        window.draw(whoMove);
        if (isMove) {
            choosenFigure->chessFigureSprite.setPosition((float) pos.x, (float) pos.y);
            choosenFigure->draw(window);
        }
        for (const auto &it: shapesForPossibleMoves) {
            window.draw(it);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}