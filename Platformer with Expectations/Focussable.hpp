#include "TheGrid\Component.hpp"

struct Focussable : public Component<Focussable>{
public:
	Focussable(int p = 0 ,bool f = false) :focussed(f), priority(p){}
	int priority;
	bool focussed = false;

};