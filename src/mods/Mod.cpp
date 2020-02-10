#include <SFML/Graphics.hpp>
#include "Mod.hpp"
#include "..\enemies\Enemy.hpp"

void draw(sf::RenderWindow& window, sf::Drawable& toDraw) {
    window.draw(toDraw);
}

void setCirclePosition(sf::CircleShape& shape, float x, float y) {
    shape.setPosition(x, y);
}

bool frectIntersection(sf::FloatRect a, sf::FloatRect b) {
    return a.intersects(b);
}

void Mod::initializeScript(sol::state& script) {
    script.open_libraries(sol::lib::base);
    script.open_libraries(sol::lib::math);

    script["rand"] = irand;

    sol::usertype<sf::Color> color_type = script.new_usertype<sf::Color>("Color",
        sol::constructors<sf::Color(int, int, int), sf::Color(int, int, int, int)>());
    color_type["a"] = &sf::Color::a;

    sol::usertype<Enemy> enemy_type = script.new_usertype<Enemy>("Enemy",
        sol::constructors<Enemy(float, float, float, float, int), Enemy(float, float, float, float, int, sf::Color)>());

    sol::usertype<sf::Vector2f> vector2f_type = script.new_usertype<sf::Vector2f>("Vec2",
        sol::constructors<sf::Vector2f(float, float)>());

    vector2f_type["x"] = &sf::Vector2f::x;
    vector2f_type["y"] = &sf::Vector2f::y;

    sol::usertype<Spawner> spawner_type = script.new_usertype<Spawner>("Spawner",
        sol::no_constructor);

    sol::usertype<Environment> env_type = script.new_usertype<Environment>("Environment",
        sol::no_constructor);

    sol::usertype<Player> player_type = script.new_usertype<Player>("Player",
        sol::no_constructor);

    sol::usertype<sf::FloatRect> frect_type = script.new_usertype<sf::FloatRect>("FloatRect",
        sol::constructors<sf::FloatRect(sf::Vector2f, sf::Vector2f), sf::FloatRect(float, float, float, float)>());

    script["floatRectHitTest"] = frectIntersection;

    spawner_type["moving"] = sol::property(&Spawner::getMoving, &Spawner::setMoving);
    spawner_type["position"] = sol::property(&Spawner::getPosition, &Spawner::setPosition);

    spawner_type["instanceVars"] = &Spawner::instanceVars;

    env_type["player"] = sol::property(&Environment::getPlayer);
    env_type["addEnemy"] = &Environment::addModdedEnemy;

    player_type["position"] = sol::property(&Player::getPosition, &Player::setPosition);
    player_type["bounds"] = &Player::getBounds;
    enemy_type["position"] = sol::property(&Enemy::getPosition, &Enemy::setPosition);
    enemy_type["bounds"] = &Enemy::getBounds;

    enemy_type["velocity"] = sol::property(&Enemy::getVelocity, &Enemy::setVelocity);
    enemy_type["size"] = sol::property(&Enemy::getSize, &Enemy::setSize);
    enemy_type["fill"] = sol::property(&Enemy::getFill, &Enemy::setFill);
    enemy_type["setFatal"] = &Enemy::setFatal;

    enemy_type["instanceVars"] = &Enemy::instanceVars;

    sol::usertype<sf::RectangleShape> rect_type = script.new_usertype<sf::RectangleShape>("Rect",
        sol::constructors<sf::RectangleShape(sf::Vector2f)>(), sol::base_classes, sol::bases<sf::Drawable>());
    sol::usertype<sf::CircleShape> circle_type = script.new_usertype<sf::CircleShape>("Circle",
        sol::constructors<sf::CircleShape(float)>(), sol::base_classes, sol::bases<sf::Shape, sf::Drawable, sf::Transformable>());

    sol::usertype<sf::RenderWindow> window_type = script.new_usertype<sf::RenderWindow>("Window",
        sol::no_constructor);

    circle_type["setFill"] = &sf::CircleShape::setFillColor;
    circle_type["setBorder"] = &sf::CircleShape::setOutlineColor;
    circle_type["setBorderWidth"] = &sf::CircleShape::setOutlineThickness;
    script["setCirclePosition"] = setCirclePosition;

    script["draw"] = draw;

    enemy_type["geometry"];
}

Mod::Mod(std::string name, std::string path) : m_name(name), m_path(path) {
    m_mainScript = sol::state();
    initializeScript(m_mainScript);
    m_mainScript.script_file(path + name + ".lua");

    std::vector<std::string> modSpawners = getSpawners();
    for (std::string spawner : modSpawners) {
        sol::state* spawnerScript = new sol::state;
        initializeScript(*spawnerScript);
        spawnerScript->script_file(path + spawner + ".lua");
        (*spawnerScript)["_NAME"] = spawner;
        m_spawnerScripts.push_back(spawnerScript);
    }
}

sol::state* Mod::getScriptForSpawner(const std::string& name) {
    sol::state* script = nullptr;
    for (sol::state* spawnerScript : m_spawnerScripts) {
        if ((*spawnerScript)["_NAME"] == name) {
            script = spawnerScript;
        }
    }
    if (script == nullptr) {
        std::cout << "Fatal Error: could not find spawner with name \"" << name << "\"" << std::endl;
        abort();
    }
    return script;
}

Spawner* Mod::createSpawner(float x, Environment* env, const std::string& name) {
    /*
    SpawnerBase spawnerData = m_script[name];
    Spawner* spawner = new Spawner(x, env, spawnerData.fireTime, spawnerData.postMoveTime,
        spawnerData.fill, spawnerData.postMoveFill, spawnerData.warningFireFill, true, this, name);
    return spawner;
    */
    sol::state* script = getScriptForSpawner(name);

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
        std::cout << "Error: Could not load spawner data for spawer \"" << name << "\"" << std::endl;
        abort();
    }
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