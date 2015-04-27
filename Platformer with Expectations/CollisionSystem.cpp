#include "CollisionSystem.hpp"




void CollisionSystem::update(EntityManager & entities, EventManager & events, double dt){
	sf::Rect<float> * CollisionRect = new sf::Rect<float>();

	for (Entity & ent : entities.withComponents<UserControlable, PhysicalComponent>()){
		for (Entity & oth: entities.withComponents<Colidable>()){
			if (ent != oth){
				if (ent.getComponent<PhysicalComponent>()->willColide(oth, CollisionRect)){
					ent.getComponent<PhysicalComponent>()->fixMovement(*CollisionRect);
					if (keybuffer.size() > 0){ 
						auto key = keybuffer.peek();
						keybuffer.remove(key);
					}
				}
				else
				{
					if (ent.getComponent<Movable>()->getVelocity().y == 0){
						ent.getComponent<Gravity>()->setFalling(true);
					}
				}
			}
		}
	}
	delete CollisionRect;
	for (Entity & ent : entities.withComponents<PhysicalComponent>()){
		Colidable::Handle & colHandle = ent.getComponent<Colidable>();
		for (Entity & other : entities.withComponents<Colidable>()){
			if (ent != other){
				Colidable::Handle & otherHandle = other.getComponent<Colidable>();

				if (PhysicalComponent::Collides(ent, other).width > 0 && PhysicalComponent::Collides(ent,other).height > 0){
					events.emit<CollisionEvent>(ent, other);
				}
			}
		}
	}
}


void CollisionSystem::configure(EventManager & event){  }
Colidable::Handle CollisionSystem::predicate(Entity & ent){

	if (ent.hasComponent<Colidable>()){
		Colidable::Handle colidable = ent.getComponent<Colidable>();
		Movable::Handle movHandle = ent.getComponent<Movable>();
		sf::Vector2f velo = movHandle->getVelocity();

		if (!keybuffer.isEmpty()){
			switch (keybuffer.peek().second)
				{
				case PWE::PlayerAction::strafeLeft:
					velo.x = (velo.x > movHandle->getMaxVelocity().x * -1 ?
						velo.x + movHandle->speed.x * -1 : movHandle->getMaxVelocity().x*-1);
					break;
				case PWE::PlayerAction::strafeRight:
					velo.x = (velo.x > movHandle->getMaxVelocity().x * 1 ?
						velo.x + movHandle->speed.x * 1 : movHandle->getMaxVelocity().x);
					break;
				default:
					break;
				}
			if (ent.hasComponent<Gravity>()){
				Gravity::Handle grav = ent.getComponent<Gravity>();
				if (grav->isFalling()){
					velo.y += grav->getFalling();
				}
			}
				
				colidable->setPosition(colidable->getPosition().x + velo.x, colidable->getPosition().y);
				return colidable;
				
		}
		else
		{ 
			return colidable; 
		}
	}else{
		return Colidable::Handle();
	}
}



CollisionSystem::~CollisionSystem()
{
}
