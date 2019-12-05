#ifndef HOMING_SPAWNER_HPP
#define HOMING_SPAWNER_HPP

#include "Spawner.hpp"

class HomingSpawner : public Spawner {
public:
	HomingSpawner(float x, Environment* env) : Spawner(x, env) {
		FIRE_TIME = 400;
		POST_MOVE_TIME = 10;
		defaultFill = sf::Color::Green; //0, 128, 0
		m_fill = sf::Color::Green;
		postMoveFill = sf::Color::Green; //Unused
		warningMoveFill = sf::Color::Green; // Unused
	}
};

#endif /* HOMING_SPAWNER_HPP */