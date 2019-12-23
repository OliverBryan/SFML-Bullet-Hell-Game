#ifndef BASIC_ENEMY_HPP
#define BASIC_ENEMY_HPP

#include "Enemy.hpp"

class BasicEnemy : public Enemy {
public:
	BasicEnemy(float x, float y) : Enemy(x, y, 0, 2, 300) {
		m_size = sf::Vector2f(10, 10);
		m_fill = sf::Color(sf::Color(35, 38, 36));
		init();
	}
};

#endif /* BASIC_ENEMY_HPP */