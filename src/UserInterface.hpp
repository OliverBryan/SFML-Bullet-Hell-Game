#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Environment.hpp"

class UserInterface {
public:
	UserInterface(Environment* env);

	void update();
	void render(sf::RenderWindow& window);
private:
	int m_teleportRechargeCounter = 0;
	int m_teleportRecharge = 60;
	std::vector<sf::RectangleShape> m_ts;

	Environment* m_env;
	sf::Font m_font;
	sf::Text m_timerLabel;
	sf::Text m_waveLabel;
};

#endif /* USER_INFERFACE_HPP */