#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
	Player(float x, float y) : m_position(x, y), m_teleports(3) {}
	void update();
	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds();

	sf::Vector2f& getPosition();
	void setPosition(sf::Vector2f p);

	bool invincible = false;
	friend class UserInterface;
	friend class Console;
	friend class Bot;
private:
	sf::Vector2f m_position;
	int m_teleports = 3;
	bool teleportKeyPressed = false;
	int m_speed = 2;
};

#endif /* PLAYER_HPP */