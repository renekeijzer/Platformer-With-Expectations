#include "ControlSystem.hpp"

void ControlSystem::configure(EventManager & event){
}


void ControlSystem::update(EntityManager & entities, EventManager & events, double dt){
	for(auto key : keys->getMap())
	{
		if (sf::Keyboard::isKeyPressed(key->first)){
			keybuffer->push(key);
		}
	}

	

}
ControlSystem::~ControlSystem()
{
}
