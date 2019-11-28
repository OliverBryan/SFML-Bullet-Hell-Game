#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Spawner.hpp"
#include "Enemy.hpp"
#include "BasicSpawner.hpp"
#include "Player.hpp"

class Environment {
public:
	Environment() : m_player(210, 260) {}
	
	void update();
	void render(sf::RenderWindow& window);

	void addEnemy(Enemy* enemy);
	void clearEnemies();
	void clearSpawners();

	bool running = true;
private:
	void addSpawner();
	void removeSpawner(int index);
	void removeEnemy(int index);

	std::vector<Spawner*> m_spawners;
	std::vector<Enemy*> m_enemies;
	int m_newSpawnerCounter = 0;
	Player m_player;
};

#endif /* ENVIRONMENT_HPP */