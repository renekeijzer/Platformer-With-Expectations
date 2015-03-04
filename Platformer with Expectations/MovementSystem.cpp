#include "MovementSystem.hpp"


void MovementSystem::configure(EventManager & event){
	event.subscribe<CollisionEvent>(*this);
}
void MovementSystem::handleCollisions(EntityManager & entities){
	while (!colidedEntities.empty() ){
		auto & colidedPair = colidedEntities.top();

		auto lhs = entities.get(colidedPair.first);
		auto rhs = entities.get(colidedPair.second);
		
		Flag::Handle & rhsFlag = rhs.getComponent<Flag>();
		Flag::Handle & lhsFlag = lhs.getComponent<Flag>();

		switch (lhsFlag->type){
		case PWE::EntityTypes::Player:
			if (rhsFlag->type == PWE::EntityTypes::Tile){
				Colidable::Handle & lhsColidable = lhs.getComponent<Colidable>();
				Colidable::Handle & rhsColidable = rhs.getComponent<Colidable>();

				if (lhsColidable->getPosition().y <= rhsColidable->getPosition().y){
					Gravity::Handle & lhsGravity = lhs.getComponent<Gravity>();
					Movable::Handle & lhsMovable = lhs.getComponent<Movable>();

					
					float yDif = rhsColidable->getPosition().y - (lhsColidable->getPosition().y + lhsColidable->getWidth());
					
					lhsMovable->setPosition(lhsMovable->getPosition().x, lhsMovable->getPosition().y + yDif);
					updateCollision(lhs);
					
					
					lhsMovable->setVelocity(lhsMovable->getVelocity().x, 0);
					lhsGravity->setFalling(false);
					lhsGravity->setJumping(false);
					
				}
			

			}
			break;
		case PWE::EntityTypes::Tile:
			std::cout << "Was Tile collision";
			break;
		default:
			std::cerr << "UNKNOWN ENTITY TYPE SOMETHING WENT WRONG";
		}

		colidedEntities.pop();

	}
}

void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){
	if (elaspedTime + interval > dt){
		return;
	}
	handleCollisions(entities);
	for (Entity & ent : entities.withComponents<Movable>()){
		updateGravity(ent);
		updateCollision(ent);
		updatePosition(ent);
		
	}



	elaspedTime = dt;
}


void MovementSystem::updatePosition(Entity & ent){
	Movable::Handle & mov = ent.getComponent<Movable>();
	mov->setPosition(mov->getPosition() + mov->getVelocity());
}

void MovementSystem::updateCollision(Entity & ent){
	if (ent.hasComponent<Colidable>()){
		Movable::Handle & mov = ent.getComponent<Movable>();
		Colidable::Handle & handle = ent.getComponent<Colidable>();
		handle->setPosition(mov->getPosition());
	}
}
void MovementSystem::updateGravity(Entity & ent){
	if (ent.hasComponent<Gravity>()){
		Movable::Handle & mov = ent.getComponent<Movable>();
		Gravity::Handle & grav = ent.getComponent<Gravity>();
		if (grav->isFalling()){
			mov->setVelocity(sf::Vector2f(mov->getVelocity().x, mov->getVelocity().y + grav->getFalling()));
		}
	}
}

void MovementSystem::receive(const CollisionEvent & event){
	Flag::Handle left = event.left.getComponent<Flag>();
	Flag::Handle right = event.right.getComponent<Flag>();

	if (event.left.hasComponent<Movable>()){
		colidedEntities.push(std::make_pair( event.left.getId(), event.right.getId()));
	}
	if (event.right.hasComponent<Movable>()){
		colidedEntities.push(std::make_pair(event.left.getId(), event.right.getId()));
	}

}


MovementSystem::~MovementSystem()
{
}
