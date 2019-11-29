#ifndef LASER_SPAWNER_HPP
#define LASER_SPAWNER_HPP

#include "Spawner.hpp"

class LaserSpawner : public Spawner {
public:
	LaserSpawner(float x, Environment* env) : Spawner(x, env) { FIRE_TIME = 300; }

	void update() override;
	void render(sf::RenderWindow& window) override;

protected:
	void spawnEnemy() override;

private:
	bool m_inPostMove = false;
	int m_postMoveCounter = 60;
};

#endif /* LASER_SPAWNER_HPP */