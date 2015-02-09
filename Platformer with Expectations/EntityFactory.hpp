#pragma once
#include <SFML\Graphics.hpp>
#include "TheGrid\EntityManager.hpp"
#include "Components.hpp"
class EntityFactory
{
public:
	static EntityFactory* get(EntityManager & manager);
	void CreatePlayer(sf::Vector2f position);
	
private:
	static EntityFactory * Instance;
	EntityManager & manager;
	EntityFactory(EntityManager & man) : manager(man){}
};

