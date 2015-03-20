#pragma once
#include "TheGrid\EventManager.hpp"
#include "TheGrid\EntityManager.hpp"

#include "Keymap.hpp"
#include "types.h"
#include "Components.hpp"
#include "Events.hpp"

#include <algorithm>
#include <queue>

typedef std::queue<KeyMap *> Keybuffer;

class CollisionSystem : public System<CollisionSystem>
{
public:
	CollisionSystem(double intr, Keybuffer * buffer) : System(intr), keybuffer(buffer){ std::cout << "bufferSize: " << keybuffer->size() << "\r\n"; }
	void update(EntityManager & entities, EventManager & events, double dt);
	void configure(EventManager & events) override;
	bool Collides(Entity & lhs, Entity & rhs);
	bool Collides(Colidable::Handle & lhs, Colidable::Handle & rhs);

	~CollisionSystem();
private:

	Colidable::Handle predicate(Entity & ent);
	Keybuffer * keybuffer;
};

