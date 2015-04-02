#pragma once
#include "TheGrid\EventManager.hpp"
#include "TheGrid\EntityManager.hpp"

#include "Keymap.hpp"
#include "types.h"
#include "Components.hpp"
#include "Events.hpp"
#include "Keybuffer.hpp"

#include <algorithm>
#include <queue>


class CollisionSystem : public System<CollisionSystem>
{
public:
	CollisionSystem(double intr, Keybuffer<KeyMap> & buffer) : System(intr), keybuffer(buffer){ std::cout << "bufferSize: " << keybuffer.size() << "\r\n"; }
	void update(EntityManager & entities, EventManager & events, double dt) override;
	void configure(EventManager & events) override;
	bool Collides(Entity & lhs, Entity & rhs);
	bool Collides(Colidable::Handle & lhs, Colidable::Handle & rhs);

	~CollisionSystem();
private:

	Colidable::Handle predicate(Entity & ent);
	Keybuffer<KeyMap> & keybuffer;
};

