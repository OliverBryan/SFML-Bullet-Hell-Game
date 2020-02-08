#ifndef RICOCHET_ENEMY_HPP
#define RICOCHET_ENEMY_HPP

#include "Enemy.hpp"
#include "..\spawners\Spawner.hpp"
#include <iostream>

class RicochetEnemy : public Enemy {
public:
	RicochetEnemy(float x, float y) : Enemy(x, y, static_cast<float>(irand(-5, 5)), 3, 275) {
		m_size = sf::Vector2f(10, 10);
		m_fill = sf::Color(255, 215, 0);
		init();
	}

	void customUpdate() override {
		if (m_position.x >= 410)
			m_velocity.x *= -1;
		if (m_position.x <= 20)
			m_velocity.x *= -1;
		if (m_position.y >= 410)
			m_velocity.y *= -1;
		if (m_position.y <= 20)
			m_velocity.y *= -1;
	}
};

#endif /* RICOCHET_ENEMY_HPP */