#pragma once
#include "TheGrid\EventManager.hpp"
#include "TheGrid\EntityManager.hpp"

#include "Keymap.hpp"
#include "Components.hpp"
#include "Events.hpp"

#include <algorithm>
#include <queue>

typedef std::queue<KeyMap *> Keybuffer;


class CollisionSystem : public System<CollisionSystem>
{
public:
	CollisionSystem(Keybuffer & buffer);
	void update(EntityManager & entities, EventManager & events, double dt);
	
	bool Collides(Entity & lhs, Entity & rhs);
	bool Collides(Colidable::Handle & lhs, Colidable::Handle & rhs);

	~CollisionSystem();
private:
	Keybuffer & buffer;
	Colidable::Handle predicate(Entity & ent);
};

