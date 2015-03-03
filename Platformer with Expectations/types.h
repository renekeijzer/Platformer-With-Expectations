#pragma once
#include <bitset>
namespace PWE{ 
	typedef std::bitset<4> CollisionMap;
	enum EntityTypes
	{
		Player,
		Tile,
	};
}