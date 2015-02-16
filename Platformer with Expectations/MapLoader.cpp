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
			else{ std::cout << "skipping: " << i << std::endl; }
		}
		
	}
	return Rectangles;
}

std::pair<sf::Vector2f, sf::Vector2f> MapLoader::MappingGrid::getRectangleat(int x){
	sf::Vector2f position(x % width, x / width);
	sf::Vector2f size(0, 0);

	int tempWidth = x % width;
	int tempheight = x / width;
	std::cout << "Prempemptive check for: "<< tempWidth << " - " << tempheight <<std::endl;

	while (tempWidth <= width){
		size_t index = tempheight * width + tempWidth;
		
		if (index >= mapping.size()){ break; }
		std::cout << "Checking x:";
		std::cout << index;
		
		if (mapping.at(index) != "0"){
			std::cout << " True" << std::endl;
			tempWidth++;
		}
		else
		{ 
			std::cout << " False" << std::endl;
			break; 
		}
	}

	while (tempheight <= height){
		size_t index = tempheight * width + x % width;
	
		if (index >= mapping.size()){ break; }
		std::cout << "Checking y:";
		std::cout << index << "size : " << mapping.size();

		if (mapping.at(index) != "0"){
			std::cout << " True" << std::endl;
			tempheight++;
		}
		else{
			std::cout << " False" << std::endl;
			break;
		}
	}

	std::cout << "=============" << std::endl <<std::endl;

	if (tempheight == 0 || tempWidth == 0)
	{
		return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
	}

	std::cout << "Expected bounds are: " << tempWidth - x % width << " - " << tempheight - x / width << "\r\n";
	for (int iY = x / width; iY < tempheight - x/width; iY++){
		for (int iX = x % width; iX < tempWidth - x%width; iX++){
			
			std::cout << "Checking position: " << "x " << iX << "-y" << iY << "\r\n";
			
			if (mapping.at(iY * width + iX) == "0"){
				std::cout << "False\r\nAdded an " << iY * width + iX << " as Checked\r\n";
				checkedPositions.push_back(iY * width + iX);
				break;
			}
			else
			{
				std::cout << "true\r\nAdded an " << iY * width + iX << " as Checked\r\n";
				checkedPositions.push_back(iY * width + iX);
				size.x = iX + 1;
				size.y = iY + 1;
			}
		}	
	}

	
	std::cout << " << Created vector: {pos : " << position.x << " - " << position.y << ", size: " << size.x << " - " << size.y << "}" << std::endl << std::endl;
	return std::pair<sf::Vector2f, sf::Vector2f>(position, size);
}

MapLoader::~MapLoader()
{
}
