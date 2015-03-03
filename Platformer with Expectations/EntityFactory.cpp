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

	player.addComponent<Focussable>(1, true);
	player.addComponent<Movable>(position.x, position.y, 0,0);
	player.addComponent<Flag>("Player");
	Movable::Handle & mov = player.getComponent<Movable>();
	mov->setMaxVelocity(sf::Vector2f(5, 5));
	mov->setSpeed(sf::Vector2f(0.1, 0.1));
	
	player.addComponent<UserControlable>();
	
	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(sf::Vector2f(32,32)));
	shape->setFillColor(sf::Color::White);
	shape->setPosition(position);
    player.addComponent<Renderable>(std::move(shape));
	player.addComponent<Gravity>(0.1);

	sf::Rect<float> cRect(position, sf::Vector2f(32,32));
	player.addComponent<Colidable>(cRect);
}

void EntityFactory::CreateTile(sf::Vector2f pos, sf::Vector2f size){
	Entity ent = manager.createEntity();

	sf::Rect<float> cRect(pos, size);
	ent.addComponent<Colidable>(cRect);
	ent.addComponent<Flag>("Tile");
		
	std::unique_ptr<sf::Shape> shape(new sf::RectangleShape(size));
	shape->setPosition(pos);
	shape->setFillColor(sf::Color::Blue);
	ent.addComponent<Renderable>(std::move(shape));




}

