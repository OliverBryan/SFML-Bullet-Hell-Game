#include "UserInterface.hpp"
#include <iostream>

void UserInterface::update() {

}

void UserInterface::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(400, 400));
	shape.setPosition(sf::Vector2f(20, 20));
	shape.setFillColor(sf::Color::White);
	window.draw(shape);
}