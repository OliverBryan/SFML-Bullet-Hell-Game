#ifndef SHOTGUN_SPAWNER_HPP
#define SHOTGUN_SPAWNER_HPP

#include "Spawner.hpp"
#include "..\enemies\Enemy.hpp"

class ShotgunSpawner : public Spawner {
public:
	ShotgunSpawner(float x, Environment* env) : Spawner(x, env) {
		FIRE_TIME = 30;
		POST_MOVE_TIME = 0;
		defaultFill = sf::Color(128, 0, 128);
		m_fill = sf::Color(128, 0, 128);
		postMoveFill = sf::Color(128, 0, 128); //Unused
		warningMoveFill = sf::Color(128, 0, 128); //Unused
	}
protected:
	void spawnEnemy() override {
		Enemy* middleEnemy = new Enemy(m_position.x + 3, m_position.y + 20, 0.0f, 3.5f, 300, sf::Color(128, 0, 128));
		m_env->addEnemy(middleEnemy);
		
		Enemy* leftEnemy = new Enemy(m_position.x + 3, m_position.y + 20, 1.0f, 3.0f, 300, sf::Color(128, 0, 128));
		m_env->addEnemy(leftEnemy);

		Enemy* rightEnemy = new Enemy(m_position.x + 3, m_position.y + 20, -1.0f, 3.0f, 300, sf::Color(128, 0, 128));
		m_env->addEnemy(rightEnemy);
	}
};


#endif /* SHOTGUN_SPAWNER_HPP */