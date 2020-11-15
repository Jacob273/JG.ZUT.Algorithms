#include "stdafx.h"
#include "string"
#include "iostream"

using namespace std;

/** Structures **/
struct Car {
private:
	int _id;
	string _manufacturer;
	string _model;
	int _yearOfProduction;

public:
	Car(int id, string manufacturer, string model, int yearOfProduction) {
		_id = id;
		_manufacturer = manufacturer;
		_model = model;
		_yearOfProduction = yearOfProduction;
	}

	void print() {
		cout << endl;
		cout << "id:" << _id << endl;
		cout << "manufacturer:" << _manufacturer << endl;
		cout << "model:" << _model << endl;
		cout << "yearOfProduction:" << _yearOfProduction << endl;
	}

	//Getters & Setters
	int getId() {
		return _id;
	}

	string getManufacturer() {
		return _manufacturer;
	}

	string getModel() {
		return _model;
	}

	int yearOfProduction() {
		return _yearOfProduction;
	}

	void setId(int id) {
		_id = id;
	}

	void setManufacturer(string manufacturer) {
		if (!manufacturer.empty())
			_manufacturer = manufacturer;
	}

	void setModel(string model) {
		if (!model.empty())

			_model = model;
	}

	void setYearOfProduction(int yearOfProduction) {
		_yearOfProduction = yearOfProduction;
	}
};

struct Volkswagen : Car {
private:
	int _volkswagenNumber;
public:
	void print() {
		Car::print();
		cout << "volkswagenNumber:" << _volkswagenNumber << endl;
	}

	Volkswagen(int id, string manufacturer, string model, int yearOfProduction, int volkswagenNumber) : Car(id, manufacturer, model, yearOfProduction) {

		_volkswagenNumber = volkswagenNumber;
	}

	int getVolkswagenNumber() {
		return _volkswagenNumber;
	}

	void setVolkswagenNumber(int volkswagenNumber) {
		_volkswagenNumber = volkswagenNumber;
	}
};

/** Global functions **/
void Menu();
void DisplayPossibleChoices();
int GetInput();
void PrintStars();
void AddNewCarToTheEnd();
void IncrementSizeOfList();
int GetActualSizeOfList();
bool ListIsNull();
void CreateList();
Car* GenerateRandomCar(int indexOfCar);
void InitializeList();
void CopyToNewThenAdd(int oldSize);
void PrintActualList();
void EliminateElements(Car** list, int sizeOfList);
void PrintCarsAddress(Car **arrOfCars, int numberOfCars);
void PrintCars(Car** list, int size);
void AlocateMemoryForElements(Car **arrOfCars, int size);
void EliminateArray(Car** list);
void PrintAddress(Car** list);
void RemoveLastCar();
void DecrementSizeOfList();
void CopyToNewThenRemove(int oldSize);
void InsertNewCar(int index);
void CopyAndInsertOnIndex(int index, int oldSize, Car *carToInsert);
void CopyAndRemoveOnIndex(int positionToRemoveAt, int oldSize);
void RemoveCar(int index);

/** Global variables which are visible troughout the program **/
int sizeOfList = 0;
Car **listOfCars = NULL;

int main()
{
	Menu();

    return 0;
}

void Menu() {
	
	int choice = 0;

	do
	{
		PrintStars();
		DisplayPossibleChoices();
		choice = GetInput();
		switch (choice) {
		case -1:
			cout << "Invalid input, please try again...";
			break;
		case 1:
			PrintActualList();
			break;
		case 2:
			AddNewCarToTheEnd();
			break;
		case 3:
			RemoveLastCar();
			break;
		case 4:
			cout << "On which index you want to insert your car?:" << endl;
			InsertNewCar(GetInput());
			break;
		case 5:
			cout << "On which index you want to delete car?:" << endl;
			RemoveCar(GetInput());
			break;
		case 6:
			system("cls");
			break;
		case 0:
			cout << "\n\n>>>>>>>>>> Printing addresses of elements in the list..." << endl;
			PrintCarsAddress(listOfCars, GetActualSizeOfList());
			cout << "\n\n>>>>>>>>>> Dealocating memory taken by cars in the list..." << endl;
			EliminateElements(listOfCars, GetActualSizeOfList());
			cout << "\n\n>>>>>>>>>> Printing addresses of elements in the list after dealocation..." << endl;
			PrintCarsAddress(listOfCars, GetActualSizeOfList());
			cout << "\n\n>>>>>>>>>> Dealocating memory taken by array..." << endl;
			EliminateArray(listOfCars);
			cout << ">> ** Exiting the CarManagerTwo program... ** << \n";
			break;
		default:
			break;
		}
	} while (choice != 0);
	system("PAUSE");
}

int GetInput()
{
	int choice;
	cin >> choice;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(512, '\n');
		return -1;
	}
	return choice;
}

void DisplayPossibleChoices()
{
	cout << "\nMain Menu\n";
	cout << "Pick one from the below:\n";
	cout << "1 - Cars in list\n";
	cout << "2 - Add car to the end of the list\n";
	cout << "3 - Remove last car\n";
	cout << "4 - Add car on specific place.\n";
	cout << "5 - Remove car from specific place.\n";
	cout << "6 - Clear the console.\n";
	cout << "0 - EXIT\n\n";
	cout << "Your choice: ";
}

void PrintStars() {
	cout << endl;
	for (int i = 0; i < 80; i++) {
		cout << "*";
	}
	cout << endl;
}

void AddNewCarToTheEnd() {
	int sizeBeforeIncrement = GetActualSizeOfList();
	IncrementSizeOfList();
	if ( ListIsNull()) {
		CreateList();
		InitializeList();
	}
	else
	{
		CopyToNewThenAdd(sizeBeforeIncrement);
	}

	cout << "\n\n >>>>>>>>>> Car(" << GetActualSizeOfList() <<  ") successfully added.";
}

void RemoveLastCar() {
	if (ListIsNull() || GetActualSizeOfList() == 0) {
		cout << "\n Car couldn't be removed from the list, because list doesn't exist or is empty.";
	}
	else
	{
		int sizeBeforeDecrement = GetActualSizeOfList();
		CopyToNewThenRemove(sizeBeforeDecrement);
		DecrementSizeOfList();
		cout << "\n\n >>>>>>>>>> Car has been successfully removed.";
	}
}

void InsertNewCar(int index) {
	int sizeBeforeIncrement = GetActualSizeOfList();

	if (index > sizeBeforeIncrement) {
		cout << "Index cannot exceed size of the list, actual size of list : " << GetActualSizeOfList();
		return;
	}

	if (ListIsNull() && sizeBeforeIncrement == 0) {
		IncrementSizeOfList();
		CreateList();
		InitializeList();
	}
	else
	{
		IncrementSizeOfList();
		Car *carToInsert = GenerateRandomCar(GetActualSizeOfList() - 1);
		CopyAndInsertOnIndex(index, sizeBeforeIncrement, carToInsert);
	}

	cout << "\n\n >>>>>>>>>> Car(" << GetActualSizeOfList() << ") successfully added.";
}

void RemoveCar(int index) {
	int sizeBeforeDecrement = GetActualSizeOfList();

	if (index >= sizeBeforeDecrement) {
		cout << "Index cannot exceed size of the list, actual size of list : " << GetActualSizeOfList();
		return;
	}
	
	DecrementSizeOfList();
	CopyAndRemoveOnIndex(index, sizeBeforeDecrement);
	cout << "\n\n >>>>>>>>>> Car has been removed.";
}


void IncrementSizeOfList() {
	sizeOfList++;
}

void DecrementSizeOfList() {
	sizeOfList--;
}

int GetActualSizeOfList() {
	return sizeOfList;
}

bool ListIsNull() {
	return (listOfCars == NULL) ? true : false;
}

void CreateList() {
	listOfCars = new Car*[sizeOfList];
}

void InitializeList() {
	int actualSizeOfList = GetActualSizeOfList();
	int carIndex = GetActualSizeOfList() - 1;
	for (int i = 0; i < actualSizeOfList; i++) {
		listOfCars[i] = GenerateRandomCar(carIndex);
	}
}

Car* GenerateRandomCar(int indexOfCar) {
	return new Car(indexOfCar, "Honda", "Civic", 1990 + indexOfCar);
}

void CopyToNewThenAdd(int oldSize) {
	int newSize = oldSize + 1;
	int newCarIndex = newSize - 1;
	Car** newArrayOfCars = new Car*[newSize];
	
	for (int i = 0; i < oldSize ; i++) {
		newArrayOfCars[i] = listOfCars[i];
	}
	//adding to the last element of array
	newArrayOfCars[newSize - 1] = GenerateRandomCar(newCarIndex);

	EliminateArray(listOfCars);
	listOfCars = newArrayOfCars;
}

void CopyToNewThenRemove(int oldSize) {
	int newSize = oldSize - 1;
	int indexOfLastElement = oldSize - 1;
	Car** newArrayOfCars = new Car*[newSize];

	for (int i = 0; i < newSize; i++) {
		newArrayOfCars[i] = listOfCars[i];
	}
	//removing last element of the array
	delete listOfCars[indexOfLastElement];

	EliminateArray(listOfCars);
	listOfCars = newArrayOfCars;
}

void CopyAndInsertOnIndex(int positionToInsertAt, int oldSize, Car *carToInsert) {
	int newSize = oldSize + 1;
	int newCarIndex = newSize - 1;
	Car** newArrayOfCars = new Car*[newSize];

	for (int i = 0; i < newSize; i++) {

		if (i < positionToInsertAt) {
			newArrayOfCars[i] = listOfCars[i]; //All the elements before that car which must be inserted
		}

		if (i == positionToInsertAt) {//The right place to insert the new element
			newArrayOfCars[i] = carToInsert;
		}

		if (i > positionToInsertAt) {//All the remaining elements
			newArrayOfCars[i] = listOfCars[i - 1];
		}
	}
	EliminateArray(listOfCars);
	listOfCars = newArrayOfCars;
}

void CopyAndRemoveOnIndex(int positionToRemoveAt, int oldSize) {
	int newSize = oldSize - 1;
	Car** newArrayOfCars = new Car*[newSize];

	for (int i = 0; i < oldSize; i++) {

		if (i < positionToRemoveAt) {
			newArrayOfCars[i] = listOfCars[i]; //All the elements before that car which must be deleted
		}

		if (i == positionToRemoveAt) {//Delete the car
			delete listOfCars[i];
		}

		if (i > positionToRemoveAt) {//All the remaining elements
			newArrayOfCars[i - 1] = listOfCars[i];
		}
	}
	EliminateArray(listOfCars);
	listOfCars = newArrayOfCars;
}

void PrintActualList() {
	int sizeOfList = GetActualSizeOfList();
	if (sizeOfList == 0) {
		cout << "\n\n>>>>>>>>>> List is empty.";
	}
	else {
		cout << "\n\n>>>>>>>>>> List of cars:";
		for (int i = 0; i < sizeOfList; i++) {
			listOfCars[i]->print();
		}
	}
	cout << endl;
	cout << "\n\n>>>>>>>>>> TOTAL NUMBER OF CARS: " << GetActualSizeOfList();
	cout << endl;
}

void PrintCars(Car** list, int size) {
	for (int i = 0; i < size; i++)
		list[i]->print();
}


void EliminateArray(Car** list) {
	delete[] list;
	list = NULL;
}

void EliminateElements(Car** list, int sizeOfList){
	for (int i = 0; i < sizeOfList; i++) {
		delete list[i];
		list[i] = 0;
	}
}

void PrintCarsAddress(Car **arrOfCars, int numberOfCars) {
	for (int i = 0; i < numberOfCars; i++) {
		cout << arrOfCars[i];
		cout << endl;
	}
}

void AlocateMemoryForElements(Car **arrOfCars, int size) {
	for (int i = 0; i < size; i++) {
		arrOfCars[i] = new Car(0,"0","0",0);
	}
}

void PrintAddress(Car** list) {
	cout << list;
}
