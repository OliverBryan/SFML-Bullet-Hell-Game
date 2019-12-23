#include "Enemy.hpp"
#include "..\Environment.hpp"
#include <iostream>

int Enemy::update() {
	customUpdate();

	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;

	if (m_position.y >= 420 || m_position.y <= 0 || m_position.x >= 420 || m_position.x <= 10 || m_lifetime <= 0) {
		m_fill = sf::Color::Black;
	}
	else {
		m_fill = m_dfill;
	}
	if (m_position.y >= 430 || m_position.y <= 0 || m_position.x >= 430 || m_position.x <= 0 || m_lifetime <= 0) {
		return 1;
	}

	m_lifetime--;
	return 0;
}

void Enemy::init() {
	m_dfill = m_fill;
}

void Enemy::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(m_size.x, m_size.y));
	shape.setPosition(m_position);
	shape.setFillColor(m_fill);
	window.draw(shape);
}