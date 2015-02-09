#pragma once 
#include <SFML\Graphics.hpp>

#include "TheGrid\Component.hpp"

struct Renderable : public Component<Renderable>{
	Renderable(sf::Shape & sh) : shape(sh){}
	
	sf::Shape & shape;
};