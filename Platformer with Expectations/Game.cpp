#include "Game.hpp"
#include "Systems.hpp"

Game::Game() :  systemManager(entityManager, eventManager)
{
	an = Analytics::get(entityManager, systemManager, eventManager);
}


void Game::run(){

	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Platformer with expectations", sf::Style::Fullscreen);
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
		sf::Time elapsed = clock.restart();
		update(static_cast<double>(elapsed.asSeconds()));
		window.display();
	}
}

void Game::initialize(sf::RenderTarget & target){
	systemManager.addSystem<ControlSystem>();

	systemManager.configure();
}

void Game::update(double dt){
	systemManager.update<ControlSystem>(dt);
	an->log();
}



Game::~Game()
{
}
