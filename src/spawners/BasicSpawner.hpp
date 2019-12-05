#ifndef BASIC_SPAWNER_HPP
#define BASIC_SPAWNER_HPP

#include "Spawner.hpp"
#include "..\enemies\BasicEnemy.hpp"

class BasicSpawner : public Spawner {
public:
	BasicSpawner(float x, Environment* env) : Spawner(x, env) {
		FIRE_TIME = 60;
		defaultFill = sf::Color(35, 38, 36);
		m_fill = sf::Color(35, 38, 36);
		postMoveFill = sf::Color(35, 38, 36); //Unused
		warningMoveFill = sf::Color(35, 38, 36); //Unused
	}

protected:
	void spawnEnemy() override {
		Enemy* enemy = new BasicEnemy(m_position.x + 3, m_position.y + 20);
		m_env->addEnemy(enemy);
	}
};

#endif /* BASIC_SPAWNER_HPP */