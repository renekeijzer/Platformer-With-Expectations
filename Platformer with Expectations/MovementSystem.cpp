#include "MovementSystem.hpp"


void MovementSystem::configure(EventManager & event){
}


void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){
	if (elaspedTime + interval > dt){
		return;
	}
	for (Entity & ent : entities.withComponents<Movable>()){
		Movable::Handle & mov = ent.getComponent<Movable>();
		
		if (!mov->gettingDirection){
			mov->setVelocity(calculateIdleMovement(mov->getVelocity()));
		}
		sf::Vector2f next;
		next.x = mov->getPosition().x + mov->getVelocity().x;
		next.y = mov->getPosition().y + mov->getVelocity().y;

		mov->setPosition(next);
	}
	elaspedTime = dt;
}


sf::Vector2f MovementSystem::calculateIdleMovement(sf::Vector2f speed){
	
	if (speed.x < 1 && speed.x > -1){
		speed.x = 0;
	}
	else{
		speed.x -= pow(speed.x, 0.5);
	}
	return speed;
}



MovementSystem::~MovementSystem()
{
}
