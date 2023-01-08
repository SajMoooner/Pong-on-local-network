//
// Created by marek on 1/8/2023.
//

#include "Ball.h"

Ball::Ball(int startPositionX, int startPositionY,  int WIDTHInput,  int HEIGHTInput) {
    ball.setRadius(10);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(startPositionX, startPositionY);
    velocityX = 1;
    velocityY = 1;

    WIDTH = WIDTHInput;
    HEIGHT = HEIGHTInput;
}

int Ball::movee(sf::FloatRect player1Bounds, sf::FloatRect player2Bounds){

    sf::Vector2f ball_velocity(velocityX, velocityY);
    ball.move(ball_velocity);
    if (ball.getPosition().y < 0 || ball.getPosition().y > HEIGHT - 20) {
        velocityY *= -1;
    }

    // Zisti či bola lopta dotknutá hráčom 1
    if (ball.getGlobalBounds().intersects(player1Bounds)) {
        velocityX *= -1;
    }

    // Zisti či bola lopta dotknutá hráčom 2
    if (ball.getGlobalBounds().intersects(player2Bounds)) {
        velocityX *= -1;
    }

    // Zisti či lopta skorovala
    if (ball.getPosition().x < 0) {
        ball.setPosition(WIDTH / 2, HEIGHT / 2);
        return 1;
    }

    if (ball.getPosition().x > WIDTH) {
        ball.setPosition(WIDTH / 2, HEIGHT / 2);
        return 2;
    }

    return 0;
}

sf::Vector2f Ball::getPosition() {
    return ball.getPosition();
}

sf::FloatRect Ball::getGlobalBounds() {
    return ball.getGlobalBounds();
};

sf::CircleShape Ball::getBall() {
    return ball;
};

void Ball::setPosition(int newX, int newY) {
    ball.setPosition(newX, newY);
};
