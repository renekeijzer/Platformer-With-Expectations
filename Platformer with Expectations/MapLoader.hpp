#pragma once
#include "EntityFactory.hpp"

#include "TheGrid\EntityManager.hpp"

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

class MapLoader
{
public:
	static MapLoader * createInstance(EntityManager & manager);
	static MapLoader * get();
	void GenerateLevel(unsigned char level);
	MapLoader(EntityManager & entityManager);
	~MapLoader();
private:
	std::vector<std::string> explode(char delimiter, std::string subject);

	static MapLoader * Instance;
	EntityFactory * factory = nullptr;
	std::vector<uint32_t> currentLevel;
};

