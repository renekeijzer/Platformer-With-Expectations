#include "EntityFactory.hpp"


EntityFactory * EntityFactory::Instance = nullptr;

EntityFactory* EntityFactory::get(EntityManager& manager){
	if (!Instance){
		Instance = new EntityFactory(manager);
	}
	return Instance;
}
void EntityFactory::CreatePlayer(sf::Vector2f position){
	Entity player = manager.createEntity();
	player.addComponent<Movable>(position.x, position.y, 0,0);
	player.addComponent<UserControlable>();
	player.addComponent<Renderable>(sf::RectangleShape(sf::Vector2f(32,32)));
	Renderable::Handle & ren = player.getComponent<Renderable>();
	ren->shape.setPosition(position);
	ren->shape.setFillColor(sf::Color::White);

	sf::Rect<float> cRect(position, sf::Vector2f(32,32));
	player.addComponent<Colidable>(cRect);
}

