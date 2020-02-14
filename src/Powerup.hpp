#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <SFML/Graphics.hpp>

class Mod;
class Player;

class Powerup {
public:
	Powerup(float x, float y, sf::Sprite sprite, int activeTime, Mod* parent, std::string name);

	int update(Player* player);
	void render(sf::RenderWindow& window, Player* player);

	void activate(Player* player);
	void deactivate(Player* player);
	
	sf::Vector2f& getPosition();
	void setPosition(sf::Vector2f p);

	bool getActive();
	void setActive(bool a);

	sf::Sprite getSprite();
	void setSprite(sf::Sprite s);

private:
	sf::Sprite m_sprite;
	bool m_active;
	sf::Vector2f m_position;

	int m_counter;
	int activeTime;

	std::string m_name;

	Mod* parent;
};

#endif /* POWERUP_HPP */