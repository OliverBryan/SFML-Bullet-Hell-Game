#include "LaserEnemy.hpp"

void LaserEnemy::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(10, 380));
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color(255, 165, 0));
	window.draw(shape);
}

sf::FloatRect LaserEnemy::getBounds() {
	return sf::FloatRect(m_position, sf::Vector2f(10, 400));
}