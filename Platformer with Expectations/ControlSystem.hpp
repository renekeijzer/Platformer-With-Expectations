#pragma once
#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"

class ControlSystem : public System<ControlSystem>
{
public:
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	~ControlSystem();
};

