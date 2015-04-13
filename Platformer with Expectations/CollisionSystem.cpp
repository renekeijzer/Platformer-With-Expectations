#include "CollisionSystem.hpp"




void CollisionSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity & ent : entities.withComponents<UserControlable>()){
		for (Entity & oth: entities.withComponents<Colidable>()){
			if (oth != ent){
				Colidable::Handle otherhandle = oth.getComponent<Colidable>();
				sf::Rect<float> colRect = Collides(otherhandle, predicate(ent));
				if (colRect.height != 0 || colRect.width != 0 ){
						std::cout << "Colided with: " << otherhandle->toString() << " - ent: " << predicate(ent)->toString() << "\r\n";
						std::cout << "Collision rect: {(" << colRect.left << "," << colRect.top << "), " << round(colRect.width) << ", " << colRect.height << "}" << std::endl << std::endl;
						Movable::Handle mov = ent.getComponent<Movable>();
						sf::Vector2f currentVel = mov->getVelocity();
						
						if (colRect.height > 0){
							if (currentVel.y < 0){
								std::cout << "correcting movement with y: " << round(colRect.height)/2 << std::endl;
								mov->setVelocity(currentVel.x, currentVel.y + round(colRect.height)/2);
								ent.getComponent<Gravity>()->setFalling(false);

							}
							else if (currentVel.y > 0) {
								std::cout << "correcting movement with y: " << round(colRect.height)/2 << std::endl;
								mov->setVelocity(currentVel.x, currentVel.y - round(colRect.height)/2);
								ent.getComponent<Gravity>()->setFalling(true);

							}
							else{
								std::cout << "correcting movement with y: " << round(colRect.height) << std::endl;
								mov->setVelocity(currentVel.x, currentVel.y + round(colRect.height));

							}
						}

						
						if (mov->getVelocity().x > 0){
							std::cout << "correcting movement with: " << round(colRect.width) << std::endl;
							mov->setVelocity(currentVel.x - round(colRect.width)/2, currentVel.y);
							if (!keybuffer.isEmpty()){
								keybuffer.pop();
							}
						}
						else if(mov->getVelocity().x < 0){
							std::cout << "correcting movement with: " << round(colRect.width) << std::endl;

							mov->setVelocity(currentVel.x + round(colRect.width)/2, currentVel.y);

							if (!keybuffer.isEmpty()){
								keybuffer.pop();
							}
						}
						else
						{
							mov->setVelocity(0, mov->getVelocity().y);
						}

					
				}
				else{
					ent.getComponent<Gravity>()->setFalling(true);
				}
			}
		}
	}
	for (Entity & ent : entities.withComponents<Colidable, Movable>()){
		Colidable::Handle & colHandle = ent.getComponent<Colidable>();
		for (Entity & other : entities.withComponents<Colidable>()){
			if (ent != other){
				Colidable::Handle & otherHandle = other.getComponent<Colidable>();

				if (Collides(ent, other).width > 0 && Collides(ent,other).height > 0){
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


sf::Rect<float> CollisionSystem::Collides(Entity & lhs, Entity & rhs){
	Colidable::Handle lhsColidable = lhs.getComponent<Colidable>();
	Colidable::Handle rhsColidable = rhs.getComponent<Colidable>();
	
	return Collides(lhsColidable, rhsColidable);

}


sf::Rect<float> CollisionSystem::Collides(Colidable::Handle & lhs, Colidable::Handle & rhs){
	sf::Rect<float> rect = lhs->getRect();
	sf::Rect<float> other = rhs->getRect();

	// Rectangles with negative dimensions are allowed, so we must handle them correctly

	// Compute the min and max of the first rectangle on both axes
	float r1MinX = std::min<float>(rect.left, rect.left + rect.width);
	float r1MaxX = std::max<float>(rect.left, rect.left + rect.width);
	float r1MinY = std::min<float>(rect.top, rect.top + rect.height);
	float r1MaxY = std::max<float>(rect.top, rect.top + rect.height);

	// Compute the min and max of the second rectangle on both axes
	float r2MinX = std::min<float>(other.left, other.left + other.width);
	float r2MaxX = std::max<float>(other.left, other.left + other.width);
	float r2MinY = std::min<float>(other.top, other.top + other.height);
	float r2MaxY = std::max<float>(other.top, other.top + other.height);

	// Compute the intersection boundaries
	float interLeft = std::max<float>(r1MinX, r2MinX);
	float interTop = std::max<float>(r1MinY, r2MinY);
	float interRight = std::min<float>(r1MaxX, r2MaxX);
	float interBottom = std::min<float>(r1MaxY, r2MaxY);

	// If the intersection is valid (positive non zero area), then there is an intersection
	if ((interLeft < interRight) && (interTop < interBottom))
	{
		return sf::Rect<float>(interTop, interLeft, interRight - interLeft, interBottom - interTop);
	}
	else
	{
		return sf::Rect<float>(0,0,0,0);
	}
}

CollisionSystem::~CollisionSystem()
{
}
