#include "RandomNumbersGenerator.h"

int RandomNumbersGenerator::_currentIndex = 0;
int* RandomNumbersGenerator::_arrOfRandoms = NULL;
bool RandomNumbersGenerator::_isInitialized = false;
int RandomNumbersGenerator::_hashTblSize = 0;

RandomNumbersGenerator::RandomNumbersGenerator(int size)
{
	Initialize(0, size);
}

void RandomNumbersGenerator::Initialize(int from, int to)
{
	if (!_isInitialized)
	{
		_hashTblSize = to - from + 1;
		_arrOfRandoms = new int[_hashTblSize];
		Fill(_arrOfRandoms, from, to);
		Shuffle(_arrOfRandoms, _hashTblSize);
		_isInitialized = true;
	}
}

void RandomNumbersGenerator::Release()
{
	if (_isInitialized)
	{
		_currentIndex = 0;
		_hashTblSize = 0;
		_isInitialized = false;
		delete[] _arrOfRandoms;
		_arrOfRandoms = NULL;
	}
}

int RandomNumbersGenerator::GetNext()
{
	if (!_isInitialized)
	{
		throw "Random numbers generator must be initialized";
	}

	if (_currentIndex < _hashTblSize)
	{
		return _arrOfRandoms[_currentIndex++];
	}
	else
	{
		throw "All unique ids were used";
	}
}

void RandomNumbersGenerator::PrintGeneratedNumbers()
{
	for (int i = 0; i < _hashTblSize; i++)
	{
		std::cout << " " << _arrOfRandoms[i] << " ";
	}
}

void RandomNumbersGenerator::Fill(int*& arr, int from, int to)
{
	int i = 0;
	int counter = 0;
	for (int j = from; j <= to; j++)
	{
		arr[i++] = j;
		counter++;
	}
}

void RandomNumbersGenerator::Shuffle(int*& arr, int size)
{
	int i, j, temp;
	for (i = size - 1; i >= 0; i--)
	{
		j = rand() % (i + 1);
		temp = arr[j];
		arr[j] = arr[i];
		arr[i] = temp;
	}
}