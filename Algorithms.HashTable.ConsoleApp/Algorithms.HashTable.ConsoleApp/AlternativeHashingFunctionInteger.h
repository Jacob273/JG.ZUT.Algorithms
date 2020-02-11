#pragma once

#include "math.h"

class AlternativeHashingFunctionInteger
{
public:
	unsigned long operator()(const int& key) const
	{
		unsigned long res = (3 * key) % 19 + 1;
		return res;
	}

private:
};