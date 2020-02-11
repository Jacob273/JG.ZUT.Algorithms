#define _CRT_SECURE_NO_WARNINGS 1

#include "iostream"
#include "List.h"
#include "Timer.h"
#include "RandomNumbersGenerator.h"
#include "windows.h"
#include "DefaultHashingFunc.h"
#include "HashTable.h"
#include "TblNode.h"
#include <string>
#include "BaseHashingFuncInteger.h"
#include "FileReader.h"
#include "Settings.h"
#include "AlternativeHashingFunctionInteger.h"

using namespace JG_Collections;

int main()
{
	Timer::Start();
	FileReader::ReadFile("C:\\ALG2\\inlab05.txt");
	RandomNumbersGenerator::Release();
	RandomNumbersGenerator::Initialize(20000, 40000);

	//Test 1 start: Hashtable with Linear probing collision solving  //////////////////////////////////////////////////////////////
	HashTable<int, std::string, BaseHashingFuncInteger>* hashTblLinear = new HashTable<int, std::string, BaseHashingFuncInteger>(Settings::LinearProbing);

	hashTblLinear->TryRemove(FileReader::k1);
	hashTblLinear->TryInsert(FileReader::k1, "A");

	hashTblLinear->Print(0, 100);

	for (int i = 0; i < FileReader::elementsToBeGenerated; i++)
	{
		int generatedNumber = RandomNumbersGenerator::GetNext();
		hashTblLinear->TryInsert(generatedNumber, "A");
	}

	hashTblLinear->Print(0, 100);
	hashTblLinear->TryInsert(FileReader::k2, "B");
	hashTblLinear->TryInsert(FileReader::k3, "C");
	hashTblLinear->TryInsert(FileReader::k4, "D");

	hashTblLinear->Print(0, 100);
	hashTblLinear->Print(0, 600);

	hashTblLinear->TryRemove(FileReader::k3);
	hashTblLinear->TryRemove(FileReader::k4);

	hashTblLinear->Print(0, 100);
	hashTblLinear->Print(0, 600);

	Timer::Stop();
	std::cout << "1st phase took time : " << Timer::TimeSpent();
	//Test 1 end //////////////////////////////////////////////////////////////
	//Test 2 start: hashtable that will generate use second hash function if collision will appear for the first one 
	Timer::Start();
	RandomNumbersGenerator::Release();
	RandomNumbersGenerator::Initialize(20000, 40000);
	HashTable<int, std::string, BaseHashingFuncInteger>* hashTblDoubleHashing = new HashTable<int, std::string, BaseHashingFuncInteger>(Settings::DoubleHashing);

	hashTblDoubleHashing->TryRemove(FileReader::k1);
	hashTblDoubleHashing->TryInsert(FileReader::k1, "A");

	hashTblDoubleHashing->Print(0, 100);

	for (int i = 0; i < FileReader::elementsToBeGenerated; i++)
	{
		int generatedNumber = RandomNumbersGenerator::GetNext();
		hashTblDoubleHashing->TryInsert(generatedNumber, "A");
	}

	hashTblDoubleHashing->Print(0, 100);
	hashTblDoubleHashing->TryInsert(FileReader::k2, "B");
	hashTblDoubleHashing->TryInsert(FileReader::k3, "C");
	hashTblDoubleHashing->TryInsert(FileReader::k4, "D");

	hashTblDoubleHashing->Print(0, 100);
	hashTblDoubleHashing->Print(0, 600);

	hashTblDoubleHashing->TryRemove(FileReader::k3);
	hashTblDoubleHashing->TryRemove(FileReader::k4);

	hashTblDoubleHashing->Print(0, 100);
	hashTblDoubleHashing->Print(0, 600);

	Timer::Stop();
	std::cout << "2nd phase took time : " << Timer::TimeSpent();
	//Test 2 end //////////////////////////////////////////////////////////////
	//Test 3: start Hashtable with chaining strategy collision solving - if collision occurs, LinkedList will be expanded!
	Timer::Start();
	RandomNumbersGenerator::Release();
	RandomNumbersGenerator::Initialize(20000, 40000);
	HashTable<int, std::string, BaseHashingFuncInteger>* hashTblChaining = new HashTable<int, std::string, BaseHashingFuncInteger>(Settings::Chaining);

	hashTblChaining->TryRemove(FileReader::k1);
	hashTblChaining->TryInsert(FileReader::k1, "A");

	hashTblChaining->Print(0, 100);

	for (int i = 0; i < FileReader::elementsToBeGenerated; i++)
	{
		int generatedNumber = RandomNumbersGenerator::GetNext();
		hashTblChaining->TryInsert(generatedNumber, "A");
	}

	hashTblChaining->Print(0, 100);
	hashTblChaining->TryInsert(FileReader::k2, "B");
	hashTblChaining->TryInsert(FileReader::k3, "C");
	hashTblChaining->TryInsert(FileReader::k4, "D");

	hashTblChaining->Print(0, 100);
	hashTblChaining->Print(0, 600);

	hashTblChaining->TryRemove(FileReader::k3);
	hashTblChaining->TryRemove(FileReader::k4);

	hashTblChaining->Print(0, 100);
	hashTblChaining->Print(0, 600);

	Timer::Stop();
	std::cout << "3rd phase took time : " << Timer::TimeSpent();
	//Test 3 ended//////////////////////////////////////////////////////////////
}
