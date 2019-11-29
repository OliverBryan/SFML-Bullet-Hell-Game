#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "..\spawners\Spawner.hpp"

class Enemy {
public:
	Enemy(float x, float y, float velX, float velY, int lifetime) : 
		m_position(x, y), m_velocity(velX, velY), m_lifetime(lifetime) {}
	virtual ~Enemy() {}

	virtual int update();
	virtual void render(sf::RenderWindow& window) = 0;
	virtual sf::FloatRect getBounds() = 0;

protected:
	int m_lifetime;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
};

#endif /* ENEMY_HPP */