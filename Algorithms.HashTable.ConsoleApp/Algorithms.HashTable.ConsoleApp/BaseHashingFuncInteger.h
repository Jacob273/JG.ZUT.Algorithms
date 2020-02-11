#pragma once

#include "math.h"

class BaseHashingFuncInteger
{
public:
	unsigned long operator()(const int& key) const
	{
		unsigned long res = (key % 1000 + pow(2, key % 10));
		return res % 996;
	}

private:
};