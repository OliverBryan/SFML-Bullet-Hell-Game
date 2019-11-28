#ifndef BASIC_SPAWNER_HPP
#define BASIC_SPAWNER_HPP

#include "Spawner.hpp"

class BasicSpawner : public Spawner {
public:
	BasicSpawner(float x, Environment* env) : Spawner(x, env) {}

	void render(sf::RenderWindow& window) override;
protected:
	void spawnEnemy() override;
};

#endif /* BASIC_SPAWNER_HPP */