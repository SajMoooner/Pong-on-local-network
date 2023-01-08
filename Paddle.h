//
// Created by marek on 1/8/2023.
//

#ifndef POSSEMESTRALKA_PADDLE_H
#define POSSEMESTRALKA_PADDLE_H
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


class Paddle {
private:
    sf::RectangleShape player;
    int WIDTH;
    int HEIGHT;
public:
    Paddle(int startPositionX, int startPositionY,   int WIDTHInput,  int HEIGHTInput);
    void move(int offsetX, int offsetY);
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();
    void setPosition(int newX, int newY);
    sf::RectangleShape getPlayer();

};


#endif //POSSEMESTRALKA_PADDLE_H
