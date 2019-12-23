#ifndef HOMING_ENEMY_HPP
#define HOMING_ENEMY_HPP

#include "..\Environment.hpp"
#include "Enemy.hpp"

class HomingEnemy : public Enemy {
public:
	HomingEnemy(float x, float y, Environment* env) : Enemy(x, y, 0, 0, 400), m_env(env) {
		m_size = sf::Vector2f(10, 10);
		m_fill = sf::Color(0, 128, 0);
		init();
	}

	void customUpdate() override {
		float playerX = m_env->getPlayer()->getBounds().left;
		float playerY = m_env->getPlayer()->getBounds().top;
		float differenceX = m_position.x - playerX - 10;
		float differenceY = m_position.y - playerY - 10;
		float distance = std::sqrtf(((m_position.x - playerX) * (m_position.x - playerX)) + ((m_position.y - playerY) * (m_position.y - playerY)));

		m_velocity.x = (-1 / distance) * differenceX;
		m_velocity.y = (-1 / distance) * differenceY;
	}

private:
	Environment* m_env;
};

#endif /* HOMING_ENEMY_HPP */