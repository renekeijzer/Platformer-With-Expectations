#pragma once
#include <bitset>
namespace PWE{ 
	typedef std::bitset<4> CollisionMap;
	enum EntityTypes
	{
		Player,
		Tile,
	};

	enum PlayerAction{
		strafeRight,
		strafeLeft,
		jump,
		duck,
	};

	
}