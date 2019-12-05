#include "Environment.hpp"
#include "spawners\Spawner.hpp"
#include "enemies\Enemy.hpp"
#include "spawners\BasicSpawner.hpp"
#include "spawners\LaserSpawner.hpp"
#include <iostream>

void Environment::update() {
	m_newSpawnerCounter++;
	if (m_spawners.size() < m_waves[m_wave - 1].spawners && m_newSpawnerCounter >= (m_waves[m_wave - 1].newSpawnerInterval * 60)) {
		addSpawner();
		m_newSpawnerCounter = 0;
	}

	for (Spawner* spawner : m_spawners) {
		spawner->update();
	}

	for (int i = 0; i < m_enemies.size(); i++) {
		int ret = m_enemies.at(i)->update();

		if (m_player.getBounds().intersects(m_enemies.at(i)->getBounds()) && !m_player.invincible) {
			//TODO: polish death
			running = false;
			return;
		}

		if (ret == 1) removeEnemy(i);
	}

	m_player.update();

	if (preWave && m_spawners.size() > 0) {
		clearSpawners();
	}
}

void Environment::render(sf::RenderWindow& window) {
	for (Spawner* spawner : m_spawners) {
		spawner->render(window);
	}

	for (Enemy* enemy : m_enemies) {
		enemy->render(window);
	}

	m_player.render(window);
}

void Environment::addEnemy(Enemy* enemy) {
	m_enemies.push_back(enemy);
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
	int spawnerType = irand(0, 100);
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

	if (name == "basic")
		m_spawners.push_back(new BasicSpawner(static_cast<float>(irand(20, 404)), this));
	else if (name == "laser")
		m_spawners.push_back(new LaserSpawner(static_cast<float>(irand(20, 404)), this));
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