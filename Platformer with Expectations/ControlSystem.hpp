#pragma once

#include <cmath>

#include "TheGrid\SystemManager.hpp"
#include "TheGrid\EntityManager.hpp"
#include "TheGrid\EventManager.hpp"

#include "Components.hpp"
#include "types.h"
#include "Keymap.hpp"
#include "Keybuffer.hpp"

#include <queue>

class ControlSystem : public System<ControlSystem>
{
public:
	ControlSystem(double intr, Keybuffer<KeyMap> & key, Keymap * keymap)
		: System<ControlSystem>(intr), keybuffer(key), keys(keymap){  }
	void configure(EventManager & events) override;
	void update(EntityManager & entities, EventManager & events, double dt);
	bool checkPossibleMovement(sf::Keyboard::Key key, EntityManager & entities); 
	~ControlSystem();
private:
	Keymap * keys;
	Keybuffer<KeyMap> & keybuffer;
};

