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
		if (ent.hasComponent<Colidable>()){
			Colidable::Handle & handle = ent.getComponent<Colidable>();
			handle->setPosition(mov->getPosition());
		}
	}


	elaspedTime = dt;
}


void MovementSystem::receive(const CollisionEvent & event){
	Flag::Handle left = event.left.getComponent<Flag>();
	Flag::Handle right = event.right.getComponent<Flag>();

	if (event.left.hasComponent<Movable>()){
		colidedEntities.push_back(event.left.getId());
	}
	if (event.right.hasComponent<Movable>()){
		colidedEntities.push_back(event.right.getId());
	}

	std::cout << "Collision between: " << left->name << " And " << right->name << "\r\n";
	//do fancy stuff
}


MovementSystem::~MovementSystem()
{
}
