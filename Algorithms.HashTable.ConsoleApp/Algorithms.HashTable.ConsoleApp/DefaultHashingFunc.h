#pragma once

#include "Settings.h"

// Default hash function class
template <typename TKey>
class DefaultHashingFunc
{
public:

	unsigned long operator()(TKey& key)
	{
		//Making conversion form K type to unsigned long type
		return static_cast<unsigned long>(key) % Settings::GlobalHashTableSize;
	}
};

