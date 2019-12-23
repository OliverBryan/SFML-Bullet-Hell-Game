#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Wave.hpp"

class Spawner;
class Enemy;

class Environment {
public:
	Environment();
	
	void update();
	void render(sf::RenderWindow& window);

	void addEnemy(Enemy* enemy);
	void clearEnemies();
	void clearSpawners();

	bool running = true;
	friend class UserInterface;

	Player* getPlayer();
private:
	void addSpawner();
	void removeSpawner(int index);
	void removeEnemy(int index);

	float m_timer;
	bool preWave = false;
	int m_wave = 1;

	std::vector<Spawner*> m_spawners;
	std::vector<Enemy*> m_enemies;
	int m_newSpawnerCounter = 0;
	Player m_player;

	std::vector<Wave> m_waves = loadWaves();
};

#endif /* ENVIRONMENT_HPP */