#pragma once
#include "TheGrid\EventManager.hpp"
#include "TheGrid\EntityManager.hpp"

#include "Components.hpp"
#include "Events.hpp"

#include <algorithm>

class CollisionSystem : public System<CollisionSystem>
{
public:
	CollisionSystem();
	void update(EntityManager & entities, EventManager & events, double dt);
	
	bool Collides(sf::Rect<float> rect, sf::Rect<float> other);

	~CollisionSystem();
};

