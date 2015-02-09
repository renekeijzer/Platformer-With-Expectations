#pragma once
#include "TheGrid\Component.hpp"

#include <SFML\Graphics.hpp>
struct Movable : Component<Movable>{
public:
	Movable(){}
	Movable(float x, float y) : position(x, y){}
	Movable(float x, float y, float vx, float vy) : position(x, y), velocity(vx, vy){}
	Movable(sf::Vector2f pos, sf::Vector2f vel) : position(pos), velocity(vel){}

	sf::Vector2f getPosition(){ return position; }
	sf::Vector2f getVelocity(){ return velocity; }

	void setVelocity(sf::Vector2f vel){ velocity = vel; }
	void setPosition(sf::Vector2f pos){ position = pos; }

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	

};