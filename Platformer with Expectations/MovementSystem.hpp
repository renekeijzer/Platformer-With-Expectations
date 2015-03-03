#pragma once
#include <cmath>
#include <stack>

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"
#include "Events.hpp"
class MovementSystem : public System<MovementSystem>, public Receiver<MovementSystem>
{
public:
	MovementSystem(double intr) : interval(intr){}
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	sf::Vector2f calculateIdleMovement(sf::Vector2f speed);
	void receive(const CollisionEvent & event);
	~MovementSystem();
private:

	void handleCollisions(EntityManager & entities);
	void updateCollision(Entity & id);
	void updateGravity(Entity & id);
	void updatePosition(Entity & id);

	std::stack<std::pair<EntityId, EntityId>> colidedEntities;
	double elaspedTime = 100; ///Dirty delta time fix
	double interval;
};

