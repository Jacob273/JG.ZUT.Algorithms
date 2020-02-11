#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include "List.h"
#include "BinaryHeap.h"
#include "Node.h"
#include "Timer.h"
#include "RandomNumbersGenerator.h"

int main()
{
	RandomNumbersGenerator::Initialize(0, 1000000);
	BinaryHeap<Node<int>>* heap = new BinaryHeap<Node<int>>();
	const int MAX_ORDER = 6;


	for (int i = 0; i < MAX_ORDER; i++)
	{
		const int n = std::pow(10, i);

		Timer::Start();
		for (int j = 0; j < n; j++)
		{
			int randomNumber = RandomNumbersGenerator::GetNext();
			Node<int>* newNode = new Node<int>(randomNumber);
			heap->Insert(newNode);
		}
		Timer::Stop();
		std::cout << "phase " << i << " [[" << n << "]] insertion time:  " << Timer::TimeSpent() << std::endl;

		Timer::Start();
		for (int j = 0; j < n; j++)
		{
			heap->RemoveRoot();
		}
		Timer::Stop();
		std::cout << "phase " << i << " [[" << n << "]] root deletion time: " << Timer::TimeSpent() << std::endl;
	}


	Timer::Stop();
	delete heap;

}