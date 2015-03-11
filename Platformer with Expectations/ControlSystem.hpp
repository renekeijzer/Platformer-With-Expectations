#pragma once

#include <cmath>

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"
#include "types.h"
#include "Keybuffer.hpp"
#include "Keymap.hpp"


class ControlSystem : public System<ControlSystem>
{
public:
	ControlSystem(double intr, Keybuffer & key, Keymap & keymap) 
		: System<ControlSystem>(intr), keybuffer(key), keys(keymap){  }
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	~ControlSystem();
private:
	Keymap & keys;
	Keybuffer &keybuffer;
};

