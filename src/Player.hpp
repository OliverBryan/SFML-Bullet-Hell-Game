#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Powerup.hpp"

class Player {
public:
	Player(float x, float y, Environment* env) : m_position(x, y), m_teleports(3), m_env(env) {}
	void update();
	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds();

	sf::Vector2f& getPosition();
	void setPosition(sf::Vector2f p);

	bool invincible = false;
	friend class UserInterface;
	friend class Console;

	void setPowerup(Powerup* powerup);

	int getSpeed();
	void setSpeed(int speed);

	friend class Console;

private:
	sf::Vector2f m_position;
	int m_teleports = 3;
	bool teleportKeyPressed = false;
	bool powerupKeyPressed = false;
	int m_speed = 2;

	Environment* m_env;
	Powerup* m_powerup = nullptr;
};

#endif /* PLAYER_HPP */