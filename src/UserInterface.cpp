#include "UserInterface.hpp"
#include <iostream>
#include "Mod.hpp"

UserInterface::UserInterface(Environment* env) : m_env(env) {
	if (!m_font.loadFromFile(".\\Roboto-Medium.ttf")) {
		std::cout << "Error: could not load font from Roboto-Medium.ttf" << std::endl;
	}
	m_timerLabel.setFont(m_font);
	m_waveLabel.setFont(m_font);
	m_statusLabel.setFont(m_font);

	m_timerLabel.setPosition(480, 80);
	m_timerLabel.setFillColor(sf::Color::White);

	m_waveLabel.setPosition(480, 160);
	m_waveLabel.setFillColor(sf::Color::White);
	m_waveLabel.setString("Wave: " + std::to_string(m_env->m_wave));

	m_statusLabel.setPosition(480, 300);
	m_statusLabel.setFillColor(sf::Color::White);
	m_statusLabel.setString("");

	sf::RectangleShape shape(sf::Vector2f(20, 20));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(480, 240);
	m_ts.push_back(shape);

	shape.setPosition(520, 240);
	m_ts.push_back(shape);

	shape.setPosition(560, 240);
	m_ts.push_back(shape);

	m_env->m_timer = static_cast<float>(m_env->m_waves[m_env->m_wave - 1].waveLength);
}

void UserInterface::update() {
	m_waveLabel.setString("Wave: " + std::to_string(m_env->m_wave));
	if (m_env->m_timer > 0.0f) {
		m_env->m_timer -= (1.0f / 60.0f);
		m_timerLabel.setString("Time: " + std::to_string(static_cast<int>(std::round(m_env->m_timer))));
	}
	else if (!m_env->preWave && m_env->getPlayer()->getBounds().top <= 20) {
		m_env->m_status = Environment::Status::WaveCleared;
		m_env->preWave = true;
		m_env->m_timer = 5.0f;
	}
	else if (m_env->preWave) {
		m_env->preWave = false;
		m_env->pickedUpPowerup = false;
		if (m_env->m_powerup != nullptr) {
			delete m_env->m_powerup;
			m_env->m_powerup = nullptr;
		}
		if (m_env->m_wave < m_env->m_waves.size() && m_env->m_status != Environment::Status::PlayerDied)
			m_env->m_wave++;
		m_env->m_timer = static_cast<float>(m_env->m_waves[m_env->m_wave - 1].waveLength);
		m_env->addSpawner();
		m_env->m_status = Environment::Status::None;
	}

	if (m_env->getPlayer()->m_teleports < 3)
		m_teleportRechargeCounter++;
	if (m_teleportRechargeCounter > m_teleportRecharge) {
		m_env->getPlayer()->m_teleports++;
		m_teleportRechargeCounter = 0;
	}

	int ts = m_env->getPlayer()->m_teleports;
	switch (ts) {
	case 0:
		m_ts[2].setFillColor(sf::Color::Black);
		m_ts[1].setFillColor(sf::Color::Black);
		m_ts[0].setFillColor(sf::Color::Black);
		break;
	case 1:
		m_ts[2].setFillColor(sf::Color::Black);
		m_ts[1].setFillColor(sf::Color::Black);
		m_ts[0].setFillColor(sf::Color::White);
		break;
	case 2:
		m_ts[2].setFillColor(sf::Color::Black);
		m_ts[1].setFillColor(sf::Color::White);
		m_ts[0].setFillColor(sf::Color::White);
		break;
	case 3:
		m_ts[2].setFillColor(sf::Color::White);
		m_ts[1].setFillColor(sf::Color::White);
		m_ts[0].setFillColor(sf::Color::White);
		break;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !pKeyDown) {
		pKeyDown = true;
		m_env->paused = true;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		pKeyDown = false;

	handleKeyBinds();

	switch (m_env->m_status) {
	case Environment::Status::PlayerDied:
		m_statusLabel.setString("You Died");
		break;
	case Environment::Status::WaveCleared:
		m_statusLabel.setString("Wave Cleared");
		break;
	case Environment::Status::None:
		m_statusLabel.setString("");
		break;
	}

	if (m_env->m_player.m_powerup != nullptr && !m_env->m_player.m_powerup->getActive()) {
		m_env->m_player.m_powerup->updateSprite();
	}
}

void UserInterface::pauseUpdate() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !pKeyDown) {
		pKeyDown = true;
		m_env->paused *= false;
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		pKeyDown = false;
}

void UserInterface::render(sf::RenderWindow& window) {
	if (m_env->m_player.m_powerup != nullptr && !m_env->m_player.m_powerup->getActive()) {
		sf::Color bfill = (*m_env->m_player.m_powerup->parent->getScriptForPowerup(m_env->m_player.m_powerup->m_name))[m_env->m_player.m_powerup->m_name]["background"].get_or(sf::Color(0, 0, 0));
		sf::RectangleShape rs(sf::Vector2f(30, 30));
		rs.setPosition(613, 235);
		rs.setFillColor(sf::Color::White);
		window.draw(rs);

		sf::Sprite powerupSprite = m_env->m_player.m_powerup->getSprite();
		powerupSprite.setPosition(620, 240);
		window.draw(powerupSprite);
	}
	

	sf::RectangleShape shape(sf::Vector2f(400, 400));
	shape.setPosition(sf::Vector2f(20, 20));
	shape.setFillColor(sf::Color::White);
	window.draw(shape);

	for (sf::RectangleShape rs : m_ts) {
		window.draw(rs);
	}

	window.draw(m_timerLabel);
	window.draw(m_waveLabel);
	window.draw(m_statusLabel);
}

void UserInterface::handleKeyBinds() {
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && !advKeyDown) {
		advKeyDown = true;
		m_env->m_timer = 0.01f;
		m_env->getPlayer()->m_position.y = 0;
	}
	else if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))))
		advKeyDown = false;
}