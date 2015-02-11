#pragma once
#include <SFML\Graphics.hpp>
class Keys
{
public:
	Keys();
	~Keys();
	static sf::Keyboard::Key getNext();

};

