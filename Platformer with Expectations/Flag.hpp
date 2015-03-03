
#include "TheGrid\Component.hpp"

struct Flag : public Component<Flag>{
public:
	Flag(std::string nm) : name(nm){}
	std::string name;


};