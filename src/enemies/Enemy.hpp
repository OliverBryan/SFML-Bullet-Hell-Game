#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "..\spawners\Spawner.hpp"

class Enemy {
public:
	Enemy(float x, float y, float velX, float velY, int lifetime, sf::Color fill = sf::Color::Black) :
		m_position(x, y), m_velocity(velX, velY), m_lifetime(lifetime), m_fill(fill), m_dfill(fill), m_size(10.0f, 10.0f) {}
	virtual ~Enemy() {}

	void init();

	virtual int update();
	virtual void customUpdate();

	bool customRender(sf::RenderWindow& window);
	virtual void render(sf::RenderWindow& window);
	virtual sf::FloatRect getBounds() const {
		return sf::FloatRect(m_position, m_size);
	}

	void modinit(Mod* parent, const std::string& name, Environment* env) {
		modded = true;
		this->parent = parent;
		this->name = name;
		m_env = env;
	}

	sf::Vector2f& getPosition();
	void setPosition(sf::Vector2f p);

	sf::Vector2f& getVelocity();
	void setVelocity(sf::Vector2f v);

	sf::Vector2f& getSize();
	void setSize(sf::Vector2f s);

	sf::Color& getFill();
	void setFill(sf::Color c);

protected:
	bool modded;
	Mod* parent;
	std::string name;
	Environment* m_env; //MODS ONLY

	int m_lifetime;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	sf::Color m_fill;
	sf::Color m_dfill;
};

#endif /* ENEMY_HPP */