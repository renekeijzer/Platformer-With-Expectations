#pragma once
#include <string>
#include <vector>
#include <SFML\Graphics.hpp>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <fstream>
#include <iostream>

#include "FileNotfound.h"
#include "types.h"
#include "TheGrid\NonCopyable.hpp"
typedef std::pair<sf::Keyboard::Key, PWE::PlayerAction> KeyMap;

class Keymap :
	public NonCopyable
{
public:
	Keymap(std::string fileLocation) : location(fileLocation){}
	void load();
	PWE::PlayerAction getAction(sf::Keyboard::Key key);
	sf::Keyboard::Key getKey(PWE::PlayerAction action);

	std::vector<KeyMap> & getMap(){ return mapping; }
	~Keymap();
private: 
	KeyMap createPair(sf::Keyboard::Key, PWE::PlayerAction);
	KeyMap createPair(std::string, std::string);
	std::vector<std::string> explode(char delimeter, std::string subject);
	std::string location;
	std::vector<KeyMap> mapping;
	bool loaded = false;
};

