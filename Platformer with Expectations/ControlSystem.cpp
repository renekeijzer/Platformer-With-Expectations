#include "ControlSystem.hpp"

void ControlSystem::configure(EventManager & event){
	actions.push_back({ sf::Keyboard::Key::W, 0.0, 1.0 });
	actions.push_back({ sf::Keyboard::Key::A, -1.0, 0.0 });
	actions.push_back({ sf::Keyboard::Key::S, 0.0, -1.0 });
	actions.push_back({ sf::Keyboard::Key::D, 1.0, 0.0 });
	
}


void ControlSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity ent : entities.withComponents<UserControlable>()){
		Movable::Handle & mov = ent.getComponent<Movable>();
		for (const auto & action: actions){
			if (sf::Keyboard::isKeyPressed(action.key)){
				float x = mov->getSpeed().x * action.x;
				float y = mov->getSpeed().y * action.y;

				sf::Vector2f current = mov->getVelocity();
				
				if (current.x < mov->getMaxVelocity().x && current.x > mov->getMaxVelocity().x * -1){ current.x += x; }
				if (current.y < mov->getMaxVelocity().y && current.y > mov->getMaxVelocity().y * -1){ current.y += y; }

				mov->setVelocity(current); 
				std::cout << current.x << " - " << current.y << "\r\n";
				std::cout << mov->getVelocity().x << " - " << mov->getVelocity().y<< "\r\n";
			}
			else{
				
			}
		}
	}
}
ControlSystem::~ControlSystem()
{
}
