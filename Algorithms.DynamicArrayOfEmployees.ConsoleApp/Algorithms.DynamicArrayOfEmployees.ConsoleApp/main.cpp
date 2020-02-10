#define _CRT_SECURE_NO_WARNINGS 1

#include "iostream"
#include "ctime"
#include "windows.h"

#define EMPL_TO_PRINT 20

using namespace std;

/** Structures **/
struct Employee {
	int uniqueValue;
	char firstNameLetter;
	float index;
};


Employee** CreateRandomEmployees(int numberOfEmployees);
void BubbleSortEmployees(Employee** arrOfEmployees, int arrSize);
void DeleteEmployees(Employee** arrOfEmployees, int arrSize);
int CountLetter(Employee** arrOfEmployees, int arrSize, char letterToSearch);

char GenereateRandomUpperCaseLetter();
void InitializeRand();
void PrintArray(int* arr, int arrSize);
void AllocateArray(int*& arr, int arrSize);
void PopulateArray(int*& arr, int arrSize);
void FisherYatesShuffle(int*& arr, int N);
void DeallocateArray(int*& arr);
int GetUniqueRandom();
Employee* CreateSingleEmployee(float index);
void PrintEmployees(Employee** arrOfEmp, int numberOfEmployees);
void PrintEmployees(Employee** arrOfEmp, int numberOfEmployees, int emplToPrint);
void PrintEmployeesAddress(Employee** arrOfEmployees, int arrSize);
void DisplayInfo();
void StartTime();
void StopTime();
double TimeSpent();
int ReadFile(const char* filePath);

/** Global variables **/
int* arrOfRandoms = NULL;
Employee** arrOfEmployees = NULL;
int actualRandomIndex = 0;
clock_t beginTime, endTime;
double timeSpent;

const char* filePath = "C:\\ALG2\\inlab01.txt";
int numberFromFile = 0;
char letterToCount = NULL;
int letterCount = 0;

int main()
{
	InitializeRand();
	int fileRead = 0;
	fileRead = ReadFile(filePath);
	if (fileRead != -1)
	{
		StartTime();

		//Generating array filled with 0 to n values and shuffling
		AllocateArray(arrOfRandoms, numberFromFile);
		PopulateArray(arrOfRandoms, numberFromFile);
		FisherYatesShuffle(arrOfRandoms, numberFromFile);

		//Generating Dynamic array of Employees
		arrOfEmployees = CreateRandomEmployees(numberFromFile);
		BubbleSortEmployees(arrOfEmployees, numberFromFile);

		//Main task: count number of occurences of a given letter
		letterCount = CountLetter(arrOfEmployees, numberFromFile, letterToCount);

		StopTime();

		PrintEmployees(arrOfEmployees, numberFromFile, EMPL_TO_PRINT);
		cout << "Letter " << letterToCount << " has occured: " << letterCount << " times." << endl;
		cout << "Time taken: " << TimeSpent() << "s.";

		//Release array of generated numbers and Dynamic array of Employees
		DeallocateArray(arrOfRandoms);
		DeleteEmployees(arrOfEmployees, numberFromFile);
	}
	else
	{
		cout << "File couldn't be open.";
	}
	DisplayInfo();
	return fileRead;
}

int ReadFile(const char* filePath)
{
	FILE* fp = fopen(filePath, "r");
	if (fp == NULL)
		return -1;
	fscanf(fp, "%d %c", &numberFromFile, &letterToCount);
	fclose(fp);
}

void StartTime()
{
	beginTime = clock();
}

void StopTime()
{
	endTime = clock();
}

double TimeSpent()
{
	return timeSpent = (double)(endTime - beginTime) / CLOCKS_PER_SEC;
}


void DeallocateArray(int*& arr)
{
	delete[]arr;
	arr = 0;
}

int CountLetter(Employee** arrOfEmployees, int arrSize, char letterToSearch)
{
	int letterCount = 0;
	for (int i = 0; i < arrSize; i++)
	{
		if (letterToSearch == arrOfEmployees[i]->firstNameLetter)
		{
			letterCount++;
		}
	}
	return letterCount;
}

void DisplayInfo()
{
	cout << "\nPress enter to continue";
	cin.ignore();
}

void AllocateArray(int*& arr, int arrSize)
{
	arr = new int[arrSize];
}


int GetUniqueRandom()
{
	if (actualRandomIndex < numberFromFile)
	{
		return arrOfRandoms[actualRandomIndex++];
	}
	else
	{
		return -1;//all were chosen
	}
}

void PrintArray(int* arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << '[' << i << "]" << arr[i] << "\n";
	}
}
void PopulateArray(int*& arr, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
		arr[i] = i + 1;
}

void FisherYatesShuffle(int*& array, int N)
{
	int i, j, temp;
	for (i = N - 1; i >= 0; i--)
	{
		j = rand() % (i + 1);
		temp = array[j];
		array[j] = array[i];
		array[i] = temp;
	}
}

Employee* CreateSingleEmployee(float index)
{
	Employee* empl = new Employee();
	empl->uniqueValue = GetUniqueRandom();
	empl->firstNameLetter = GenereateRandomUpperCaseLetter();
	empl->index = 100 + index;
	return empl;
}

void InitializeRand()
{
	srand(time(NULL));//time(NULL) returns current time
}

char GenereateRandomUpperCaseLetter()
{
	return 'A' + rand() % 26;	//A is equal 65 in int
}

void PrintEmployees(Employee** arrOfEmp, int numberOfEmployees)
{
	for (int i = 0; i < numberOfEmployees; i++)
	{
		cout << "Letter:" << arrOfEmp[i]->firstNameLetter << " ";
		cout << "Unique:" << arrOfEmp[i]->uniqueValue << " ";
		cout << "Index:" << arrOfEmp[i]->index << " \n";
	}
	cout << endl;
}

void PrintEmployees(Employee** arrOfEmp, int numberOfEmployees, int emplToPrint)
{

	for (int i = 0; i < emplToPrint; i++) {
		cout << "Letter:" << arrOfEmp[i]->firstNameLetter << " ";
		cout << "Unique:" << arrOfEmp[i]->uniqueValue << " ";
		cout << "Index:" << arrOfEmp[i]->index << " \n";
	}
	cout << endl;
}

Employee** CreateRandomEmployees(int numberOfEmployees)
{
	Employee** arrOfEmployees = new Employee * [numberOfEmployees];

	for (int i = 0; i < numberOfEmployees; i++)
	{
		arrOfEmployees[i] = CreateSingleEmployee(i);
	}

	return arrOfEmployees;
};

void BubbleSortEmployees(Employee** empsToSort, int numberOfEmployees)
{

	bool swapOccured;
	for (int i = 0; i < numberOfEmployees; i++)
	{
		swapOccured = false;
		for (int j = 0; j < numberOfEmployees - 1 - i; j++)
		{
			if (empsToSort[j]->uniqueValue > empsToSort[j + 1]->uniqueValue)
			{
				swap(empsToSort[j], empsToSort[j + 1]);
				swapOccured = true;
			}
		}

		//optimization, no swapping took place
		if (swapOccured == false)
		{
			return;
		}
	}
}

void DeleteEmployees(Employee** empsToDelete, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		delete empsToDelete[i];
	}
	delete[] empsToDelete;
	empsToDelete = 0;
}


void PrintEmployeesAddress(Employee** arrOfEmployees, int arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		cout << arrOfEmployees[i];
		cout << endl;
	}
}