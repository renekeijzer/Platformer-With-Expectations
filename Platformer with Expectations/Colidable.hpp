#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>

#include "TheGrid\Component.hpp"
#include "types.h"
struct Colidable : public Component<Colidable>
{
	enum CollisionSide{
		left = 0,
		right = 1,
		up = 2, 
		down = 3,
	};

	Colidable(){}
	Colidable(sf::Rect<float> pos) : collisionRect(pos){}
	Colidable(sf::Vector2f position, sf::Vector2f dim) : collisionRect(position, dim){}

	sf::Rect<float> getRect(){ return collisionRect; }
	float getWidth(){ return collisionRect.width; }
	float getHeight(){ return collisionRect.height; }

	sf::Vector2f getPosition(){ return sf::Vector2f(collisionRect.left, collisionRect.top); }
	
	void setPosition(sf::Vector2f pos){
		collisionRect.top = pos.y;
		collisionRect.left = pos.x;
	}

	void setPosition(float x, float y){
		collisionRect.top = y;
		collisionRect.left = x;
	}

	void setCollision(bool col, CollisionSide side){
		map[side] = col;
	}

	bool getCollision(CollisionSide side){
		return map.at(side);
	}

	PWE::CollisionMap getCollision(){
		return map;
	}

	std::string toString() override {
		std::stringstream output;
		output << "({" << collisionRect.left << ", " << collisionRect.top << "), "<< collisionRect.width << ", " << collisionRect.height << "}";
		return output.str();
	}

	bool operator==(Colidable & other){
		return other.collisionRect == collisionRect;
	}
	bool operator !=(Colidable & other){
		return other.collisionRect != collisionRect;
	}


private:
	sf::Rect<float> collisionRect;
	PWE::CollisionMap map = 0;
};
