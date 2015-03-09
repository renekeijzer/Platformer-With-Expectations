#pragma once
#include <queue>
#include <SFML\Graphics.hpp>
#include "Keymap.hpp"

class Keybuffer : public std::queue<Keymap::KeyMap>
{
public:
	Keybuffer();
	
	~Keybuffer();
};

