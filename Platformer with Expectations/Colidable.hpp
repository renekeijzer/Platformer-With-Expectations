#pragma once
#include <SFML\Graphics.hpp>
#include "TheGrid\Component.hpp"
struct Colidable : public Component<Colidable>
{
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

	void setCollision(std::bitset<4> cMap){
		map = cMap;
	}

	bool getCollisionX(){
		return map.at(0);
	}

	bool getCollisionXY(){
		return map.at(1);
	}

	bool getCollisionYX(){
		return map.at(2);
	}

	bool getCollisionY(){
		return map.at(3);
	}

	PWE::CollisionMap getCollision(){
		return map;
	}


private:
	sf::Rect<float> collisionRect;
	PWE::CollisionMap map = 0;
};