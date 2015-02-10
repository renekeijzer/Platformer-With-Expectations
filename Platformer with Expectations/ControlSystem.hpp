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
	struct control{
	public:
		sf::Keyboard::Key key;
		float x;
		float y;
	};

	std::vector<control> actions;
	double elapsedTime = 100; /// Dirty delta time fix
	double interval;
};

