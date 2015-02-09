#include "RenderSystem.hpp"

void RenderSystem::configure(EventManager & event){
}


void RenderSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity ent : entities.withComponents<Renderable>()){
		Renderable::Handle & render = ent.getComponent<Renderable>();

		if (Movable::Handle & mov = ent.getComponent<Movable>()){
			render->shape->setPosition(mov->getPosition());
		}


		target.draw(*render->shape.get());
	}
}