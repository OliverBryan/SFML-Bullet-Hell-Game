#include "Mod.hpp"
#include "..\enemies\Enemy.hpp"

class SpawnerBase {
public:
    SpawnerBase(int firetime, int postmovetime, sf::Color fill, sf::Color postmovefill, sf::Color warningfirefill) : 
       fireTime(firetime), postMoveTime(postmovetime), fill(fill), postMoveFill(postmovefill),
       warningFireFill(warningfirefill) {}

    SpawnerBase(int firetime, sf::Color fill) : SpawnerBase(firetime, 0, fill, fill, fill) {}
    SpawnerBase(int firetime, int postmovetime, sf::Color fill, sf::Color postmovefill) : SpawnerBase(firetime, postmovetime, fill, postmovefill, fill) {}
    SpawnerBase(int firetime, sf::Color fill, sf::Color warningfirefill) : SpawnerBase(firetime, 0, fill, fill, warningfirefill) {}

    int fireTime;
    int postMoveTime;
    sf::Color fill;
    sf::Color postMoveFill;
    sf::Color warningFireFill;
};

Mod::Mod(std::string name, std::string path) : m_name(name), m_path(path) {
    m_script.open_libraries(sol::lib::base);
    m_script.open_libraries(sol::lib::math);

    sol::usertype<sf::Color> color_type = m_script.new_usertype<sf::Color>("Color",
        sol::constructors< sf::Color(int, int, int)>());

    sol::usertype<Enemy> enemy_type = m_script.new_usertype<Enemy>("Enemy",
        sol::constructors<Enemy(float, float, float, float, int), Enemy(float, float, float, float, int, sf::Color)>());

    
    sol::usertype<SpawnerBase> spawnerbase_type = m_script.new_usertype<SpawnerBase>("SpawnerBase",
        sol::constructors<SpawnerBase(int, int, sf::Color, sf::Color, sf::Color), SpawnerBase(int, sf::Color),
                          SpawnerBase(int, int, sf::Color, sf::Color), SpawnerBase(int, sf::Color, sf::Color)>());

    sol::usertype<sf::Vector2f> vector2f_type = m_script.new_usertype<sf::Vector2f>("Vec2",
        sol::constructors<sf::Vector2f(float, float)>());

    vector2f_type["x"] = &sf::Vector2f::x;
    vector2f_type["y"] = &sf::Vector2f::y;

    sol::usertype<Spawner> spawner_type = m_script.new_usertype<Spawner>("Spawner",
        sol::no_constructor);

    sol::usertype<Environment> env_type = m_script.new_usertype<Environment>("Environment",
        sol::no_constructor);

    sol::usertype<Player> player_type = m_script.new_usertype<Player>("Player",
        sol::no_constructor);

    spawner_type["moving"] = sol::property(&Spawner::getMoving, &Spawner::setMoving);
    spawner_type["position"] = sol::property(&Spawner::getPosition, &Spawner::setPosition);

    env_type["player"] = sol::property(&Environment::getPlayer);
    env_type["addEnemy"] = &Environment::addModdedEnemy;

    player_type["position"] = sol::property(&Player::getPosition, &Player::setPosition);
    enemy_type["position"] = sol::property(&Enemy::getPosition, &Enemy::setPosition);

    enemy_type["velocity"] = sol::property(&Enemy::getVelocity, &Enemy::setVelocity);

    m_script.script_file(path);
}

Spawner* Mod::createSpawner(float x, Environment* env, const std::string& name) {
    /*
    SpawnerBase spawnerData = m_script[name];
    Spawner* spawner = new Spawner(x, env, spawnerData.fireTime, spawnerData.postMoveTime,
        spawnerData.fill, spawnerData.postMoveFill, spawnerData.warningFireFill, true, this, name);
    return spawner;
    */
    auto spawnerData = m_script[name];
    int fireTime = spawnerData["fireTime"];
    int postMoveTime = spawnerData["postMoveTime"].get_or(0);
    sf::Color fill = spawnerData["fill"];
    sf::Color postMoveFill = spawnerData["postMoveFill"].get_or(fill);
    sf::Color warningFireFill = spawnerData["warningFireFill"].get_or(fill);
    return new Spawner(x, env, fireTime, postMoveTime, fill, postMoveFill, warningFireFill, true, this, name);
}

std::vector<std::string> Mod::getSpawners() {
    int i = 1;
    bool m = true;
    std::vector<std::string> spawners;
    sol::table names = m_script["exportedSpawners"];
    while (m) {
        std::string name = names[i].get_or(std::string("none"));
        if (name == "none")
            m = false;
        else spawners.push_back(name);
        i++;
    }

    return spawners;
}