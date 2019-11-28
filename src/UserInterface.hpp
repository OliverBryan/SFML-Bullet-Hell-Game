#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <SFML/Graphics.hpp>

class UserInterface {
public:
	UserInterface() {};

	void update();
	void render(sf::RenderWindow& window);
};

#endif /* USER_INFERFACE_HPP */