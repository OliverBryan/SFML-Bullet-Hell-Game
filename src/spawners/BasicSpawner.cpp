#include "BasicSpawner.hpp"
#include "Environment.hpp"
#include "BasicEnemy.hpp"
#include <iostream>

int BasicSpawner::FIRE_TIME = 60;

void BasicSpawner::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(16, 20));
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color(35, 38, 36));
	window.draw(shape);
}

void BasicSpawner::spawnEnemy() {
	Enemy* enemy = new BasicEnemy(m_position.x + 3, m_position.y + 20);
	m_env->addEnemy(enemy);
}