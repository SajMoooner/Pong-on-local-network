//
// Created by marek on 1/8/2023.
//

#ifndef POSSEMESTRALKA_BALL_H
#define POSSEMESTRALKA_BALL_H
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>


class Ball {
private:
    sf::CircleShape ball;
    int velocityX;
    int velocityY;
    int WIDTH;
    int HEIGHT;
public:
    Ball(int startPositionX, int startPositionY, int WIDTH, int HEIGHT);
    void move(sf::FloatRect player1Bounds, sf::FloatRect player2Bounds, int* score1N, int* score2N);
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();
    sf::CircleShape getBall();
    void setPosition(int newX, int newY);
};


#endif //POSSEMESTRALKA_BALL_H
