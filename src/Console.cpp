#include "Console.hpp"
#include <iostream>

Console::Console(Environment* env) : m_env(env) {}

void Console::run() {
	while (m_running) {
		std::string command;
		std::getline(std::cin, command);
		interpret(command);
	}
}

void Console::interpret(const std::string& command) {
	m.lock();
	
	if (command == "clear enemies") {
		while (!m_env->m_enemies.empty())
			m_env->clearEnemies();
	}
	else if (command == "clear spawners") {
		while (!m_env->m_spawners.empty())
			m_env->clearSpawners();
	}
	else if (command == "toggle invincible") {
		if (m_env->getPlayer()->invincible)
			m_env->getPlayer()->invincible = false;
		else m_env->getPlayer()->invincible = true;
	}
	else if (command == "advance") {
		m_env->m_timer = 0.01f;
		m_env->getPlayer()->m_position.y = 0;
	}

	m_running = m_env->running;

	m.unlock();
}