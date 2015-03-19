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
	for (Entity ent : entities.withComponents<Focussable>()){
		Focussable::Handle & focus = ent.getComponent<Focussable>();
		Renderable::Handle & render = ent.getComponent<Renderable>();
		if (focus->focussed){
			sf::View view = target.getView();
			view.setCenter(sf::Vector2f(render->shape->getPosition().x, render->shape->getPosition().y));
			target.setView(view);
		}
	}

}