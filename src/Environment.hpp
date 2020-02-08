#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Wave.hpp"


#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

static float FPS = 60.0f;

class Spawner;
class Enemy;
class Mod;
class ModLoader;

class Environment : public sf::NonCopyable {
public:
	Environment();
	~Environment();
	
	void update();
	void render(sf::RenderWindow& window);

	void addEnemy(Enemy* enemy);
	void clearEnemies();
	void clearSpawners();

	bool running = true;
	bool paused = false;
	friend class UserInterface;
	friend class Console;
	friend class Bot;

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

	ModLoader* m_modLoader;

	std::vector<Wave> m_waves = loadWaves();
};

#endif /* ENVIRONMENT_HPP */