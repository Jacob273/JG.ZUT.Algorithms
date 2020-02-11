#pragma once
#include "iostream"


class RandomNumbersGenerator
{
public:

	static bool _isInitialized;

	RandomNumbersGenerator(int size);
	static void Initialize(int from, int to);
	static void Release();
	static int GetNext();
	static void PrintGeneratedNumbers();

private:
	static int _currentIndex;
	static int _hashTblSize;
	static int* _arrOfRandoms;

	static void Fill(int*& arr, int from, int to);
	static void Shuffle(int*& arr, int size);
};

