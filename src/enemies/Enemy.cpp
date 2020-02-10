#include "Enemy.hpp"
#include "..\Environment.hpp"
#include "..\mods\Mod.hpp"
#include <iostream>

int Enemy::update() {
	customUpdate();

	m_position.x += m_velocity.x;
	m_position.y += m_velocity.y;

	if (m_position.y >= 420 || m_position.y <= 0 || m_position.x >= 420 || m_position.x <= 10 || m_lifetime <= 0) {
		m_fill = sf::Color::Black;
	}
	else {
		m_fill = m_dfill;
	}
	if (m_position.y >= 430 || m_position.y <= 0 || m_position.x >= 430 || m_position.x <= 0 || m_lifetime <= 0) {
		return 1;
	}

	m_lifetime--;
	return 0;
}

void Enemy::customUpdate() {
	if (modded) {
		sol::protected_function customUpdateFunction = (*(parent->getScriptForSpawner(name, "enemyCustomUpdate")))[name]["enemyUpdate"];
		if (customUpdateFunction.valid()) {
			auto t = customUpdateFunction(this, m_env);
			if (!t.valid()) {
				sol::error err = t;
				std::cout << "Error in enemyUpdate for " << name << ": " << err.what() << std::endl;
				abort();
			}
		}
	}
}

void Enemy::init() {
	m_dfill = m_fill;
}

void Enemy::modinit(Mod* parent, const std::string& name, Environment* env) {
	modded = true;
	this->parent = parent;
	this->name = name;
	m_env = env;

	try {
		sol::optional<sol::table> t = (*parent->getScriptForSpawner(name, "enemy modinit"))[name]["EnemyInstanceVars"];
		if (t.has_value())
			instanceVars = t.value()["new"](t);
	}
	catch (sol::error) {
		std::cout << "Error: function EnemyInstanceVars:new failed for enemy \"" << name << "\"" << std::endl;
		abort();
	}
}

bool Enemy::customRender(sf::RenderWindow& window) {
	if (modded) {
		sol::protected_function customRenderFunction = (*(parent->getScriptForSpawner(name, "enemy custom render")))[name]["enemyRender"];
		if (customRenderFunction.valid()) {
			auto t = customRenderFunction(this, window);
			if (!t.valid()) {
				sol::error err = t;
				std::cout << "Error in enemyRender for " << name << ": " << err.what() << std::endl;
				abort();
			}
			return true;
		}
	}
	return false;
}

void Enemy::render(sf::RenderWindow& window) {
	if (!customRender(window)) {
		sf::RectangleShape shape(sf::Vector2f(m_size.x, m_size.y));
		shape.setPosition(m_position);
		shape.setFillColor(m_fill);
		window.draw(shape);
	}
}
sf::Vector2f& Enemy::getPosition() {
	return m_position;
}

void Enemy::setPosition(sf::Vector2f p) {
	m_position = p;
}

sf::Vector2f& Enemy::getVelocity() {
	return m_velocity;
}

void Enemy::setVelocity(sf::Vector2f v) {
	m_velocity = v;
}

sf::Vector2f& Enemy::getSize() {
	return m_size;
}

void Enemy::setSize(sf::Vector2f s) {
	m_size = s;
}

sf::Color& Enemy::getFill() {
	return m_fill;
}

void Enemy::setFill(sf::Color c) {
	m_fill = c;
	m_dfill = c;
}