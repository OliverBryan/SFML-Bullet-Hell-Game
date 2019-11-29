#ifndef LASER_ENEMY_HPP
#define LASER_ENEMY_HPP

#include "Enemy.hpp"

class LaserEnemy : public Enemy {
public:
	LaserEnemy(float x, float y) : Enemy(x, y, 0, 0, 60) {}

	void render(sf::RenderWindow& window) override;
	sf::FloatRect getBounds() override;
};

#endif /* LASER_ENEMy_HPP */