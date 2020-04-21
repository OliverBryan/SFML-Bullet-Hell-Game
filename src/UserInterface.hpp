#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include "Environment.hpp"

class UserInterface {
public:
	UserInterface(Environment* env);

	void update();
	void pauseUpdate();
	void render(sf::RenderWindow& window);

private:
	int m_teleportRechargeCounter = 0;
	std::vector<sf::RectangleShape> m_ts;

	void handleKeyBinds();

	bool pKeyDown = false;

	Environment* m_env;
	sf::Font m_font;
	sf::Text m_timerLabel;
	sf::Text m_waveLabel;
	sf::Text m_statusLabel;

	float oldTPS = 60.0f;
};

#endif /* USER_INFERFACE_HPP */