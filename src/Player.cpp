#include "Player.hpp"

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_position.y -= m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_position.y += m_speed;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_position.x -= m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_position.x += m_speed;
	}

	if (m_position.x >= 400)
		m_position.x = 400;
	if (m_position.x <= 20)
		m_position.x = 20;
	if (m_position.y >= 400)
		m_position.y = 400;
	if (m_position.y <= 20)
		m_position.y = 20;
}

void Player::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(20, 20));
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color(35, 38, 36));

	window.draw(shape);
}

sf::FloatRect Player::getBounds() {
	return sf::FloatRect(m_position, sf::Vector2f(20, 20));
}