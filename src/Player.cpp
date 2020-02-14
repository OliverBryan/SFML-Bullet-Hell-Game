#include "Player.hpp"

void Player::update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_position.y -= m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_position.y += m_speed;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_position.x -= m_speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_position.x += m_speed;
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) && !teleportKeyPressed && m_teleports > 0) {
		teleportKeyPressed = true;
		m_teleports--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			m_position.x -= 71;
			m_position.y -= 71;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			m_position.x += 71;
			m_position.y -= 71;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
			m_position.x -= 71;
			m_position.y += 71;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
			m_position.x += 71;
			m_position.y += 71;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_position.y += 100;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			m_position.x -= 100;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_position.y -= 100;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			m_position.x += 100;
		}
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::M) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
		teleportKeyPressed = false;

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::C) || sf::Keyboard::isKeyPressed(sf::Keyboard::B)) && !powerupKeyPressed) {
		powerupKeyPressed = true;
		if (m_powerup != nullptr) {
			m_powerup->setActive(true);
			m_powerup->activate(this);
		}
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::C) || sf::Keyboard::isKeyPressed(sf::Keyboard::B)))
		powerupKeyPressed = false;

	if (m_position.x >= 400)
		m_position.x = 400;
	if (m_position.x <= 20)
		m_position.x = 20;
	if (m_position.y >= 400)
		m_position.y = 400;
	if (m_position.y <= 20)
		m_position.y = 20;

	if (m_powerup != nullptr) {
		int i = m_powerup->update(this);
		if (i == 1) {
			m_powerup->setActive(false);
			delete m_powerup;
			m_powerup = nullptr;
		}
	}
}

void Player::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(20, 20));
	shape.setPosition(m_position);
	shape.setFillColor(sf::Color(35, 38, 36));

	window.draw(shape);

	if (m_powerup != nullptr && m_powerup->getActive()) {
		m_powerup->render(window, this);
	}
}

void Player::setPowerup(Powerup* powerup) {
	m_powerup = powerup;
}

sf::FloatRect Player::getBounds() {
	return sf::FloatRect(m_position, sf::Vector2f(20, 20));
}

sf::Vector2f& Player::getPosition() {
	return m_position;
}

void Player::setPosition(sf::Vector2f p) {
	m_position = p;
}

int Player::getSpeed() {
	return m_speed;
}

void Player::setSpeed(int speed) {
	m_speed = speed;
}