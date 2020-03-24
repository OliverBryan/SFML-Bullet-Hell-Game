#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>
#include <deque>
#include <any>
#include <mutex>
#include <functional>
#include "Environment.hpp"

using Args = std::variant<double, std::string, bool>;

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

	void runCommands();

	// Function that parses and executes the commands entered
	void interpret(const std::string& cmdStr);

private:
	// Used to lock down the environment object, so that the main game does not try to access it
	// while the console is modifying it
	std::mutex m;

	// Keeps track of whether the application is running or not (set by the main game loop)
	bool m_running = true;

	// Pointer to main environment object that allows the console to access the main game state
	Environment* m_env;

	std::deque<std::string> m_queuedCommands;

	enum class Type {
		String,
		Number,
		Boolean
	};

	struct Token {
		Console::Type type;
		Args data;
	};

	struct Command {
		std::string name;
		std::vector<Console::Type> arguments;
		std::function<void(std::vector<Args>)> callback;
	};

	struct CommandGroup {
		std::string name;
		std::vector<Console::Command> subcommands;
	};

	bool toBool(std::string str);
	std::string tokenStr(Token t);
	std::string stringForType(Type t);

	std::vector<CommandGroup> m_registeredCommands;

	void registerCommandGroup(const std::string& name);

	void registerCommand(std::string name, std::string group, std::function<void(std::vector<Args>)> callback, std::vector<Type> params);
};

#endif /* CONSOLE_HPP */