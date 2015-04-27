#pragma once
#include <cmath>
#include <stack>
#include <queue>
#include <SFML\Graphics.hpp>

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"
#include "Events.hpp"
#include "Keymap.hpp"
#include "Keybuffer.hpp"

class MovementSystem : public System<MovementSystem>, public Receiver<MovementSystem>
{
public:
	MovementSystem(double intr, Keybuffer<KeyMap> & buf) : System(intr), keybuffer(buf)  {  }
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	sf::Vector2f calculateIdleMovement(sf::Vector2f speed);
	void receive(const CollisionEvent & event);
	~MovementSystem();
private:

	void updateCollision(Entity & id);
	void updateGravity(Entity & id);
	void updatePosition(Entity & id);
	void updateMovement(Entity & id);

	std::stack<std::pair<EntityId, EntityId>> colidedEntities;
	Keybuffer<KeyMap> & keybuffer;

};

