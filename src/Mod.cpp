#include <SFML/Graphics.hpp>
#include "Mod.hpp"
#include "Enemy.hpp"
#include "Powerup.hpp"
#include <iostream>

void printRect(sf::RectangleShape& shape) {
	std::cout << "Rect: Pos=" << shape.getPosition().x << "," << shape.getPosition().y << " Size=" << shape.getSize().x << "," << shape.getSize().y << " Fill=" << shape.getFillColor().r << "," << shape.getFillColor().g << "," << shape.getFillColor().b << "," << shape.getFillColor().a << std::endl;
}

void draw(sf::RenderWindow& window, sf::Drawable& toDraw) {
	window.draw(toDraw);
}

void setCirclePosition(sf::CircleShape& shape, float x, float y) {
	shape.setPosition(x, y);
}

void setRectPosition(sf::RectangleShape& shape, float x, float y) {
	shape.setPosition(x, y);
}

bool frectIntersection(sf::FloatRect a, sf::FloatRect b) {
	return a.intersects(b);
}

void drawGradient(sf::RenderWindow& window, sf::RectangleShape& shape, sf::Color topColor, sf::Color bottomColor) {
	sf::VertexArray va(sf::Quads, 4);
	va[1].position = shape.getPosition() + shape.getPoint(0);
	va[1].color = topColor;
	va[2].position = shape.getPosition() + shape.getPoint(1);
	va[2].color = topColor;
	va[3].position = shape.getPosition() + shape.getPoint(2);
	va[3].color = bottomColor;
	va[0].position = shape.getPosition() + shape.getPoint(3);
	va[0].color = bottomColor;

	window.draw(va);
}

void Mod::initializeScript(sol::state& script) {
	script.open_libraries(sol::lib::base);
	script.open_libraries(sol::lib::math);
	script.open_libraries(sol::lib::table);

	script["rand"] = irand;
	script["floatRectHitTest"] = frectIntersection;
	script["printRect"] = printRect;
	script["setRectPosition"] = setRectPosition;
	script["drawGradient"] = drawGradient;
	script["draw"] = draw;
	script["setCirclePosition"] = setCirclePosition;

	sol::usertype<sf::Color> color_type = script.new_usertype<sf::Color>("Color",
		sol::constructors<sf::Color(int, int, int), sf::Color(int, int, int, int)>());
	color_type["a"] = &sf::Color::a;
	color_type["r"] = &sf::Color::r;
	color_type["g"] = &sf::Color::g;
	color_type["b"] = &sf::Color::b;

	sol::usertype<Enemy> enemy_type = script.new_usertype<Enemy>("Enemy",
		sol::constructors<Enemy(float, float, float, float, int), Enemy(float, float, float, float, int, sf::Color)>());
	enemy_type["position"] = sol::property(&Enemy::getPosition, &Enemy::setPosition);
	enemy_type["bounds"] = &Enemy::getBounds;
	enemy_type["velocity"] = sol::property(&Enemy::getVelocity, &Enemy::setVelocity);
	enemy_type["size"] = sol::property(&Enemy::getSize, &Enemy::setSize);
	enemy_type["fill"] = sol::property(&Enemy::getFill, &Enemy::setFill);
	enemy_type["setFatal"] = &Enemy::setFatal;
	enemy_type["instanceVars"] = &Enemy::instanceVars;

	sol::usertype<sf::Vector2f> vector2f_type = script.new_usertype<sf::Vector2f>("Vec2",
		sol::constructors<sf::Vector2f(float, float)>());
	vector2f_type["x"] = &sf::Vector2f::x;
	vector2f_type["y"] = &sf::Vector2f::y;

	sol::usertype<Spawner> spawner_type = script.new_usertype<Spawner>("Spawner",
		sol::no_constructor);
	spawner_type["moving"] = sol::property(&Spawner::getMoving, &Spawner::setMoving);
	spawner_type["position"] = sol::property(&Spawner::getPosition, &Spawner::setPosition);
	spawner_type["postmove"] = &Spawner::postmove;
	spawner_type["instanceVars"] = &Spawner::instanceVars;

	sol::usertype<Environment> env_type = script.new_usertype<Environment>("Environment",
		sol::no_constructor);
	env_type["player"] = sol::property(&Environment::getPlayer);
	env_type["addEnemy"] = &Environment::addModdedEnemy;
	env_type["removeEnemy"] = &Environment::removeModdedEnemy;
	env_type["tps"] = &Environment::TPS;

	sol::usertype<Player> player_type = script.new_usertype<Player>("Player",
		sol::no_constructor);
	player_type["position"] = sol::property(&Player::getPosition, &Player::setPosition);
	player_type["bounds"] = &Player::getBounds;

	sol::usertype<sf::FloatRect> frect_type = script.new_usertype<sf::FloatRect>("FloatRect",
		sol::constructors<sf::FloatRect(sf::Vector2f, sf::Vector2f), sf::FloatRect(float, float, float, float)>());

	player_type["invincible"] = &Player::invincible;
	player_type["speed"] = sol::property(&Player::getSpeed, &Player::setSpeed);

	sol::usertype<sf::RectangleShape> rect_type = script.new_usertype<sf::RectangleShape>("Rect",
		sol::constructors<sf::RectangleShape(sf::Vector2f)>(), sol::base_classes, sol::bases<sf::Shape, sf::Drawable, sf::Transformable>());
	rect_type["setFill"] = &sf::RectangleShape::setFillColor;

	sol::usertype<sf::CircleShape> circle_type = script.new_usertype<sf::CircleShape>("Circle",
		sol::constructors<sf::CircleShape(float)>(), sol::base_classes, sol::bases<sf::Shape, sf::Drawable, sf::Transformable>());
	circle_type["setFill"] = &sf::CircleShape::setFillColor;
	circle_type["setBorder"] = &sf::CircleShape::setOutlineColor;
	circle_type["setBorderWidth"] = &sf::CircleShape::setOutlineThickness;

	sol::usertype<Powerup> powerup_type = script.new_usertype<Powerup>("Powerup",
		sol::no_constructor);
	powerup_type["position"] = sol::property(&Powerup::getPosition, &Powerup::setPosition);
	powerup_type["active"] = sol::property(&Powerup::getActive, &Powerup::setActive);

	sol::usertype<sf::RenderWindow> window_type = script.new_usertype<sf::RenderWindow>("Window",
		sol::no_constructor);
}

Mod::Mod(std::string name, std::string path) : m_name(name), m_path(path) {
	m_mainScript = sol::state();
	initializeScript(m_mainScript);
	m_mainScript.script_file(path + name + ".lua");

	std::vector<std::string> modSpawners = getSpawners();
	std::vector<std::string> modPowerups = getPowerups();

	for (std::string spawner : modSpawners) {
		sol::state* spawnerScript = new sol::state;
		initializeScript(*spawnerScript);
		sol::protected_function_result result = spawnerScript->script_file(path + "/spawners/" + spawner + ".lua");
		if (!result.valid()) {
			std::cout << "Error in loading script for spawner " << spawner << ":" << std::endl;
			sol::error err = result;
			std::cout << err.what() << std::endl;
		}
		(*spawnerScript)["_NAME"] = spawner;
		m_spawnerScripts.push_back(spawnerScript);
	}

	for (std::string powerup : modPowerups) {
		sol::state* powerupScript = new sol::state;
		initializeScript(*powerupScript);
		sol::protected_function_result result = powerupScript->script_file(path + "/powerups/" + powerup + ".lua");
		if (!result.valid()) {
			std::cout << "Error in loading script for powerup " << powerup << ":" << std::endl;
			sol::error err = result;
			std::cout << err.what() << std::endl;
		}
		(*powerupScript)["_NAME"] = powerup;
		m_powerupScripts.push_back(powerupScript);
	}
}

Mod::~Mod() {
	while (!m_spawnerScripts.empty()) {
		for (int i = 0; i < m_spawnerScripts.size(); i++) {
			sol::state* script = m_spawnerScripts[i];
			m_spawnerScripts.erase(m_spawnerScripts.begin() + i);
			delete script;
		}
	}

	while (!m_powerupScripts.empty()) {
		for (int i = 0; i < m_powerupScripts.size(); i++) {
			sol::state* script = m_powerupScripts[i];
			m_powerupScripts.erase(m_powerupScripts.begin() + i);
			delete script;
		}
	}

	//TODO: Clean up textures
}

sol::state* Mod::getScriptForSpawner(const std::string& name, const std::string& origin) {
	sol::state* script = nullptr;
	for (sol::state* spawnerScript : m_spawnerScripts) {
		if ((*spawnerScript)["_NAME"] == name) {
			script = spawnerScript;
		}
	}
	if (script == nullptr) {
		std::cout << "ORIGIN " << origin << std::endl;
		std::cout << "Fatal Error: could not find spawner with name \"" << name << "\"" << std::endl;
		abort();
	}

	return script;
}

sol::state* Mod::getScriptForPowerup(const std::string& name) {
	sol::state* script = nullptr;
	for (sol::state* powerupScript : m_powerupScripts) {
		if ((*powerupScript)["_NAME"] == name) {
			script = powerupScript;
		}
	}
	if (script == nullptr) {
		std::cout << "Fatal Error: could not find powerup with name \"" << name << "\"" << std::endl;
		abort();
	}
	return script;
}

Spawner* Mod::createSpawner(float x, Environment* env, const std::string& name) {
	sol::state* script = getScriptForSpawner(name, "createSpawner");

	try {
		auto spawnerData = (*script)[name];
		int fireTime = spawnerData["fireTime"];
		int postMoveTime = spawnerData["postMoveTime"].get_or(0);
		sf::Color fill = spawnerData["fill"];
		sf::Color postMoveFill = spawnerData["postMoveFill"].get_or(fill);
		sf::Color warningFireFill = spawnerData["warningFireFill"].get_or(fill);
		return new Spawner(x, env, fireTime, postMoveTime, fill, postMoveFill, warningFireFill, true, this, name);
	}
	catch (sol::error e) {
		std::cout << "Error: Could not load spawner data for spawner \"" << name << "\"" << std::endl;
		abort();
	}
}

Powerup* Mod::createPowerup(float x, float y, const std::string& name) {
	sol::state* script = getScriptForPowerup(name);

	try {
		auto powerupData = (*script)[name];
		int activeTime = powerupData["activeTime"];
		std::string sprite = powerupData["sprite"];
		sf::Texture* t = new sf::Texture;
		if (t->loadFromFile("./mods/" + m_name + "/sprites/" + sprite)) {
			bool animated = powerupData["animated"].get_or(false);
			int frameCount = powerupData["frames"].get_or(0);
			int frameDelay = powerupData["frameDelay"].get_or(0);
			sf::Sprite s(*t);
			m_textures.insert(std::make_pair(sprite, t));
			return new Powerup(x, y, s, activeTime, this, name, animated, frameCount, frameDelay);
		}
		else {
			std::cout << "Error: could not load texture for powerup \"" << name << "\"" << std::endl;
			abort();
		}
	}
	catch (sol::error e) {
		std::cout << "Error: could not load powerup data for powerup \"" << name << "\"" << std::endl;
	}

	return nullptr;
}

std::vector<std::string> Mod::getSpawners() {
	int i = 1;
	bool m = true;
	std::vector<std::string> spawners;
	sol::table names = m_mainScript["exportedSpawners"];
	while (m) {
		std::string name = names[i].get_or(std::string("none"));
		if (name == "none")
			m = false;
		else spawners.push_back(name);
		i++;
	}

	return spawners;
}

std::vector<std::string> Mod::getPowerups() {
	int i = 1;
	bool m = true;
	std::vector<std::string> powerups;
	sol::table names = m_mainScript["exportedPowerups"];
	while (m) {
		std::string name = names[i].get_or(std::string("none"));
		if (name == "none")
			m = false;
		else powerups.push_back(name);
		i++;
	}

	return powerups;
}