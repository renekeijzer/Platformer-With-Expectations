#pragma once
#include "TheGrid\Event.hpp"

struct CollisionEvent : Event<CollisionEvent>{
	CollisionEvent(Entity l, Entity r) : left(l),right(r){}
public:
	Entity left;
	Entity right;
};