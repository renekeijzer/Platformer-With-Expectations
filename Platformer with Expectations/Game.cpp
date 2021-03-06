#include "Game.hpp"

Game::Game() : systemManager(entityManager, eventManager)
{

	an = Analytics::get(entityManager, systemManager, eventManager);
	EntityFactory::get(entityManager)->CreatePlayer(sf::Vector2f(100,100));
	MapLoader * loader = MapLoader::createInstance(entityManager);
	loader->GenerateLevel(1);
	delete loader; 
}


void Game::run(){
	
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer with expectations", sf::Style::Default);
	sf::Font font;
	initialize(window);

	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			default:
				break;
			}
		}

		window.clear();
		sf::Time elapsed = clock.getElapsedTime();
		update(static_cast<double>(elapsed.asMilliseconds()));
		window.display();
	}
}

void Game::initialize(sf::RenderWindow & target)
{
	
	map = new Keymap("keys.conf");
	map->load();

	
	systemManager.addSystem<ControlSystem>(10, buffer, map);
	systemManager.addSystem<CollisionSystem>(2,buffer);
	systemManager.addSystem<MovementSystem>(10, buffer);
	systemManager.addSystem<RenderSystem>(target);
	systemManager.configure();
}

void Game::update(double dt){
	systemManager.update<ControlSystem>(dt);
	systemManager.update<CollisionSystem>(dt);
	systemManager.update<MovementSystem>(dt);
	systemManager.update<RenderSystem>(dt);
	an->log();
}



Game::~Game()
{
	delete an;
	delete map;
}
