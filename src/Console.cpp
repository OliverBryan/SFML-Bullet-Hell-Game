#include "Console.hpp"
#include <iostream>
#include <iterator>
#include <sstream>
#include <algorithm>
#include "ModLoader.hpp"
#include "Mod.hpp"
#include "Spawner.hpp"
#include "Wave.hpp"

// Constructor
Console::Console(Environment* env) : m_env(env) {
	// Register commands
	registerCommandGroup("set");
	registerCommand("invincible", "set", [this](std::vector<Args> args) {
		m_env->getPlayer()->invincible = std::get<bool>(args[0]);
	}, { Type::Boolean });

	registerCommand("teleports", "set", [this](std::vector<Args> args) {
		int t = static_cast<int>(std::get<double>(args[0]));
		if (t < 0 || t > 3) throw std::invalid_argument("Amount of teleports must be between 0 and 3");
		m_env->getPlayer()->m_teleports = static_cast<int>(std::get<double>(args[0]));
	}, { Type::Number });

	registerCommand("position", "set", [this](std::vector<Args> args) {
		float px = static_cast<float>(std::get<double>(args[0])), py = static_cast<float>(std::get<double>(args[1]));
		if (px < 0.0f || px > 400.0f || py < 0.0f || py > 400.0f) throw std::invalid_argument("Player position must be between 0 and 400");
		m_env->getPlayer()->m_position = sf::Vector2f(px, py);
	}, {Type::Number, Type::Number});

	registerCommand("powerup", "set", [this](std::vector<Args> args) {
		Mod* mod = m_env->m_modLoader->getModByPowerupName(std::get<std::string>(args[0]));
		if (mod == nullptr) throw std::invalid_argument("\"" + std::get<std::string>(args[0]) + "\" is not a valid powerup name");
		m_env->getPlayer()->setPowerup(mod->createPowerup(static_cast<float>(irand(20, 400)), static_cast<float>(irand(20, 400)), std::get<std::string>(args[0])));
	}, { Type::String });

	registerCommand("speed", "set", [this](std::vector<Args> args) {
		int s = static_cast<int>(std::get<double>(args[0]));
		if (s < 1) throw std::invalid_argument("Speed must be above 0");
		m_env->getPlayer()->m_speed = s;
	}, { Type::Number });

	registerCommand("tps", "set", [this](std::vector<Args> args) {
		float tps = static_cast<float>(std::get<double>(args[0]));
		if (tps < 1.0f) throw std::invalid_argument("TPS must be above 1");
		m_env->TPS = tps;
	}, { Type::Number });

	registerCommand("paused", "set", [this](std::vector<Args> args) {
		m_env->paused = std::get<bool>(args[0]);
	}, { Type::Boolean });

	registerCommand("running", "set", [this](std::vector<Args> args) {
		m_env->running = std::get<bool>(args[0]);
	}, { Type::Boolean });

	registerCommand("time", "set", [this](std::vector<Args> args) {
		float time = static_cast<float>(std::get<double>(args[0]));
		if (time < 0 || time > static_cast<double>(m_env->m_waves[m_env->m_wave].waveLength)) throw std::invalid_argument("Time must be between 0 and wave length");
		m_env->m_timer = time;
	}, { Type::Number });

	registerCommand("wave", "set", [this] (std::vector<Args> args) {
		int wave = static_cast<int>(std::get<double>(args[0]));
		if (wave < 1 || wave > 100) throw std::invalid_argument("Wave must be between 0 and 100");
		interpret("clear spawners");
		interpret("clear enemies");
		m_env->preWave = false;
		m_env->pickedUpPowerup = false;
		if (m_env->m_powerup != nullptr) {
			delete m_env->m_powerup;
			m_env->m_powerup = nullptr;
		}
		m_env->m_wave = wave;
		m_env->m_timer = static_cast<float>(m_env->m_waves[m_env->m_wave - 1].waveLength);
		m_env->addSpawner();
		m_env->m_newSpawnerCounter = 0;
		m_env->m_spawnedSpawners = 1;
		m_env->m_status = Environment::Status::None;
	}, { Type::Number });

	registerCommand("teleport_recharge", "set", [this](std::vector<Args> args) {
		int tpr = static_cast<int>(std::get<double>(args[0]));
		if (time < 0) throw std::invalid_argument("Teleport recharge must be greater than 0");
		m_env->teleportRechargeTime = tpr * 60;
	}, { Type::Number });

	registerCommandGroup("clear");

	registerCommand("spawners", "clear", [this](std::vector<Args> args) {
		while (!m_env->m_spawners.empty()) {
			m_env->clearSpawners();
		}
	}, {});

	registerCommand("enemies", "clear", [this](std::vector<Args> args) {
		while (!m_env->m_enemies.empty()) {
			m_env->clearEnemies();
		}
	}, {});
}

void Console::run() {
	// Loop while the game is running
	while (m_running) {
		std::cout << ">";
		// Get a command as string input from the standard input stream (console window)
		std::string command;
		std::getline(std::cin, command);

		// Parse and execute the command
		m.lock();
		m_queuedCommands.push_back(command);
		m.unlock();
	}
}

bool Console::toBool(std::string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::istringstream is(str);
	bool b;
	is >> std::boolalpha >> b;
	if (is.fail()) throw std::invalid_argument("\"" + str + "\" is not a valid boolean literal");
	return b;
}

std::string Console::tokenStr(Token t) {
	switch (t.type) {
	case Type::Boolean:
		return std::to_string(std::get<bool>(t.data));
	case Type::Number:
		return std::to_string(std::get<double>(t.data));
	case Type::String:
		return std::get<std::string>(t.data);
	}
	// Not possible
	return "null";
}

std::string Console::stringForType(Type t) {
	switch (t) {
	case Type::Boolean:
		return "Boolean";
	case Type::Number:
		return "Number";
	case Type::String:
		return "String";
	}
	// Not possible
	return "null";
}

void Console::runCommands() {
	while (!m_queuedCommands.empty()) {
		std::string command = m_queuedCommands[0];
		m_queuedCommands.pop_front();
		interpret(command);
	}
}

void Console::interpret(const std::string& cmdStr) {
	if (cmdStr.empty()) return;

	std::vector<std::string> stokens;
	std::istringstream iss(cmdStr);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(stokens));

	std::vector<Token> tokens;
	for (std::string stoken : stokens) {
		Token token;
		try {
			double num = std::stod(stoken);
			token.data = num;
			token.type = Type::Number;
		}
		catch (std::invalid_argument) {
			try {
				bool b = toBool(stoken);
				token.data = b;
				token.type = Type::Boolean;
			}
			catch (std::invalid_argument) {
				token.data = stoken;
				token.type = Type::String;
			}
		}
		tokens.push_back(token);
	}

	if (tokens.size() < 2) {
		std::cout << "Error: must provide a subcommand" << std::endl;
		return;
	}

	if (tokens[0].type != Type::String || tokens[1].type != Type::String) {
		std::cout << "Error: first and second token must be of type \"String\"" << std::endl;
		return;
	}

	CommandGroup group; group.name = "null";
	for (CommandGroup cg : m_registeredCommands) {
		if (cg.name == std::get<std::string>(tokens[0].data)) {
			group = cg;
		}
	}
	if (group.name == "null") {
		std::cout << "Error: invalid command group \"" << std::get<std::string>(tokens[0].data) << "\"" << std::endl;
		return;
	}

	Command command; command.name = "null";
	for (Command c : group.subcommands) {
		if (c.name == std::get<std::string>(tokens[1].data)) {
			command = c;
		}
	}
	if (command.name == "null") {
		std::cout << "Error: invalid subcommand \"" << std::get<std::string>(tokens[1].data) << "\"" << std::endl;
		return;
	}

	if (tokens.size() - 2 != command.arguments.size()) {
		std::cout << "Error : expected " << command.arguments.size() << " arguments for \"" << std::get<std::string>(tokens[1].data) << "\" command, received " << tokens.size() - 2 << std::endl;
		return;
	}

	std::vector<Args> args;
	int x = 0;
	for (int i = 2; i < tokens.size(); i++) {
		Token token = tokens[i];

		Type t = command.arguments[x];
		if (token.type != t) {
			std::cout << "Error in token \"" << tokenStr(token) << "\": expected type \"" << stringForType(t) << "\", received type \"" << stringForType(token.type) << "\"" << std::endl;
			return;
		}
		args.push_back(token.data);

		x++;
	}

	try {
		command.callback(args);
	}
	catch (std::exception e) {
		std::cout << "Error running command callback: " << e.what() << std::endl;
	}

	// Make sure the game is still running
	m_running = m_env->running;
}

void Console::registerCommandGroup(const std::string& name) {
	CommandGroup cg;
	cg.name = name;
	m_registeredCommands.push_back(cg);
}

void Console::registerCommand(std::string name, std::string group, std::function<void(std::vector<Args>)> callback, std::vector<Type> params) {
	Command command;
	command.arguments = params;
	command.callback = callback;
	command.name = name;

	for (CommandGroup& cg : m_registeredCommands) {
		if (cg.name == group) {
			cg.subcommands.push_back(command);
			return;
		}
	}
	std::cout << "Error registering sub command \"" << name << "\": could not find command group \"" << group << "\"" << std::endl;
}