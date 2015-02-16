#include "MovementSystem.hpp"


void MovementSystem::configure(EventManager & event){
	event.subscribe<CollisionEvent>(*this);
}


void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){
	if (elaspedTime + interval > dt){
		return;
	}

	

	for (Entity & ent : entities.withComponents<Movable>()){
		Movable::Handle & mov = ent.getComponent<Movable>();
		if (ent.hasComponent<Gravity>()){
			Gravity::Handle & grav = ent.getComponent<Gravity>();
			mov->setVelocity(sf::Vector2f(mov->getVelocity().x, mov->getVelocity().y + grav->getFalling()));
		}
		mov->setPosition(mov->getPosition() + mov->getVelocity());
	}


	elaspedTime = dt;
}


void MovementSystem::receive(const CollisionEvent & event){

	//do fancy stuff
}


MovementSystem::~MovementSystem()
{
}
