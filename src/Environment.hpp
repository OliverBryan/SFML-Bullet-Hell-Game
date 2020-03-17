#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"

class Spawner;
class Enemy;
class Mod;
class ModLoader;
class Powerup;

struct Wave;

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

// Class that defines the game environment, which controls the behavior for the entire game, such as
// updating and rendering spawners and enemies.
class Environment : public sf::NonCopyable {
public:
	// Constructor and destructor
	Environment();
	~Environment();

	// Updates the game environment, which in turn updates all spawners and enemies, as well as the player
	void update();
	// Renders the game environment, including all spawners, enemies, and the player
	void render(sf::RenderWindow& window);

	// Registers an enemy with the game environment
	void addEnemy(Enemy* enemy);
	// Unregisters and deletes all enemy objects that are currently active
	void clearEnemies();
	// Unregisters and deletes all spawner objects that are currently active
	void clearSpawners();
	// Registers a modded enemy with the game environment. Same as calling addEnemy, but supplies an
	// additional parameter representing the enemy name to distinguish between mods
	void addModdedEnemy(Enemy enemy, std::string name);

	// Variables that represent the current state of the game
	bool running = true;
	bool paused = false;

	// Value that defines the amount of logic updates per second
	float TPS = 60.0f;

	friend class UserInterface;
	friend class Console;

	// Returns a pointer to the game's player instance
	Player* getPlayer();
private:
	// Internal table representing the configurations loaded from config.lua
	sol::state m_config;

	// Internal enumeration to represent the current state of the player, with None being inactive
	// WaveCleared representing a passed wave, and PlayerDied representing a death event
	enum class Status {
		None,
		WaveCleared,
		PlayerDied
	};

	void pushRect(const sf::RectangleShape& rect, std::vector<sf::Vertex>& va);

	// Internal helper to load the config flie and set game values
	void loadConfig();

	// Registers a spawner with the game environment
	void addSpawner();
	// Removes and deletes a spawner object from the game's internal spawner container
	void removeSpawner(int index);
	// Removes and deletes an enemy object from the game's internal spawner container
	void removeEnemy(int index);

	// Represents the time left in the wave in seconds
	float m_timer;
	// Variable representing the game's wave state. True if the game is currently between waves,
	// false otherwise
	bool preWave = false;
	// Represents the current wave
	int m_wave = 1;

	int m_spawnedSpawners = 1;

	int teleportRechargeTime = 300;

	// Represents the game's player state. If the game is not between waves value is Status::None.
	// If the game is between waves and the player did not die during the wave the value is
	// Status::WaveCleared, otherwise value is Status::PlayerDied.
	Status m_status = Status::None;

	// The game's internal storage of spawner objects
	std::vector<Spawner*> m_spawners;
	// The game's internal storage of enemy objects
	std::vector<Enemy*> m_enemies;
	// Counter representing the amount of time passed since the last spawner was created
	int m_newSpawnerCounter = 0;
	// The game's player object
	Player m_player;

	// Represents the player's powerup state. True if the player is currently holding a powerup,
	// otherwise false
	bool pickedUpPowerup = false;
	// Pointer to the environment's powerup object. Only valid to access the powerup if it has not
	// been picked up by the player. Nullptr if the player has picked up the powerup.
	Powerup* m_powerup = nullptr;

	// Pointer to the game's ModLoader object, which is used to access and manage mods
	ModLoader* m_modLoader;

	// Represents the game's internal container of wave objects
	std::vector<Wave> m_waves;
};

#endif /* ENVIRONMENT_HPP */