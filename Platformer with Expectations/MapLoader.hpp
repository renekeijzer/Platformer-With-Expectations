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
	typedef std::pair<sf::Vector2f, sf::Vector2f> rectangle; 
class MappingGrid{
	public:
		MappingGrid();
		MappingGrid(int x, int y);

		void addLine(std::vector<std::string> line);
		std::vector<std::pair<sf::Vector2f, sf::Vector2f>> Calculate();

	private:
		std::pair<sf::Vector2f, sf::Vector2f> getRectangleat(int x);
		std::vector<std::string> mapping;
		std::vector<int> checkedPositions;
		int width;
		int height;
	};


	std::vector<std::string> explode(char delimiter, std::string subject);

	static MapLoader * Instance;
	EntityFactory * factory = nullptr;
	std::vector<uint32_t> currentLevel;
};

