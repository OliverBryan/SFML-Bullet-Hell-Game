#include "Console.hpp"
#include <iostream>

// Constructor
Console::Console(Environment* env) : m_env(env) {}

void Console::run() {
	// Loop while the game is running
	while (m_running) {
		// Get a command as string input from the standard input stream (console window)
		std::string command;
		std::getline(std::cin, command);

		// Parse and execute the command
		interpret(command);
	}
}

void Console::interpret(const std::string& command) {
	// Lock the environment object so that no concurrent access problems can occur
	m.lock();

	// Run the command
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
		// Advances the wave by setting the time remaining in the wave to 1/100th of a second and
		// automatically moving the player to the top of the screen
		m_env->m_timer = 0.01f;
		m_env->getPlayer()->m_position.y = 0;
	}

	// Make sure the game is still running
	m_running = m_env->running;

	// Unlock the mutex so that normal game execution can occur
	m.unlock();
}