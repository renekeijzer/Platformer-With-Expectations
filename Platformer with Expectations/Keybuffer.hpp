#pragma once
#include <vector>

#include "TheGrid\NonCopyable.hpp"
template <typename T>
class Keybuffer :
	public NonCopyable
{
public:
	Keybuffer(){}
	void add(T item){
		container.push_back(item);
	}

	T pop(){
		assert(!container.empty());
		T rtnVal = container.front();
		container.erase(container.begin());
		return rtnVal;
	}
	T peek(){
		assert(!container.empty());
		return container.front();
	}
	
	size_t size(){
		return container.size();
	}
	bool isEmpty(){
		return container.empty();
	}
	~Keybuffer(){}
private:
	std::vector<T> container;
};

