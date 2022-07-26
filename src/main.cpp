#include "board.h"


std::vector<sf::CircleShape> createCircleShapes(std::vector<std::pair<int,int>> &possibleMoves){
    std::vector<sf::CircleShape> shapesForPossibleMoves;
    for(auto it: possibleMoves){
        sf::CircleShape tmp(20.f);
        tmp.setOrigin(-10.f,-10.f);
        tmp.setFillColor(sf::Color(153,255,51,150));
        tmp.setPosition((float)it.first * 56 + 27, (float)it.second * 56 + 27);
        shapesForPossibleMoves.push_back(tmp);
    }
    return shapesForPossibleMoves;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    window.setFramerateLimit(64);
    board b;
    bool isMove = false;
    bool whiteMove = true;
    sf::Font font;
    font.loadFromFile("../fonts/Psilent.otf");
    sf::Text whoMove("",font,30);
    whoMove.setFillColor(sf::Color::White);
    whoMove.setString("White move");
    whoMove.setPosition(600,30);
    figure *choosenFigure = nullptr;
    std::vector<figure*> x;
    std::vector<std::pair<int,int>> possibleMoves;
    std::vector<sf::CircleShape> shapesForPossibleMoves;

    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window) - sf::Vector2i(28,28);
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left){
                    if (whiteMove){
                        for (int i = 0; i < b.whiteFigure.size(); ++i) {
                            if (b.whiteFigure[i]->chessFigureSprite.getGlobalBounds().contains((float)pos.x + 28,
                                                                                               (float)pos.y + 28)) {
                                shapesForPossibleMoves.clear();
                                possibleMoves.clear();
                                isMove = true;
                                choosenFigure = b.whiteFigure[i];
                                b.whiteFigure.erase(b.whiteFigure.cbegin() + i);
                                possibleMoves = b.findAllMoves(choosenFigure);
                                shapesForPossibleMoves = createCircleShapes(possibleMoves);
                                break;
                            }
                        }
                    } else{
                        for (int i = 0; i < b.blackFigure.size(); ++i) {
                            if (b.blackFigure[i]->chessFigureSprite.getGlobalBounds().contains((float)pos.x + 28,
                                                                                               (float)pos.y + 28)) {
                                shapesForPossibleMoves.clear();
                                possibleMoves.clear();
                                isMove = true;
                                choosenFigure = b.blackFigure[i];
                                b.blackFigure.erase(b.blackFigure.cbegin() + i);
                                possibleMoves = b.findAllMoves(choosenFigure);
                                shapesForPossibleMoves = createCircleShapes(possibleMoves);
                                break;
                            }
                        }
                    }
                }
            if (event.type == sf::Event::MouseButtonReleased)
                if (event.mouseButton.button == sf::Mouse::Left){
                    shapesForPossibleMoves.clear();
                    if (choosenFigure){
                        if (whiteMove){
                            whoMove.setString("Black move");
                            isMove = false;
                            sf::Vector2i newPos = sf::Vector2i((int)(pos.x / 56),(int)(pos.y / 56));
                            if (newPos.x == choosenFigure->getX() && newPos.y == choosenFigure->getY()){
                                whiteMove = !whiteMove;
                                whoMove.setString("White move");
                                b.whiteFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                            }else if (newPos.x <= 7 && newPos.x >= 0 && newPos.y <= 7 && newPos.y >= 0){
                                int resultCodeOfMove = choosenFigure->move(b.whiteFigure, b.blackFigure, newPos);
                                if (resultCodeOfMove){
                                    if (resultCodeOfMove == 2){
                                        b.whiteFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    } else{
                                        whiteMove = !whiteMove;
                                        whoMove.setString("White move");
                                        b.whiteFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    }
                                } else{
                                    choosenFigure->setCoordinate(newPos);
                                    b.whiteFigure.push_back(choosenFigure);
                                    choosenFigure = nullptr;
                                }
                            } else{
                                b.whiteFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                                whiteMove = !whiteMove;
                                whoMove.setString("White move");
                            }
                        } else{
                            whoMove.setString("White move");
                            isMove = false;
                            sf::Vector2i newPos = sf::Vector2i((int)(pos.x / 56),(int)(pos.y / 56));
                            if (newPos.x == choosenFigure->getX() && newPos.y == choosenFigure->getY()){
                                whiteMove = !whiteMove;
                                whoMove.setString("Black move");
                                b.blackFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                            }
                            else if (newPos.x <= 7 && newPos.x >= 0 && newPos.y <= 7 && newPos.y >= 0){
                                int resultCodeMove = choosenFigure->move(b.whiteFigure, b.blackFigure, newPos);
                                if (resultCodeMove > 0){
                                    if (resultCodeMove == 2){
                                        b.blackFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    }else{
                                        whiteMove = !whiteMove;
                                        whoMove.setString("Black move");
                                        b.blackFigure.push_back(choosenFigure);
                                        choosenFigure = nullptr;
                                    }
                                } else{
                                    choosenFigure->setCoordinate(newPos);
                                    b.blackFigure.push_back(choosenFigure);
                                    choosenFigure = nullptr;
                                }
                            } else{
                                whiteMove = !whiteMove;
                                b.blackFigure.push_back(choosenFigure);
                                choosenFigure = nullptr;
                                whoMove.setString("Black move");
                            }
                        }
                        whiteMove = !whiteMove;
                    }
                }
        }

        window.clear();
        b.draw(window);
        window.draw(whoMove);
        if (isMove){
            choosenFigure->chessFigureSprite.setPosition((float)pos.x, (float)pos.y);
            choosenFigure->draw(window);
        }
        for(const auto& it: shapesForPossibleMoves){
            window.draw(it);
        }
        window.display();
    }
    return EXIT_SUCCESS;
}