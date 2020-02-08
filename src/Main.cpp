#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "UserInterface.hpp"
#include "Environment.hpp"
#include "Console.hpp"
#include <fstream>
#include <map>
#include <future>

int main() {
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(700, 440), "Bullet Hell Game", sf::Style::Default, cs);

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / FPS);

	Environment env;
	UserInterface ui(&env);
	Console console(&env);
	auto t = std::async(std::launch::async, &Console::run, &console);

	while (window.isOpen()) {
		sf::Clock c;
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
			case sf::Event::Closed:
				window.close();
			}
		}

		while (accumulator > ups) {
			accumulator -= ups;
			//update
			if (env.running && !env.paused) {
				env.update();
				ui.update();
			}
			else if (env.paused)
				ui.pauseUpdate();
			else env.clearEnemies();
		}

		//render
		window.clear(sf::Color::Black);

		ui.render(window);
		env.render(window);

		window.display();
		accumulator += clock.restart();
	}
	t.get();
	return 0;
}