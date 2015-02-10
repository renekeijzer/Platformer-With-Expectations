#include "ControlSystem.hpp"

void ControlSystem::configure(EventManager & event){
	actions.push_back({ sf::Keyboard::Key::W, 0, -1 });
	actions.push_back({ sf::Keyboard::Key::A, -1, 0 });
	actions.push_back({ sf::Keyboard::Key::S, 0, 1 });
	actions.push_back({ sf::Keyboard::Key::D, 1, 0 });
	
}


void ControlSystem::update(EntityManager & entities, EventManager & events, double dt){
	if (elapsedTime + interval > dt){
		return;
	}
		for (Entity ent : entities.withComponents<UserControlable>()){
			Movable::Handle & mov = ent.getComponent<Movable>();
			for (const auto & action : actions){
				if (sf::Keyboard::isKeyPressed(action.key)){
					mov->setVelocity(sf::Vector2f(mov->getVelocity().x + mov->speed.x * action.x, mov->getVelocity().y + mov->speed.y * action.y));
				}
			}
		}

		elapsedTime = dt;
	
}
ControlSystem::~ControlSystem()
{
}
