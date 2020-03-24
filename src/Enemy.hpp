#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Spawner.hpp"

// Class that represents an enemy, which are created by spawners and managed by the environment Most
// methods are virtual because non modded enemies technically still work, and they use classes
// derived from enemy that override enemy's methods, however this behavior is deprecated
class Enemy {
public:
	// Constructor and Destructor
	Enemy::Enemy(float x, float y, float velX, float velY, int lifetime, sf::Color fill = sf::Color::Black) :
		m_position(x, y), m_velocity(velX, velY), m_lifetime(lifetime), m_fill(fill), m_dfill(fill), m_size(10.0f, 10.0f) {}
	~Enemy() {}

	// Updates the enemy with default behavior (gets called even if a custom update is defined)
	int update();
	// Calls the enemyUpdate function in the enemies mod script (does not completely override default update)
	void customUpdate();

	// Calls the enemyRender function in the enemies mod script (completely overrides default render)
	bool customRender(sf::RenderWindow& window);
	// Renders the enemy with default render behavior (does not get called if a custom render is defined)
	sf::RectangleShape render(sf::RenderWindow& window);
	// Returns the bounds of the enemy as a float rectangle using the enemies current position and size
	sf::FloatRect getBounds() const {
		return sf::FloatRect(m_position, m_size);
	}

	// Initializes the enemy's mod state
	void modinit(Mod* parent, const std::string& name, Environment* env);

	// Getter and setter functions for enemy properties. They return mutable references because the
	// mod api needs them to function properly, it is not a design error
	sf::Vector2f& getPosition();
	void setPosition(sf::Vector2f p);

	sf::Vector2f& getVelocity();
	void setVelocity(sf::Vector2f v);

	sf::Vector2f& getSize();
	void setSize(sf::Vector2f s);

	sf::Color& getFill();
	void setFill(sf::Color c);

	void setFatal(bool f) {
		fatal = f;
	}

	bool stay = false;

	// Lua table representing the enemies instance variables (defined in mod script)
	sol::table instanceVars;
	// If true, the enemy will kill the player on contact, if false, it won't (defaults to true)
	bool fatal = true;

protected:
	// (Deprecated) True if the enemy is modded, false if it isn't
	bool modded;
	// Pointer to the enemies parent mod
	Mod* parent;
	// Name of the enemy (used for identification purposes)
	std::string name;
	// Pointer to the game's environment object
	Environment* m_env;

	// Counter representing the enemy's remaining lifetime
	int m_lifetime;
	// Float vector representing the enemy's position on screen
	sf::Vector2f m_position;
	// Float vector representing the size of the enemy
	sf::Vector2f m_size;
	// Float vector representing the enemy's velocity (directional movement)
	sf::Vector2f m_velocity;
	// Color object representing the enemy's current fill (mutable)
	sf::Color m_fill;
	// Color object representing the enemy's default fill (immutable)
	sf::Color m_dfill;
};

#endif /* ENEMY_HPP */