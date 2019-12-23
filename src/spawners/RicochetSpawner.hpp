#ifndef RICOCHET_SPAWNER_HPP
#define RICOCHET_SPAWNER_HPP

#include "Spawner.hpp"
#include "..\enemies\RicochetEnemy.hpp"

class RicochetSpawner : public Spawner {
public:
	RicochetSpawner(float x, Environment* env) : Spawner(x, env) {
		FIRE_TIME = 100;
		defaultFill = sf::Color(255, 215, 0);
		m_fill = sf::Color(255, 215, 0);
		postMoveFill = sf::Color(255, 215, 0); //Unused
		warningMoveFill = sf::Color(255, 215, 0); //Unused
	}

protected:
	void spawnEnemy() override {
		Enemy* enemy = new RicochetEnemy(m_position.x + 3, m_position.y + 20);
		m_env->addEnemy(enemy);
	}
};

#endif /* RICOCHET_SPAWNER_HPP */