#include "Powerup.hpp"
#include "Mod.hpp"
#include "Player.hpp"

Powerup::Powerup(float x, float y, sf::Sprite sprite, int activeTime, Mod* parent, std::string name) : 
	m_position(x, y), m_sprite(sprite), activeTime(activeTime), parent(parent), m_name(name), m_counter(activeTime) {}

int Powerup::update(Player* player) {
	if (m_active) {
		m_counter--;
		if (m_counter <= 0) {
			m_active = false;
			deactivate(player);
			return 1;
		}
	}

	sol::protected_function customUpdateFunction = (*(parent->getScriptForPowerup(m_name)))[m_name]["update"];
	if (customUpdateFunction.valid()) {
		auto t = customUpdateFunction(this, player);
		if (!t.valid()) {
			sol::error err = t;
			std::cout << "Error in update for " << m_name << ": " << err.what() << std::endl;
			abort();
		}
	}

	return 0;
}

void Powerup::activate(Player* player) {
	sol::protected_function activateFunction = (*(parent->getScriptForPowerup(m_name)))[m_name]["activate"];
	if (activateFunction.valid()) {
		auto t = activateFunction(this, player);
		if (!t.valid()) {
			sol::error err = t;
			std::cout << "Error in activate for " << m_name << ": " << err.what() << std::endl;
			abort();
		}
	}
}

void Powerup::deactivate(Player* player) {
	sol::protected_function deactivateFunction = (*(parent->getScriptForPowerup(m_name)))[m_name]["deactivate"];
	if (deactivateFunction.valid()) {
		auto t = deactivateFunction(this, player);
		if (!t.valid()) {
			sol::error err = t;
			std::cout << "Error in deactivate for " << m_name << ": " << err.what() << std::endl;
			abort();
		}
	}
}

void Powerup::render(sf::RenderWindow& window, Player* player) {
	if (m_active) {
		sol::protected_function renderFunction = (*(parent->getScriptForPowerup(m_name)))[m_name]["render"];
		if (renderFunction.valid()) {
			auto t = renderFunction(this, player, window);
			if (!t.valid()) {
				sol::error err = t;
				std::cout << "Error in render for " << m_name << ": " << err.what() << std::endl;
				abort();
			}
		}
	}
	else {
		m_sprite.setPosition(m_position);
		window.draw(m_sprite);
	}
}

sf::Vector2f& Powerup::getPosition() {
	return m_position;
}

void Powerup::setPosition(sf::Vector2f p) {
	m_position = p;
}

bool Powerup::getActive() {
	return m_active;
}

void Powerup::setActive(bool a) {
	m_active = a;
}

sf::Sprite Powerup::getSprite() {
	return m_sprite;
}

void Powerup::setSprite(sf::Sprite s) {
	m_sprite = s;
}