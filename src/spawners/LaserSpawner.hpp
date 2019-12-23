#ifndef LASER_SPAWNER_HPP
#define LASER_SPAWNER_HPP

#include "Spawner.hpp"
#include "..\enemies\LaserEnemy.hpp"

class LaserSpawner : public Spawner {
public:
	LaserSpawner(float x, Environment* env) : Spawner(x, env) { 
		FIRE_TIME = 300;
		POST_MOVE_TIME = 60;
		m_postMoveCounter = POST_MOVE_TIME;
		defaultFill = sf::Color::Red;
		m_fill = sf::Color::Red;
		postMoveFill = sf::Color(255, 165, 0);
		warningMoveFill = sf::Color::Red; //Unused
	}

protected:
	void spawnEnemy() override {
		Enemy* enemy = new LaserEnemy(m_position.x + 3, m_position.y + 20);
		m_env->addEnemy(enemy);
	}
};

#endif /* LASER_SPAWNER_HPP */