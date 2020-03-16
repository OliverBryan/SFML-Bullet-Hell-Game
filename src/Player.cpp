#include "Player.hpp"
#include "Input.hpp"

void Player::update() {
	if (Input::pressed("up")) {
		m_position.y -= m_speed;
	}
	else if (Input::pressed("down")) {
		m_position.y += m_speed;
	}

	if (Input::pressed("left")) {
		m_position.x -= m_speed;
	}
	else if (Input::pressed("right")) {
		m_position.x += m_speed;
	}

	if (Input::pressed("teleport") && !teleportKeyPressed && m_teleports > 0) {
		teleportKeyPressed = true;
		m_teleports--;
		if (Input::pressed("up") && Input::pressed("left")) {
			m_position.x -= 71;
			m_position.y -= 71;
		}
		else if (Input::pressed("up") && Input::pressed("right")) {
			m_position.x += 71;
			m_position.y -= 71;
		}
		else if (Input::pressed("down") && Input::pressed("left")) {
			m_position.x -= 71;
			m_position.y += 71;
		}
		else if (Input::pressed("down") && Input::pressed("right")) {
			m_position.x += 71;
			m_position.y += 71;
		}

		else if (Input::pressed("down")) {
			m_position.y += 100;
		}
		else if (Input::pressed("left")) {
			m_position.x -= 100;
		}
		else if (Input::pressed("up")) {
			m_position.y -= 100;
		}
		else if (Input::pressed("right")) {
			m_position.x += 100;
		}
		else {
			m_teleports++;
		}
	}
	else if (!Input::pressed("teleport"))
		teleportKeyPressed = false;

	if (Input::pressed("powerup") && !powerupKeyPressed) {
		powerupKeyPressed = true;
		if (m_powerup != nullptr) {
			m_powerup->setActive(true);
			m_powerup->activate(this, m_env);
		}
	}
	else if (!Input::pressed("powerup"))
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
		int i = m_powerup->update(this, m_env);
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
	if (m_powerup != nullptr)
		m_powerup->deactivate(this, m_env);
	delete m_powerup;
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