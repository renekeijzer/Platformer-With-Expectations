#pragma once

#include <cmath>

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"

class ControlSystem : public System<ControlSystem>
{
public:
	ControlSystem(double intr) : interval(intr){}
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	~ControlSystem();
private:
	double elapsedTime = 100; /// Dirty delta time fix
	double interval;
};

