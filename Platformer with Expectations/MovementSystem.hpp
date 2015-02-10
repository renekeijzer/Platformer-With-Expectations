#pragma once
#include <cmath>

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"
class MovementSystem : public System<MovementSystem>
{
public:
	MovementSystem(double intr) : interval(intr){}
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	sf::Vector2f calculateIdleMovement(sf::Vector2f speed);
	~MovementSystem();
private:
	double elaspedTime = 100; ///Dirty delta time fix
	double interval;
};

