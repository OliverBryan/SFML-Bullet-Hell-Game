#ifndef LASER_ENEMY_HPP
#define LASER_ENEMY_HPP

#include "Enemy.hpp"

class LaserEnemy : public Enemy {
public:
	LaserEnemy(float x, float y) : Enemy(x, y, 0, 0, 60, sf::Color(255, 165, 0)) {
		m_size = sf::Vector2f(10, 380);
		init();
	}
};

#endif /* LASER_ENEMy_HPP */