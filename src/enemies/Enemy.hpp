#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include "..\spawners\Spawner.hpp"

class Enemy {
public:
	Enemy(float x, float y, float velX, float velY, int lifetime, sf::Color fill = sf::Color::Black) : 
		m_position(x, y), m_velocity(velX, velY), m_lifetime(lifetime), m_fill(fill), m_dfill(fill), m_size(10.0f, 10.0f) {}
	virtual ~Enemy() {}

	void init();

	virtual int update();
	virtual void customUpdate() {}
	virtual void render(sf::RenderWindow& window);
	virtual sf::FloatRect getBounds() {
		return sf::FloatRect(m_position, m_size);
	}

protected:
	int m_lifetime;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	sf::Color m_fill;
	sf::Color m_dfill;
};

#endif /* ENEMY_HPP */