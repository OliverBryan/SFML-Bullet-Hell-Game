#ifndef WAVE_SPAWNER_HPP
#define WAVE_SPAWNER_HPP

#include "Spawner.hpp"
#include "..\enemies\BasicEnemy.hpp"

class WaveSpawner : public Spawner {
public:
	WaveSpawner(float x, Environment* env) : Spawner(x, env) {
		FIRE_TIME = 400;
		POST_MOVE_TIME = 0;
		defaultFill = sf::Color(0, 0, 255);
		m_fill = sf::Color(0, 0, 255);
		postMoveFill = sf::Color(0, 0, 255); //Unused
		warningMoveFill = sf::Color(0, 206, 209);
	}

	void spawnerUpdate() override {
		if (!m_moving)
			return;
		if (ec > 10) {
			spawnEnemy();
			ec = 0;
		}
		ec++;
	}

protected:
	void spawnEnemy() override {
		Enemy* enemy = new BasicEnemy(m_position.x + 3, m_position.y + 20);
		m_env->addEnemy(enemy);
	}

private:
	int ec = 0;
};

#endif /* WAVE_SPAWNER_HPP */