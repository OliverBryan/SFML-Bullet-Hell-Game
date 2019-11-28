#include "Enemy.hpp"
#include "Environment.hpp"

int Enemy::update() {
	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;

	if (m_position.y >= 410 || m_position.y <= 0 || m_position.x >= 410 || m_position.x <= 0 || m_lifetime <= 0) {
		return 1;
	}

	m_lifetime--;
}