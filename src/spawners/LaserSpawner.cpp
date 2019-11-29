#include "LaserSpawner.hpp"
#include "..\Environment.hpp"
#include "..\enemies\LaserEnemy.hpp"

void LaserSpawner::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(16, 20));
	shape.setPosition(m_position);
	shape.setFillColor(m_inPostMove ? sf::Color(255, 165, 0) : sf::Color::Red);
	window.draw(shape);
}

void LaserSpawner::update() {
	m_counter++;
	if (m_counter >= FIRE_TIME && m_position.x != m_newX && m_position.x != m_newX + 1) {
		m_newX >= m_position.x ? m_position.x += 2 : m_position.x -= 2;
	}
	else if ((m_position.x == m_newX || m_position.x == m_newX + 1) && m_postMoveCounter > 0) {
		m_postMoveCounter--;
		m_inPostMove = true;
	}
	else if (m_counter >= FIRE_TIME && m_postMoveCounter <= 0) {
		spawnEnemy();
		m_counter = 0;
		m_newX = irand(20, 404);
		m_inPostMove = false;
		m_postMoveCounter = 60;
	}
}

void LaserSpawner::spawnEnemy() {
	Enemy* enemy = new LaserEnemy(m_position.x + 3, m_position.y + 20);
	m_env->addEnemy(enemy);
}