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
		if (rect.second.x > 0 && rect.second.y > 0){
			factory->CreateTile(sf::Vector2f(rect.first.x * 32, rect.first.y * 32), sf::Vector2f(rect.second.x * 32, rect.second.y * 32));
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
	if (mapping.at(x) == "0")
	{
		return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
	}


	int tempWidth = x % width;
	int tempheight = x / width;


	while (tempWidth <= width){
		size_t index = tempheight * width + tempWidth;
		
		if (index >= mapping.size()){ break; }
		if (mapping.at(index) != "0"){
			tempWidth++;
		}
		else
		{ 
			break; 
		}
	}

	while (tempheight <= height){
		size_t index = tempheight * width + x % width;
	
		if (index >= mapping.size()){ break; }
		if (mapping.at(index) != "0"){
			tempheight++;
		}
		else{
			break;
		}
	}

	if (tempheight <= 1 && tempWidth <= 1)
	{
		return std::pair<sf::Vector2f, sf::Vector2f>(position, sf::Vector2f(1,1));
	}

	size.x = 1;
	size.y = 1;

	for (int iY = x / width; iY < tempheight - x/width; iY++){
		for (int iX = x % width; iX < tempWidth - x%width; iX++){
			size_t index = iY * width + iX;
			if (index >= mapping.size()){ break; }
			
			if (mapping.at(index) != "0"){
				size.x = iX + 1;
				size.y = iY + 1;
				checkedPositions.push_back(iY * width + iX);
			}
			else
			{
			
				checkedPositions.clear();
				return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
			}
		}	
	}
	return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
}

MapLoader::~MapLoader()
{
}
