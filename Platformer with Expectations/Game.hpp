#pragma once
#include <SFML\Graphics.hpp>
#include <queue>

#include "TheGrid\NonCopyable.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"
#include "TheGrid\SystemManager.hpp"
#include "TheGrid\Analytics.hpp"

#include "Systems.hpp"
#include "EntityFactory.hpp"
#include "Keybuffer.hpp"
#include "MapLoader.hpp"

class Game :
	public NonCopyable
{
public:
	Game();
	void run();
	~Game();

	class Config{
	public:
		Config * get(){};
		Config * operator->(){ if (Instance == nullptr){ Instance = new Config; } return Instance; }
		bool Fullscreen = false;
		~Config();
	private:
		static Config * Instance;
		Config();
		Config(Config const&){};
		Config& operator=(Config const &){};

	};

private:
	void initialize(sf::RenderWindow & target);
	void update(double dt);
	

	EntityManager entityManager;
	EventManager eventManager;
	SystemManager systemManager;
	Analytics * an = nullptr;
	Keymap * map;
	Keybuffer<KeyMap> buffer;
};

