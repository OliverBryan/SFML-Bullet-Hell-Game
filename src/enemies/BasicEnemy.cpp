#include "BasicEnemy.hpp"

void BasicEnemy::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(10, 10));
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color(35, 38, 36));
	window.draw(shape);
}

sf::FloatRect BasicEnemy::getBounds() {
	return sf::FloatRect(m_position, sf::Vector2f(10, 10));
}