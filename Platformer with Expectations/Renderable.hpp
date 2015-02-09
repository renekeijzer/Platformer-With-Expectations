#pragma once 
#include <SFML\Graphics.hpp>

#include "TheGrid\Component.hpp"

struct Renderable : public Component<Renderable>{
	explicit Renderable(std::unique_ptr<sf::Shape> &shape) : shape(std::move(shape)) {}

	std::unique_ptr<sf::Shape> shape;
};