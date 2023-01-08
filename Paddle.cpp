//
// Created by marek on 1/8/2023.
//

#include "Paddle.h"
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

Paddle::Paddle(int startPositionX, int startPositionY) {
    player.setSize(sf::Vector2f(10, 50));
    player.setFillColor(sf::Color::White);
    player.setPosition(startPositionX, startPositionY);
}

void Paddle::move(int offsetX, int offsetY) {
    player.move(offsetX, offsetY);
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


