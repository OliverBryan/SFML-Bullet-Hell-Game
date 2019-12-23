#ifndef HOMING_SPAWNER_HPP
#define HOMING_SPAWNER_HPP

#include "Spawner.hpp"
#include "..\enemies\HomingEnemy.hpp"

class HomingSpawner : public Spawner {
public:
	HomingSpawner(float x, Environment* env) : Spawner(x, env) {
		FIRE_TIME = 400;
		POST_MOVE_TIME = 10;
		m_postMoveCounter = POST_MOVE_TIME;
		defaultFill = sf::Color(0, 128, 0); //0, 128, 0
		m_fill = sf::Color(0, 128, 0);
		postMoveFill = sf::Color(0, 128, 0); //Unused
		warningMoveFill = sf::Color(0, 128, 0); // Unused
	}
protected:
	void spawnEnemy() override {
		Enemy* enemy = new HomingEnemy(m_position.x + 3, m_position.y + 20, m_env);
		m_env->addEnemy(enemy);
	}
};

#endif /* HOMING_SPAWNER_HPP */