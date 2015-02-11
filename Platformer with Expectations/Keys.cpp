#include "Keys.hpp"


Keys::Keys()
{
}


Keys::~Keys()
{
}

sf::Keyboard::Key Keys::getNext(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
		return sf::Keyboard::Key::W;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
		return sf::Keyboard::Key::A;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
		return sf::Keyboard::Key::S;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
		return sf::Keyboard::Key::D;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
		return sf::Keyboard::Key::Space;
	}
}
