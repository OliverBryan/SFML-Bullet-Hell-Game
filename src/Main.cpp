#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.hpp"
#include "UserInterface.hpp"
#include "Environment.hpp"
#include "Console.hpp"
#include <fstream>
#include <map>
#include <future>

// TODO:
// Admin Console: improve command parser
// Wave System: implement new system

int main() {
	// Create Window
	// Initialize a context settings object, and set the antialiasing level to its max
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;
	// Actually initialize the window object, with a size of 700px by 400px, with the default window style
	sf::RenderWindow window(sf::VideoMode(700, 440), "Bullet Hell Game", sf::Style::Default, cs);

	// Create timer clock, set the update speed to the FPS variable define in Environment.hpp
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / FPS);

	// Create the game environment object and the UI object
	Environment env;
	UserInterface ui(&env);
	// Create the admin console
	Console console(&env);
	// Start the admin console on a separate thread, so that it can run at the same time as the game
	auto t = std::async(std::launch::async, &Console::run, &console);

	// Core event loop; run until window is closed
	while (window.isOpen()) {
		// Create local clock object
		sf::Clock c;
		// Poll the window for events
		sf::Event e;
		while (window.pollEvent(e)) {
			switch (e.type) {
				// Close the window if a close event is received
			case sf::Event::Closed:
				window.close();
			}
		}

		// Update according to the FPS
		while (accumulator > ups) {
			accumulator -= ups;
			// Update the Environment (GameObjects) and the UI if the game is not paused
			if (env.running && !env.paused) {
				env.update();
				ui.update();
			}
			// If the game is paused, call the special pause update function for the UI
			else if (env.paused)
				ui.pauseUpdate();
			else env.clearEnemies();
		}

		// Render
		// Clear the window
		window.clear(sf::Color::Black);

		// Render the UI and the Environment (GameObjects)
		ui.render(window);
		env.render(window);

		// Display the window, update the clock
		window.display();
		accumulator += clock.restart();
	}

	// Close the admin console thread
	t.get();
	return 0;
}