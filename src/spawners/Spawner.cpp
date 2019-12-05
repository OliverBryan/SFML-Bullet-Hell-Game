#include "Spawner.hpp"
#include <iostream>

Spawner::Spawner(float x, Environment* env) : 
m_position(x, 20), m_env(env) {
	m_newX = irand(20, 404);
}

void Spawner::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(16, 20));
	shape.setPosition(m_position);
	shape.setFillColor(m_fill);
	window.draw(shape);
}

void Spawner::update() {
	spawnerUpdate();

	m_counter++;
	if (m_counter >= FIRE_TIME && m_position.x != m_newX && m_position.x != m_newX + 1) {
		m_newX >= m_position.x ? m_position.x += 2 : m_position.x -= 2;
	}
	else if ((m_position.x == m_newX || m_position.x == m_newX + 1) && m_postMoveCounter > 0) {
		m_postMoveCounter--;
		m_fill = postMoveFill;
	}
	else if (m_counter >= FIRE_TIME && m_postMoveCounter <= 0) {
		spawnEnemy();
		m_counter = 0;
		m_newX = irand(20, 404);
		m_fill = defaultFill;
		m_postMoveCounter = POST_MOVE_TIME;
	}
}