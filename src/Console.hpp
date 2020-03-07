#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <mutex>
#include "Environment.hpp"

// Class that defines the admin console, which is what the console window is used for at
// runtime. It parses and executes commands inputted by the user to change game state (E.g. Toggling
// player invincibility or advancing waves)
class Console {
public:
	// Constructor
	Console(Environment* env);

	// Meant to be called asynchronously. Loops while the application is running, gets a command as
	// string input from the console window, and passes it to the interpret function to parse and execute
	void run();

private:
	// Used to lock down the environment object, so that the main game does not try to access it
	// while the console is modifying it
	std::mutex m;

	// Keeps track of whether the application is running or not (set by the main game loop)
	bool m_running = true;

	// Pointer to main environment object that allows the console to access the main game state
	Environment* m_env;

	// Function that parses and executes the commands entered
	void interpret(const std::string& command);
};

#endif /* CONSOLE_HPP */