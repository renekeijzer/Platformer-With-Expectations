#include "RenderSystem.hpp"

void RenderSystem::configure(EventManager & event){
}


void RenderSystem::update(EntityManager & entities, EventManager & events, double dt){
	for (Entity ent : entities.withComponents<Renderable>()){
		Renderable::Handle & render = ent.getComponent<Renderable>();
		target.draw(*render->shape.get());
	}
}