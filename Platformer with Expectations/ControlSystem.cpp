#include "ControlSystem.hpp"

void ControlSystem::configure(EventManager & event){
}


void ControlSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity ent : entities.withComponents<UserControlable>()){
		std::cout << "found player\r\n";
	}
}
ControlSystem::~ControlSystem()
{
}
