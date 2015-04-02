#include "Keymap.hpp"


void Keymap::load(){
	try{
		if (!loaded){
			std::string configLine;
			std::ifstream config(location);
			if (!config.is_open()){
				throw FileNotFound(location);
			}

			while (getline(config, configLine)){
				auto lines = explode(':', configLine);
				mapping.push_back(createPair(lines[0], lines[1]));
			}
			loaded = true;
		}
	}
	catch (std::exception ex){
		std::cout << ex.what();
	}

}

KeyMap Keymap::createPair(std::string key, std::string action){
	KeyMap pair;
	sf::Keyboard::Key temp = (sf::Keyboard::Key)stoi(key);
	pair.first = temp;
	switch (stoi(action)){
	case 1:
		pair.second = PWE::PlayerAction::strafeLeft;
		break;
	case 2:
		pair.second = PWE::PlayerAction::strafeRight;
		break;
	case 3:
		pair.second = PWE::PlayerAction::jump;
		break;
	case 4:
		pair.second = PWE::PlayerAction::duck;
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	default:
		break;
	}

	return pair;
}
KeyMap Keymap::createPair(sf::Keyboard::Key key, PWE::PlayerAction action){

}

std::vector<std::string> Keymap::explode(char delimeter, std::string subject){
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



Keymap::~Keymap()
{
}
