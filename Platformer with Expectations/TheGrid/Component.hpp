#pragma once
#include "ComponentHandle.hpp"
#include "BaseComponent.hpp"
template <typename Derived>
struct Component : public BaseComponent{
public:

	typedef ComponentHandle<Derived> Handle;
	virtual std::string toString();
	static Family family();
};

template <typename Derived>
ostream & Component::operator<<(ostream & ost, Component x){
	return ost << x.toString();
}

template <typename C>
BaseComponent::Family Component<C>::family(){
	static Family family = familyCounter++;
	return family;
}