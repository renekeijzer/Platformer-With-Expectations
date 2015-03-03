
#include "TheGrid\Component.hpp"
#include "types.h"

struct Flag : public Component<Flag>{
public:
	Flag(PWE::EntityTypes nm) : type(nm){}
	PWE::EntityTypes type;




};