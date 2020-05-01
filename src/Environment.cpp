#include "Spawner.hpp"
#include "Enemy.hpp"
#include "Powerup.hpp"
#include <iostream>
#include "ModLoader.hpp"
#include "Wave.hpp"
#include "Input.hpp"

// Initialize player at the center of the game space
Environment::Environment() : m_player(210, 260, this) {
	// Initialize modloader
	m_modLoader = new ModLoader();
	// Load the core game data
	m_modLoader->loadMod("GameData");
	// Initialize the waves object with procedurally generated waves
	m_waves = newLoadWaves(m_modLoader);
	// Load the configuration file
	loadConfig();
	// Set the value of the timer to the length of the first wave
	m_timer = static_cast<float>(m_waves[0].waveLength);
	// Add the first spawner
	addSpawner();
}

Environment::~Environment() {
	// Delete the modloader and powerup object, if it is not nullptr
	delete m_modLoader;
	delete m_powerup;
}

void Environment::loadConfig() {
	// Open important sol libraries
	m_config.open_libraries(sol::lib::base);
	m_config.open_libraries(sol::lib::math);
	Input::registerKeys(m_config);

	m_config.script_file("config.lua");

	// Set game values
	TPS = m_config["config"]["tps"].get_or(60.0f);
	m_player.invincible = m_config["config"]["invincible"].get_or(false);
	cheatsEnabled = m_config["config"]["cheats"].get_or(false);

	Input::init(m_config);
}

void Environment::update() {
	// Increment the new spawner counter
	m_newSpawnerCounter++;
	// If the new spawner counter is greater than the current wave's new spawner interval and the
	// current amount of spawners is less than the current wave's max amount of spawners, then add a
	// new spawner and reset the spawner counter
	if (m_spawnedSpawners < m_waves[m_wave - 1].spawners && m_newSpawnerCounter >= (m_waves[m_wave - 1].newSpawnerInterval * 60)) {
		addSpawner();
		m_spawnedSpawners++;
		m_newSpawnerCounter = 0;
	}

	// Iterate through all of the game's spawner objects, and update them
	for (Spawner* spawner : m_spawners) {
		spawner->update();
	}

	// If the environment has an active powerup object, update it
	if (m_powerup != nullptr) {
		int i = m_powerup->update(&m_player, this);
		// If the powerup's activation time is over, delete it
		if (i == 1) {
			delete m_powerup;
			m_powerup = nullptr;
		}
	}

	// Update the player
	m_player.update();

	// If the environment has a powerup that has not been picked up, and it is colliding with the
	// player, pick it up and transfer ownership of the powerup object to the player
	if (m_powerup != nullptr && m_player.getBounds().intersects(sf::FloatRect(m_powerup->getPosition(), sf::Vector2f(16, 20)))) {
		pickedUpPowerup = true;
		if (m_powerup != nullptr)
			m_player.setPowerup(m_powerup);
		m_powerup = nullptr;
	}

	// Iterate through the game's enemy objects
	bool died = false;
	for (int i = 0; i < m_enemies.size(); i++) {
		// Update each enemy
		int ret = m_enemies.at(i)->update();

		// If the player is colliding with the enemy and the enemy is fatal, kill the player
		if (m_player.getBounds().intersects(m_enemies.at(i)->getBounds()) && !m_player.invincible && m_enemies.at(i)->fatal) {
			died = true;
		}

		// If the enemy's lifetime is over, delete it
		if (ret == 1) removeEnemy(i);
	}

	// If the player died, set the player state to Status::PlayerDied and reset the wave
	if (died) {
		m_timer = 5.0f;
		preWave = true;
		clearSpawners();
		clearEnemies();
		m_status = Status::PlayerDied;
	}

	// If the player has just finished a wave without dying, spawn a random powerup
	if (preWave && m_powerup == nullptr && !pickedUpPowerup && m_status != Status::PlayerDied) {
		// Get available powerup choices from mods
		std::vector<std::string> choices;
		for (Mod* mod : m_modLoader->getMods()) {
			for (std::string powerup : mod->getPowerups()) {
				choices.push_back(powerup);
			}
		}

		// Choose a random powerup
		std::string choice = choices[irand(0, choices.size() - 1)];
		// Create the powerup object
		m_powerup = m_modLoader->getModByPowerupName(choice)->createPowerup(static_cast<float>(irand(20, 400)), static_cast<float>(irand(20, 400)), choice);
	}

	// If the game is between waves and there are still enemies or spawners left, delete them
	if (preWave && m_spawners.size() > 0) {
		clearSpawners();
	}
	if (preWave && m_enemies.size() > 0) {
		clearEnemies();
	}
}

inline void Environment::pushRect(const sf::RectangleShape& rect, std::vector<sf::Vertex>& va) {
	int x = 3;
	for (int i = 0; i < 4; i++) {
		va.push_back(sf::Vertex(sf::Vector2f(rect.getPosition() + rect.getPoint(x)), rect.getFillColor()));
		x++;
		if (x > 3) x = 0;
	}
}

void Environment::render(sf::RenderWindow& window) {
	std::vector<sf::Vertex> vertexArray;
	vertexArray.reserve((m_spawners.size() * 4) + (m_enemies.size() * 4) + 16);

	// Iterate through the game's spawner objects, and render each one
	for (Spawner* spawner : m_spawners) {
		sf::RectangleShape rs = spawner->render(window);
		if (rs.getSize() != sf::Vector2f(0, 0))
			pushRect(rs, vertexArray);
	}

	// If the environment has a powerup that has not been picked up by the player, render it
	if (m_powerup != nullptr) {
		m_powerup->render(window, &m_player);
	}

	// Iterate through the game's enemy objects, and render each one
	for (Enemy* enemy : m_enemies) {
		sf::RectangleShape rs = enemy->render(window);
		if (rs.getSize() != sf::Vector2f(0, 0))
			pushRect(rs, vertexArray);
	}

	// Render the player
	m_player.render(window);

	// Draw the borders around the canvas, so that enemies transition off screen smoothly
	sf::RectangleShape shape(sf::Vector2f(20, 400));
	shape.setFillColor(sf::Color::Black);
	pushRect(shape, vertexArray);

	shape.setPosition(420, 0);
	shape.setSize(sf::Vector2f(50, 400));
	pushRect(shape, vertexArray);

	shape.setSize(sf::Vector2f(400, 20));
	shape.setPosition(0, 0);
	pushRect(shape, vertexArray);

	shape.setPosition(20, 420);
	pushRect(shape, vertexArray);

	window.draw(&vertexArray[0], vertexArray.size(), sf::Quads);
}

void Environment::addEnemy(Enemy* enemy) {
	// Append the passed enemy object to the internal enemy storage
	m_enemies.push_back(enemy);
}

void Environment::addModdedEnemy(Enemy enemy, std::string name) {
	// Initialize the enemy with its mod information
	enemy.modinit(m_modLoader->getModBySpawnerName(name), name, this);
	// Append a copy of the enemy object to the internal enemy storage
	m_enemies.push_back(new Enemy(enemy));
}

void Environment::removeModdedEnemy(Enemy* enemy) {
	auto it = std::find(m_enemies.begin(), m_enemies.end(), enemy);
	int index = std::distance(m_enemies.begin(), it);
	removeEnemy(index);
}

void Environment::clearEnemies() {
	// If there are enemies left, iterate through the internal enemy storage, and delete each enemy
	if (!m_enemies.empty()) {
		for (int i = 0; i < m_enemies.size(); i++) {
			if (m_enemies[i]->stay)
				continue;
			removeEnemy(i);
		}
	}
}

void Environment::clearSpawners() {
	// If there are enemies left, iterate through the internal enemy storage, and delete each enemy
	if (!m_spawners.empty()) {
		for (int i = 0; i < m_spawners.size(); i++) {
			removeSpawner(i);
		}
	}
}

void Environment::addSpawner() {
	// Get the initial spawner type value, and set the sum to 0
	int spawnerType = irand(0, 99);
	int sum = 0;
	// Initialize the name to a null string, and retrieve the spawner types vector from the wave
	std::string name = "";
	std::vector<std::pair<std::string, int>> spawnerTypes = m_waves[m_wave - 1].spawnerTypes;

	// Iterate through every type in the vector
	for (std::pair<std::string, int> type : spawnerTypes) {
		// Add the spawner weight to the sum
		sum += type.second;
		// If the if the spawnerType is less than the sum, pick that spawner and break out of the loop
		if (spawnerType < sum) {
			name = type.first;
			break;
		}
	}

	// Iterate through all the loaded mods and their exported spawners
	for (Mod* mod : m_modLoader->getMods()) {
		for (std::string spawner : mod->getSpawners()) {
			// If the spawner matches the picked spawner, create the spawner and append it to the
			// games internal spawner storage
			if (spawner == name) {
				m_spawners.push_back(mod->createSpawner(static_cast<float>(irand(20, 404)), this, name));
				return;
			}
		}
	}

	// If execution reaches this point, that means no mod was found that exported the picked spawner,
	// which means that a fatal error has occurred and the application must terminate
	abort();
}

void Environment::removeSpawner(int index) {
	// Retrieve the spawner object from the spawners vector
	Spawner* spawner = m_spawners.at(index);
	// Remove the object from the vector
	m_spawners.erase(m_spawners.begin() + index);
	// Delete the object
	delete spawner;
}

void Environment::removeEnemy(int index) {
	// Retrieve the enemy object from the enemies vector
	Enemy* enemy = m_enemies.at(index);
	// Remove the object from the vector
	m_enemies.erase(m_enemies.begin() + index);
	// Delete the object
	delete enemy;
}

Player* Environment::getPlayer() {
	// Return a pointer to the game's player object
	return &m_player;
}