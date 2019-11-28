#include "Spawner.hpp"
#include <iostream>

Spawner::Spawner(float x, Environment* env) : 
m_position(x, 20), m_env(env) {
	m_newX = irand(20, 404);
}

void Spawner::update() {
	m_counter++;
	if (m_counter >= FIRE_TIME && m_position.x != m_newX && m_position.x != m_newX + 1) {
		m_newX >= m_position.x ? m_position.x += 2 : m_position.x -= 2;
	}
	else if (m_counter >= FIRE_TIME) {
		spawnEnemy();
		m_counter = 0;
		m_newX = irand(20, 404);
	}
}