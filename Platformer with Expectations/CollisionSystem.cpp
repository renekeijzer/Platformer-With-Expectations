#include "CollisionSystem.hpp"
#include "types.h"

CollisionSystem::CollisionSystem()
{
}


void CollisionSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity & ent : entities.withComponents<Colidable, Movable>()){
		Colidable::Handle & colHandle = ent.getComponent<Colidable>();
		for (Entity & other : entities.withComponents<Colidable>()){
			if (ent != other){
				Colidable::Handle & otherHandle = other.getComponent<Colidable>();

				sf::Rect<float> entRect = colHandle->getRect();
				sf::Rect<float> otherRect = otherHandle->getRect();

				if (Collides(entRect, otherRect)){
					events.emit<CollisionEvent>(ent, other);
				}
			}
		}
	}
}



bool CollisionSystem::Collides(sf::Rect<float> rect, sf::Rect<float> other){
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
		return true;
	}
	else
	{
		return false;
	}
}


CollisionSystem::~CollisionSystem()
{
}
