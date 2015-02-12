#include "MapLoader.hpp"

MapLoader* MapLoader::Instance = nullptr;

MapLoader * MapLoader::createInstance(EntityManager & manager){
	if (!Instance){
		Instance = new MapLoader(manager);
	}
	return get();
}

MapLoader * MapLoader::get(){
	assert(Instance && "Instance should be created!");
	return Instance;
}


MapLoader::MapLoader(EntityManager & manager) : factory(EntityFactory::get(manager))
{
}


void MapLoader::GenerateLevel(unsigned char level){
	std::stringstream file;
	file << "level" << (int)level << ".dat";
	std::vector<std::vector<std::string>> mapping;
	std::ifstream Level(file.str().c_str());
	std::string layer;
	if (!Level.is_open()){
		std::cout << file.str().c_str();
	}
	while (getline(Level, layer)){
		mapping.push_back(explode(',',layer));
	}
	
	for (int y = 0; y < mapping.size(); y++){
		for (int x = 0; x < mapping[y].size(); x++){
			if (mapping[y][x] != "0"){
				/**
				* \Todo: rectangle algoritme -> iterating through mapping vector in search of 
				*		 4 consecutive corners creating biggest possible rectangle minimalizing entities
				*/
				factory->CreateTile(sf::Vector2f(x * 32, y * 32), sf::Vector2f(32, 32));
				

			}
		}
	}
}




std::vector<std::string> MapLoader::explode(char delimeter, std::string subject){
	std::string next;
	std::vector<std::string> result;
	for (std::string::const_iterator it = subject.begin(); it != subject.end(); it++) {
		if (*it == delimeter) {
			if (!next.empty()) {
				result.push_back(next);
				next.clear();
			}
		}
		else {
			next += *it;
		}
	}
	if (!next.empty())
		result.push_back(next);
	return result;
}


MapLoader::~MapLoader()
{
}
