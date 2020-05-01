#ifndef INPUT_HPP
#define INPUT_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

class Console;

struct Action {
	std::string name;
	std::vector<std::string> commands;
	std::vector<std::vector<sf::Keyboard::Key>> keys;

	Action(std::string n, std::vector<std::string> c, std::vector<std::vector<sf::Keyboard::Key>> k) :
		name(n), commands(c), keys(k) {}
};

class Input {
public:
	static void init(sol::state& config);

	static bool pressed(const std::string& action);

	static void handleActions(const std::unordered_map<sf::Keyboard::Key, bool>& keys, Console& console);

	static void registerKeys(sol::state& config);

private:
	static std::unordered_map<std::string, std::vector<sf::Keyboard::Key>> m_keybinds;
	static std::vector<Action> m_actions;
};

#endif /* INPUT_HPP */