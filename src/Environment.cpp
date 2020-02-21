#include "Spawner.hpp"
#include "Enemy.hpp"
#include "Powerup.hpp"
#include <iostream>
#include "ModLoader.hpp"

Environment::Environment() : m_player(210, 260) {
	m_timer = static_cast<float>(m_waves[0].waveLength);
	m_modLoader = new ModLoader();
	m_modLoader->loadMod("GameData");
	addSpawner();
}

Environment::~Environment() {
	delete m_modLoader;
	delete m_powerup;
}

void Environment::update() {
	m_newSpawnerCounter++;
	if (m_spawners.size() < m_waves[m_wave - 1].spawners && m_newSpawnerCounter >= (m_waves[m_wave - 1].newSpawnerInterval * 60)) {
		addSpawner();
		m_newSpawnerCounter = 0;
	}

	for (Spawner* spawner : m_spawners) {
		spawner->update();
	}

	if (m_powerup != nullptr) {
		int i = m_powerup->update(&m_player);
		if (i == 1) {
			delete m_powerup;
			m_powerup = nullptr;
		}
	}

	m_player.update();

	if (m_powerup != nullptr && m_player.getBounds().intersects(sf::FloatRect(m_powerup->getPosition(), sf::Vector2f(16, 20)))) {
		pickedUpPowerup = true;
		m_player.setPowerup(m_powerup);
		m_powerup = nullptr;
	}

	bool died = false;
	for (int i = 0; i < m_enemies.size(); i++) {
		int ret = m_enemies.at(i)->update();

		if (m_player.getBounds().intersects(m_enemies.at(i)->getBounds()) && !m_player.invincible && m_enemies.at(i)->fatal) {
			died = true;
		}

		if (ret == 1) removeEnemy(i);
	}

	if (died) {
		m_timer = 5.0f;
		preWave = true;
		clearSpawners();
		clearEnemies();
		m_status = Status::PlayerDied;
	}

	if (preWave && m_powerup == nullptr && !pickedUpPowerup && m_status != Status::PlayerDied) {
		std::vector<std::string> choices;
		for (Mod* mod : m_modLoader->getMods()) {
			for (std::string powerup : mod->getPowerups()) {
				choices.push_back(powerup);
			}
		}
		std::string choice = choices[irand(0, choices.size() - 1)];
		m_powerup = m_modLoader->getModByPowerupName(choice)->createPowerup(static_cast<float>(irand(20, 400)), static_cast<float>(irand(20, 400)), choice);
	}

	if (preWave && m_spawners.size() > 0) {
		clearSpawners();
	}
	if (preWave && m_enemies.size() > 0) {
		clearEnemies();
	}
}

void Environment::render(sf::RenderWindow& window) {
	for (Spawner* spawner : m_spawners) {
		spawner->render(window);
	}

	if (m_powerup != nullptr) {
		m_powerup->render(window, &m_player);
	}

	for (Enemy* enemy : m_enemies) {
		enemy->render(window);
	}

	m_player.render(window);

	sf::RectangleShape shape(sf::Vector2f(20, 400));
	shape.setFillColor(sf::Color::Black);
	window.draw(shape);

	shape.setPosition(420, 0);
	shape.setSize(sf::Vector2f(50, 400));
	window.draw(shape);

	shape.setSize(sf::Vector2f(400, 20));
	shape.setPosition(0, 0);
	window.draw(shape);

	shape.setPosition(20, 420);
	window.draw(shape);
}

void Environment::addEnemy(Enemy* enemy) {
	m_enemies.push_back(enemy);
}

void Environment::addModdedEnemy(Enemy enemy, std::string name) {
	enemy.modinit(m_modLoader->getModBySpawnerName(name), name, this);
	m_enemies.push_back(new Enemy(enemy));
}

void Environment::clearEnemies() {
	if (!m_enemies.empty()) {
		for (int i = 0; i < m_enemies.size(); i++) {
			removeEnemy(i);
		}
	}
}

void Environment::clearSpawners() {
	if (!m_spawners.empty()) {
		for (int i = 0; i < m_spawners.size(); i++) {
			removeSpawner(i);
		}
	}
}

void Environment::addSpawner() {
	int spawnerType = irand(0, 99);
	int sum = 0;
	std::string name = "";
	std::vector<std::pair<std::string, int>> spawnerTypes = m_waves[m_wave - 1].spawnerTypes;

	for (std::pair<std::string, int> type : spawnerTypes) {
		sum += type.second;
		if (spawnerType < sum) {
			name = type.first;
			break;
		}
	}

	for (Mod* mod : m_modLoader->getMods()) {
		for (std::string spawner : mod->getSpawners()) {
			if (spawner == name) {
				m_spawners.push_back(mod->createSpawner(static_cast<float>(irand(20, 404)), this, name));
				return;
			}
		}
	}
	abort();
}

void Environment::removeSpawner(int index) {
	Spawner* spawner = m_spawners.at(index);
	m_spawners.erase(m_spawners.begin() + index);
	delete spawner;
}

void Environment::removeEnemy(int index) {
	Enemy* enemy = m_enemies.at(index);
	m_enemies.erase(m_enemies.begin() + index);
	delete enemy;
}

Player* Environment::getPlayer() {
	return &m_player;
}