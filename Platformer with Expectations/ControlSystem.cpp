#include "ControlSystem.hpp"

void ControlSystem::configure(EventManager & event){
	//actions.push_back({ sf::Keyboard::Key::W, 0, -1 });
	//actions.push_back({ sf::Keyboard::Key::A, -1, 0 });
	//actions.push_back({ sf::Keyboard::Key::S, 0, 1 });
	//actions.push_back({ sf::Keyboard::Key::D, 1, 0 });
	
}


void ControlSystem::update(EntityManager & entities, EventManager & events, double dt){
	if (elapsedTime + interval > dt){
		return;
	}
		for (Entity ent : entities.withComponents<UserControlable>()){
			Movable::Handle & mov = ent.getComponent<Movable>();
			sf::Vector2f Velocity = mov->getVelocity();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
				Velocity.x = (Velocity.x > mov->getMaxVelocity().x * -1 ? Velocity.x + mov->speed.x * -1 : mov->getMaxVelocity().x*-1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
				Velocity.x = (Velocity.x > mov->getMaxVelocity().x * 1 ? Velocity.x + mov->speed.x * 1 : mov->getMaxVelocity().x);
			}
			else
			{
				if (Velocity.x > 0.1){
					Velocity.x -= 0.1;
				}
				else if(Velocity.x < -0.1){
					Velocity.x += 0.1;
				}else{ 
					Velocity.x = 0; 
				}
			}
			mov->setVelocity(Velocity);
		}

		elapsedTime = dt;
	
}
ControlSystem::~ControlSystem()
{
}
