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
	std::ifstream Level(file.str().c_str());
	std::string layer;
	MappingGrid grid;
	if (!Level.is_open()){
		std::cout << file.str().c_str();
	}
	while (getline(Level, layer)){
		grid.addLine(explode(',',layer));
	}
	
	std::vector<rectangle> rects = grid.Calculate();

	for (rectangle rect : rects){

		factory->CreateTile(sf::Vector2f(rect.first.x * 32, rect.first.y * 32), sf::Vector2f(rect.second.x*32, rect.second.y*32));
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



MapLoader::MappingGrid::MappingGrid(){}
MapLoader::MappingGrid::MappingGrid(int x, int y) : width(x), height(y){}

void MapLoader::MappingGrid::addLine(std::vector<std::string> lines){
	width = lines.size();
	for (std::string line : lines){
		mapping.push_back(line);
	}
	height = mapping.size() / width;
}

std::vector<std::pair<sf::Vector2f, sf::Vector2f>> MapLoader::MappingGrid::Calculate(){
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> Rectangles;
	if (width < 1){}
	else{
		
		for (int i = 0; i < mapping.size(); i++){
			if (std::find(checkedPositions.begin(), checkedPositions.end(), i) == checkedPositions.end()){
				Rectangles.push_back(getRectangleat(i));
			}
		}
		
	}
	return Rectangles;
}

std::pair<sf::Vector2f, sf::Vector2f> MapLoader::MappingGrid::getRectangleat(int x){
	sf::Vector2f position(x % width, x / width);
	sf::Vector2f size(0, 0);

	int tempWith = x;
	int tempheight = x;
	std::cout << width << " \r\n";
	while (tempWith < width){
		if (mapping.at(tempWith) != "0"){
			tempWith++;
		}
		else
		{ 
			break; 
		}
	}
	while (tempheight < mapping.size()){
		if (mapping.at(tempheight) != "0" && tempheight/width <= height){
			tempheight += width;
		}
		else{
			break;
		}
		
	}

	if (tempheight - x == 0 || tempWith - x == 0)
	{
		return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
	}

	std::cout << "Expected bounds are: " << tempWith % width << " - " << tempheight / width << "\r\n";
	for (int iY = x; iY < tempheight + x; iY += width){
		size.y++;
		for (int iX = iY; iX < tempWith + iY; iX++){
			std::cout << "Checking position: " << "x " << iX % width << "-y" << iY / width << "\r\n";
			
			if (mapping.at(iX + iY) == "0"){
				std::cout << " << Created vector: {pos : " << position.x << " - " << position.y << ", size: " << size.x << " - " << size.y << "}" << std::endl << std::endl;
				return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
			}
			else
			{
				std::cout << "Added an " << iX << " as Checked\r\n";
				checkedPositions.push_back(iX);
			}

			size.x++;
		}
		
	
	}


	std::cout << " << Created vector: {pos : " << position.x << " - " << position.y << ", size: " << size.x << " - " << size.y << "}" << std::endl << std::endl;
	return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
}

MapLoader::~MapLoader()
{
}
