#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

static float FPS = 60.0f;

class Spawner;
class Enemy;
class Mod;
class ModLoader;
class Powerup;

struct Wave;

class Environment : public sf::NonCopyable {
public:
	Environment();
	~Environment();

	void update();
	void render(sf::RenderWindow& window);

	void addEnemy(Enemy* enemy);
	void clearEnemies();
	void clearSpawners();

	void addModdedEnemy(Enemy enemy, std::string name);

	bool running = true;
	bool paused = false;
	friend class UserInterface;
	friend class Console;

	Player* getPlayer();
private:
	enum class Status {
		None,
		WaveCleared,
		PlayerDied
	};

	void addSpawner();
	void removeSpawner(int index);
	void removeEnemy(int index);

	float m_timer;
	bool preWave = false;
	int m_wave = 1;

	Status m_status = Status::None;

	std::vector<Spawner*> m_spawners;
	std::vector<Enemy*> m_enemies;
	int m_newSpawnerCounter = 0;
	Player m_player;

	bool pickedUpPowerup = false;
	Powerup* m_powerup = nullptr;

	ModLoader* m_modLoader;

	std::vector<Wave> m_waves;
};

#endif /* ENVIRONMENT_HPP */