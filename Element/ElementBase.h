#pragma once
#include <vector>
class ElementBase
{
public:
	ElementBase();
	~ElementBase();
public:
	std::vector<ElementBase> children;
private:

};

