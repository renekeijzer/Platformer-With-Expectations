#include "MovementSystem.hpp"


void MovementSystem::configure(EventManager & event){
}


void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity & ent : entities.withComponents<Movable>()){
		Movable::Handle & mov = ent.getComponent<Movable>();

		std::cout << mov->getPosition().x << " - " << mov->getPosition().y << "\r\n";
		std::cout << mov->getVelocity().x << " - " << mov->getVelocity().y << "\r\n";

		sf::Vector2f next;
		next.x = mov->getPosition().x + mov->getVelocity().x;
		next.y = mov->getPosition().y + mov->getVelocity().y;


		mov->setPosition(next);
	}
}

MovementSystem::~MovementSystem()
{
}
