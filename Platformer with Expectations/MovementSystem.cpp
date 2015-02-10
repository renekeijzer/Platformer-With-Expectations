#include "MovementSystem.hpp"


void MovementSystem::configure(EventManager & event){
}


void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){
	if (elaspedTime + interval > dt){
		return;
	}
	for (Entity & ent : entities.withComponents<Movable>()){
		Movable::Handle & mov = ent.getComponent<Movable>();
		mov->setPosition(mov->getPosition() + mov->getVelocity());
	}
	elaspedTime = dt;
}



MovementSystem::~MovementSystem()
{
}
