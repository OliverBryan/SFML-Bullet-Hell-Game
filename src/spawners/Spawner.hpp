#ifndef SPAWNER_HPP
#define SPAWNER_HPP

#include "..\Environment.hpp"

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

	virtual void spawnerUpdate() {}
	virtual void update();

	virtual void render(sf::RenderWindow& window);

	int FIRE_TIME;
	int POST_MOVE_TIME;

protected:
	int m_newX;
	int m_counter = 0;
	sf::Vector2f m_position;
	Environment* m_env;
	virtual void spawnEnemy() = 0;

	int m_postMoveCounter = 60;
	sf::Color m_fill;
	sf::Color defaultFill;
	sf::Color postMoveFill;
	sf::Color warningMoveFill;
};

#endif /* SPAWNER_HPP */