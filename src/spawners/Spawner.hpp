#ifndef SPAWNER_HPP
#define SPAWNER_HPP

class Environment;

#include <SFML/Graphics.hpp>
#include <memory>
#include <random>

static int irand(int min, int max) {
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::uniform_int_distribution<> dis{ min, max };

	return dis(gen);
}

class Spawner {
public:
	Spawner(float x, Environment* env);
	virtual ~Spawner() {}

	virtual void update();

	virtual void render(sf::RenderWindow& window) = 0;

	static int FIRE_TIME;

protected:
	int m_newX;
	int m_counter = 0;
	sf::Vector2f m_position;
	Environment* m_env;
	virtual void spawnEnemy() = 0;
};

#endif /* SPAWNER_HPP */