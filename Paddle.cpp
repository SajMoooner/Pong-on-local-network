//
// Created by marek on 1/8/2023.
//

#include "Paddle.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

Paddle::Paddle(int startPositionX, int startPositionY,   int WIDTHInput,  int HEIGHTInput) {
    player.setSize(sf::Vector2f(10, 50));
    player.setFillColor(sf::Color::White);
    player.setPosition(startPositionX, startPositionY);

    WIDTH = WIDTHInput;
    HEIGHT = HEIGHTInput;
}

void Paddle::move(int offsetX, int offsetY) {
    player.move(offsetX, offsetY);

    if (player.getPosition().y < 0) {
        player.setPosition(player.getPosition().x, 0);
    }
    if (player.getPosition().y > HEIGHT - 50) {
        player.setPosition(player.getPosition().x, HEIGHT - 50);
    }
}

sf::Vector2f Paddle::getPosition() {
    return player.getPosition();
}

sf::RectangleShape Paddle::getPlayer() {
    return player;
}

sf::FloatRect Paddle::getGlobalBounds() {
    return player.getGlobalBounds();
}

void Paddle::setPosition(int newX, int newY) {
    player.setPosition(newX, newY);
}


