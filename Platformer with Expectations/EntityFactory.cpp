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
	Movable::Handle & mov = player.getComponent<Movable>();
	mov->setMaxVelocity(sf::Vector2f(15, 15));
	mov->setSpeed(sf::Vector2f(2, 2));

	player.addComponent<UserControlable>();
	
	
	
	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(sf::Vector2f(32,32)));
	shape->setFillColor(sf::Color::White);
	shape->setPosition(position);
     player.addComponent<Renderable>(std::move(shape));
	
	
	
	sf::Rect<float> cRect(position, sf::Vector2f(32,32));
	player.addComponent<Colidable>(cRect);
}

