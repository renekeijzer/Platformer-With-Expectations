#include "TheGrid\Component.hpp"
struct Gravity : Component<Gravity>{
public:
	Gravity(float fs) : fallingSpeed(fs), falling(true){}
	void setFalling(bool fa){ falling = fa; }
	float getFalling(){ return fallingSpeed; }
	bool isFalling(){ return falling; }


private:
	float fallingSpeed;
	bool falling;

};