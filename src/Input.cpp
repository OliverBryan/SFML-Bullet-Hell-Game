#include "Input.hpp"

std::unordered_map<std::string, sf::Keyboard::Key> Input::m_keybinds;

void Input::init(sol::state& config) {
	sol::table keybindsTable = config["keybinds"];
	for (auto keybind : keybindsTable) {
		auto t = keybind.second.get_type();
		std::string action = keybind.first.as<std::string>();
		sf::Keyboard::Key key = keybind.second.as<sf::Keyboard::Key>();
		m_keybinds.insert(std::make_pair(action, key));
	}
}

bool Input::pressed(const std::string& action) {
	return sf::Keyboard::isKeyPressed(m_keybinds[action]);
}

void Input::registerKeys(sol::state& config) {
	config.new_enum("Keys",
		"A", sf::Keyboard::A,
		"B", sf::Keyboard::B,
		"C", sf::Keyboard::C,
		"D", sf::Keyboard::D,
		"E", sf::Keyboard::E,
		"F", sf::Keyboard::F,
		"G", sf::Keyboard::G,
		"H", sf::Keyboard::H,
		"I", sf::Keyboard::I,
		"J", sf::Keyboard::J,
		"K", sf::Keyboard::K,
		"L", sf::Keyboard::L,
		"M", sf::Keyboard::M,
		"N", sf::Keyboard::N,
		"O", sf::Keyboard::O,
		"P", sf::Keyboard::P,
		"Q", sf::Keyboard::Q,
		"R", sf::Keyboard::R,
		"S", sf::Keyboard::S,
		"T", sf::Keyboard::T,
		"U", sf::Keyboard::U,
		"V", sf::Keyboard::V,
		"W", sf::Keyboard::W,
		"X", sf::Keyboard::X,
		"Y", sf::Keyboard::Y,
		"Z", sf::Keyboard::Z,
		"0", sf::Keyboard::Num0,
		"1", sf::Keyboard::Num1,
		"2", sf::Keyboard::Num2,
		"3", sf::Keyboard::Num3,
		"4", sf::Keyboard::Num4,
		"5", sf::Keyboard::Num5,
		"6", sf::Keyboard::Num6,
		"7", sf::Keyboard::Num7,
		"8", sf::Keyboard::Num8,
		"9", sf::Keyboard::Num9
	);
}