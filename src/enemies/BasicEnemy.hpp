#ifndef BASIC_ENEMY_HPP
#define BASIC_ENEMY_HPP

#include "Enemy.hpp"

class BasicEnemy : public Enemy {
public:
	BasicEnemy(float x, float y) : Enemy(x, y, 0, 2, 300) {}

	void render(sf::RenderWindow& window) override;
	sf::FloatRect getBounds() override;
};

#endif /* BASIC_ENEMY_HPP */