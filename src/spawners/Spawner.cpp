#include "Spawner.hpp"
#include "..\enemies\Enemy.hpp"
#include <iostream>
#include "..\mods\Mod.hpp"

Spawner::Spawner(float x, Environment* env) : 
m_position(x, 20), m_env(env) {
	m_newX = irand(20, 404);
}

Spawner::Spawner(float x, Environment* env, int firetime, int postmovetime, sf::Color fill, sf::Color postmovefill, sf::Color warningfirefill, bool modded, Mod* parent, std::string name) :
m_position(x, 20), m_env(env), FIRE_TIME(firetime), POST_MOVE_TIME(postmovetime),
m_fill(fill), postMoveFill(postmovefill), warningMoveFill(warningfirefill), 
modded(modded), parent(parent), m_name(name) {
	m_newX = irand(20, 404);
	defaultFill = m_fill;
	m_postMoveCounter = POST_MOVE_TIME;

	try {
		sol::optional<sol::table> t = (*parent->getScriptForSpawner(name))[name]["SpawnerInstanceVars"];
		if (t.has_value())
			instanceVars = t.value()["new"](t);
	}
	catch (sol::error) {
		std::cout << "Error: function SpawnerInstanceVars:new failed for spawner \"" << m_name << "\"" << std::endl;
		abort();
	}
}

void Spawner::spawnEnemy() {
	if (!modded) {
		std::cout << "Fatal Error: cannot call base spawnEnemy() on a non modded spawner" << std::endl;
		abort();
	}

	try {
		sol::function spawnerFunction = (*(parent->getScriptForSpawner(m_name)))[m_name]["spawnEnemies"];
		sol::table table = spawnerFunction(this);
		int amount = table["amount"];
		sol::table enemies = table["enemies"];
		for (int i = 1; i <= amount; i++) {
			Enemy e = enemies[i];
			e.modinit(parent, m_name, m_env);
			m_env->addEnemy(new Enemy(e));
		}
	}
	catch (sol::error) {
		std::cout << "Error: function spawnEnemies failed for spawner \"" << m_name << "\"" << std::endl;
		abort();
	}
}

void Spawner::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(16, 20));
	shape.setPosition(m_position);
	shape.setFillColor(m_fill);
	window.draw(shape);
}

void Spawner::spawnerUpdate() {
	if (modded) {
		sol::protected_function spawnerUpdateFunction = (*(parent->getScriptForSpawner(m_name)))[m_name]["spawnerUpdate"];
		if (spawnerUpdateFunction.valid()) {
			auto t = spawnerUpdateFunction(this, m_env);
			if (!t.valid()) {
				sol::error err = t;
				std::cout << "Error in spawnerUpdate for " << m_name << ": " << err.what() << std::endl;
			}
		}
	}
}

void Spawner::update() {
	spawnerUpdate();

	m_counter++;
	if (m_counter >= FIRE_TIME && m_position.x != m_newX && m_position.x != m_newX + 1) {
		m_newX >= m_position.x ? m_position.x += 2 : m_position.x -= 2;
		m_moving = true;
	}
	else if ((m_position.x == m_newX || m_position.x == m_newX + 1) && m_postMoveCounter > 0) {
		m_postMoveCounter--;
		m_fill = postMoveFill;
	}
	else if (m_counter >= FIRE_TIME && m_postMoveCounter <= 0) {
		if (modded)
			spawnEnemy();
		else spawnEnemy();
		m_counter = 0;
		m_newX = irand(20, 404);
		m_fill = defaultFill;
		m_postMoveCounter = POST_MOVE_TIME;
		m_moving = false;
	}
	
	if (m_counter > FIRE_TIME - 60 && !m_moving) {
		m_fill = warningMoveFill;
	}
}

bool Spawner::getMoving() {
	return m_moving;
}

void Spawner::setMoving(bool m) {
	m_moving = m;
}

sf::Vector2f Spawner::getPosition() {
	return m_position;
}

void Spawner::setPosition(sf::Vector2f p) {
	m_position = p;
}