#pragma once
class Settings
{
public:
	static const int GlobalHashTableSize = 1000;

	enum Strategy
	{
		//It assumes that every node is a linked list..if collision occurs, LinkedList will be expanded!
		Chaining = 1,
		//It assumes that whenever collision takes place, we try to find a place as close as possible to the given node
		LinearProbing = 2,
		DoubleHashing = 3
	};
};

