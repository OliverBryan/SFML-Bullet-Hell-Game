#include "UserInterface.hpp"
#include <iostream>

UserInterface::UserInterface(Environment* env) : m_env(env) {
	if (!m_font.loadFromFile(".\\Roboto-Medium.ttf")) {
		std::cout << "Error: could not load font from Roboto-Medium.ttf" << std::endl;
	}
	m_timerLabel.setFont(m_font);
	m_waveLabel.setFont(m_font);

	m_timerLabel.setPosition(480, 100);
	m_timerLabel.setFillColor(sf::Color::White);

	m_waveLabel.setPosition(480, 200);
	m_waveLabel.setFillColor(sf::Color::White);
	m_waveLabel.setString("Wave: " + std::to_string(m_env->m_wave));
}

void UserInterface::update() {
	if (m_env->m_timer > 0.0f) {
		m_env->m_timer -= (1.0f / 60.0f);
		m_timerLabel.setString("Time: " + std::to_string(static_cast<int>(std::round(m_env->m_timer))));
	}
	else if (!m_env->preWave) {
		m_env->preWave = true;
		m_env->m_timer = 5.0f;
	}
	else {
		std::cout << "Environment: wave cleared" << std::endl;
		m_env->preWave = false;
		if (m_env->m_wave < m_env->m_waves.size())
			m_env->m_wave++;
		m_waveLabel.setString("Wave: " + std::to_string(m_env->m_wave));
		m_env->m_timer = static_cast<float>(m_env->m_waves[m_env->m_wave - 1].newSpawnerInterval * m_env->m_waves[m_env->m_wave - 1].spawners);
		m_env->addSpawner();
	}
}

void UserInterface::render(sf::RenderWindow& window) {
	sf::RectangleShape shape(sf::Vector2f(400, 400));
	shape.setPosition(sf::Vector2f(20, 20));
	shape.setFillColor(sf::Color::White);
	window.draw(shape);

	window.draw(m_timerLabel);
	window.draw(m_waveLabel);
}