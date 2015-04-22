#include "ControlSystem.hpp"

void ControlSystem::configure(EventManager & event){
}


void ControlSystem::update(EntityManager & entities, EventManager & events, double dt){
	for(auto key : keys->getMap())
	{
		if (sf::Keyboard::isKeyPressed(key.first)){
			if (checkPossibleMovement(key.first, entities)){
				keybuffer.add(key);
			}
		}
	}
}
bool ControlSystem::checkPossibleMovement(sf::Keyboard::Key key, EntityManager &entities){
	for (auto & ent : entities.withComponents<UserControlable>()){
		if (sf::Keyboard::Key::A == key && !ent.getComponent<Colidable>()->getCollision(Colidable::CollisionSide::left)){
			return true;
		}
		if (sf::Keyboard::Key::D == key && !ent.getComponent<Colidable>()->getCollision(Colidable::CollisionSide::right)){
			return true;
		}
		return false;

	}

}



ControlSystem::~ControlSystem()
{
}
