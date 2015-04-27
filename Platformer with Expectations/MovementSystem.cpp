#include "MovementSystem.hpp"


void MovementSystem::configure(EventManager & event){
	event.subscribe<CollisionEvent>(*this);
}

void MovementSystem::update(EntityManager & entities, EventManager & events, double dt){
	for(Entity & entity : entities.withComponents<UserControlable>())
	{
		updateMovement(entity);
	}
	for (Entity & ent : entities.withComponents<Movable>()){
		updateGravity(ent);
		updateCollision(ent);
		updatePosition(ent);
		
	}
}


void MovementSystem::updatePosition(Entity & ent){
	Movable::Handle & mov = ent.getComponent<Movable>();
	mov->setPosition(mov->getPosition() + mov->getVelocity());
}

void MovementSystem::updateCollision(Entity & ent){
	if (ent.hasComponent<Colidable>()){
		ent.getComponent<Colidable>()->setPosition(ent.getComponent<Movable>()->getPosition());
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

void MovementSystem::updateMovement(Entity & id){
	/* check if we need to use keybuffer or ai component */
	if (id.hasComponent<UserControlable>()){
		Movable::Handle movHandle = id.getComponent<Movable>();
		sf::Vector2f velo = movHandle->getVelocity();
		if (!keybuffer.isEmpty()){
			switch (keybuffer.peek().second)
			{
			case PWE::PlayerAction::strafeLeft:
				if (!id.getComponent<Colidable>()->getCollision(Colidable::CollisionSide::left)){

					id.getComponent<Colidable>()->setCollision(false, Colidable::CollisionSide::right);
					velo.x = (velo.x > movHandle->getMaxVelocity().x * -1 ?
						velo.x + movHandle->speed.x * -1 : movHandle->getMaxVelocity().x*-1);
				}
			break;
			case PWE::PlayerAction::strafeRight:
				if (!id.getComponent<Colidable>()->getCollision(Colidable::CollisionSide::right)){

					id.getComponent<Colidable>()->setCollision(false, Colidable::CollisionSide::left);
					velo.x = (velo.x > movHandle->getMaxVelocity().x * 1 ?
						velo.x + movHandle->speed.x * 1 : movHandle->getMaxVelocity().x);
				}
				break;
			case PWE::PlayerAction::duck:
				break;
			case PWE::PlayerAction::jump:
				break;
			default:
				break;
			}
			keybuffer.pop();
		}else{

			if (velo.x > -1 && velo.x < 1){ velo.x = 0; }
			if (velo.x >= 1){ velo.x -= 0.5f; }
			if (velo.x <= -1){ velo.x += 0.5f; }
		}
		movHandle->setVelocity(velo);


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
