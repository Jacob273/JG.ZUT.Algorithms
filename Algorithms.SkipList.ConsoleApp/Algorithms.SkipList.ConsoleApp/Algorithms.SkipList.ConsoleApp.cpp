#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include "ctime"

#define MAX_NODE_LEVEL 7
#define UNIQUE_ID_GENERATOR_SIZE 99999
#define PROB 0.5

/**
Klasa sluzaca do generowania poziomu dla wezla.
Wykonuje sie tutaj petla, ktora wykonuje sie MAX_NODE_LEVEL razy,
w ktorej istnieje 50% prawdopodobienstwo, ze nastapi inkrementacja zmiennej level.
**/
static class LevelGenerator
{
public:
	static int GenerateLevel()
	{
		int level = 0;
		while ((rand() % 100 < PROB * 100) & (level < MAX_NODE_LEVEL - 1))
		{
			level++;
		}
		return(level);
	}
};

/**
Generator liczb lowosych.
Posiada tablice z wartosciami o wielkosci UNIQUE_ID_GENERATOR_SIZE,
ktora zostaje przy inicjalizacji przetasowana wg. algorytmu FisherYatesShuffle.
**/
static class RandomNumbersGenerator
{

public:

	RandomNumbersGenerator(int size)
	{
		Initialize();
	}

	~RandomNumbersGenerator()
	{
		delete _arrOfRandoms;
	}

	static int GetNext()
	{
		if (!_isInitialized)
		{
			Initialize();
			_isInitialized = true;
		}

		if (_currentIndex < _hashTblSize)
		{
			return _arrOfRandoms[_currentIndex++];
		}
		else
		{
			std::cout << "All unique ids were used";
			return -1;
		}
	}

	void PrintUniqueIds()
	{
		for (int i = 0; i < _hashTblSize; i++)
		{
			std::cout << " " << _arrOfRandoms[i] << std::endl;
		}
	}

private:
	static bool _isInitialized;
	static int _currentIndex;
	static int _hashTblSize;
	static int* _arrOfRandoms;

	static void Initialize()
	{
		//todo: srand missing!
		_hashTblSize = UNIQUE_ID_GENERATOR_SIZE;
		_arrOfRandoms = new int[_hashTblSize];
		Fill(_arrOfRandoms, _hashTblSize);
		Shuffle(_arrOfRandoms, _hashTblSize);
	}

	static void Fill(int*& arr, int size)
	{
		for (int i = 0; i < size; i++)
		{
			arr[i] = i;
		}
	}

	static void Shuffle(int*& arr, int size)
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
};
int RandomNumbersGenerator::_currentIndex = 0;
int* RandomNumbersGenerator::_arrOfRandoms = NULL;
bool RandomNumbersGenerator::_isInitialized = false;
int RandomNumbersGenerator::_hashTblSize = 0;


/**
Klasa bazowa dla wezlow skip listy.
Przy kazdym wywolaniu konstruktora, nastepuje wylosowanie poziomu wezla a takze jego klucz.
**/
class BaseNode
{
public:

	BaseNode(bool isHeadOrTail)
	{
		Initialize(isHeadOrTail);
	}

	BaseNode(bool isHeadOrTail, int _key)
	{
		Initialize(false);
		if (_key != 0)
		{
			_uniqueKey = _key;
		}
	}

	BaseNode** neighbour;
	int _uniqueKey;
	int _generatedLevel;
	char _type;
	bool _visited;
	int _id;


	~BaseNode()
	{
		std::cout << "Releasing memory related with node with ID (" << _id << ") and key: " << _uniqueKey << "from level" << _generatedLevel << std::endl;
	}

protected:
	double rating;

	void SetNeighboursToNull()
	{
		for (int i = 0; i < _generatedLevel; i++)
		{
			neighbour[i] = NULL;
		}
	}

	void UpdateType(char newType)
	{
		_type = newType;
	}


private:
	static int _counter;
	void Initialize(bool isHeadOrTail)
	{
		_generatedLevel = MAX_NODE_LEVEL;
		_uniqueKey = 0;
		if (!isHeadOrTail)
		{
			_generatedLevel = LevelGenerator::GenerateLevel();
			_uniqueKey = RandomNumbersGenerator::GetNext();
		}
		neighbour = new BaseNode * [_generatedLevel];
		_type = 'T';
		SetNeighboursToNull();
		_id = ++_counter;
		//std::cout << " Node generated: " << " ID(" << _id << ")" << " key[" << _uniqueKey << "]" << "level: " << _generatedLevel << std::endl;
	}

};
int BaseNode::_counter = 0;

/**
Klasa typu helper, ktora wypelnia miejsce w pamieci dla przekazanego parametru zerami.
**/
static class Helper
{
public:
	static void FillWithValues(BaseNode**& baseNodeArray, int _value, int size)
	{
		memset(baseNodeArray, _value, sizeof(BaseNode*) * (MAX_NODE_LEVEL));
	}

};

/**
Head skip listy.
**/
class HeadNode : public BaseNode
{
public:
	HeadNode() : BaseNode(true)
	{
		this->Initialize();
	}

private:
	void Initialize()
	{
		Helper::FillWithValues(neighbour, 0, MAX_NODE_LEVEL);
	}
};

/**
Tail skip listy.
**/
class TailNode : public BaseNode
{
public:
	TailNode() : BaseNode(true)
	{

	}
private:

};

/**
Liniowa struktura danych charakteryzujaca sie tym, ze wkladane wezly maja
okreslony poziom wysokosci, ktora jest generowany z pewnym prawdopodobienstwem PROB.
**/
class SkipList
{
public:
	const int MaxLevel = MAX_NODE_LEVEL;

	SkipList()
	{
		Initialize();
	}

	/**
	Wyswietlenie wezlow bedacych sasiadami heada.
	**/
	void DisplayHeadNeighbours()
	{
		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			BaseNode* node = head->neighbour[i];
			std::cout << "Level <<" << i << ">>";

			if (node == NULL)
			{
				std::cout << "NULL" << std::endl;
			}
			else
			{
				std::cout << node->_uniqueKey << std::endl;
				node = node->neighbour[i];
			}
		}
	}

	/**
	Wyswietlenie wszystkich wezow: Rozpoczynajac od najwyzszego poziomu,
	odwiedzamy sasiada, a nastepnie kolejnego... a gdy juz sasiadow brak powtorzenie tej samej operacji dla poziomu o 1 nizszego.
	**/
	void DisplayAll_Ver1()
	{
		if (_hashTblSize <= 0)
		{
			std::cout << "List is empty" << std::endl;
			return;
		}

		BaseNode* current = head;
		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			std::cout << "Level [" << i << "]";
			BaseNode* neighbour = current->neighbour[i];
			while (neighbour != NULL)
			{
				std::cout << neighbour->_uniqueKey << "   ";
				if (neighbour->neighbour[i] != NULL)
				{
					neighbour = neighbour->neighbour[i];
				}
				else
				{
					neighbour = NULL;
				}
			}
			std::cout << std::endl;
		}
	}

	/**
	Ustawienie wszystkim  wezlom flagi visited na false.

	**/
	void SetAllToNotVisitedAgain()
	{
		std::cout << "~~~~~~~~~~~~~SetAllToNotVisitedAgain" << std::endl;

		BaseNode* current = head;
		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			BaseNode* neighbour = current->neighbour[i];
			while (neighbour != NULL)
			{
				if (neighbour->neighbour[i] != NULL)
				{
					neighbour = neighbour->neighbour[i];
					neighbour->_visited = false;
				}
				else
				{
					neighbour = NULL;
				}
			}
		}
	}

	/**
	Funkcja wyswietlajaca top zadanych wezlow, ktorych poziom jest conajmniej wiekszy rowny wartosci minimumLevel.
	Aby nie wyswietlac n-razy tego samego wezla zostala wykorzystana uzywa flaga visited do oznaczenia czy dany wezel byl juz odwiedzony.
	**/
	void Display(int top, int minimumLevel)
	{

		std::cout << "~~~~~~~~~~~~~Displaying top<" << top << "> ~~~~~~~~~~ minimumLevel<" << minimumLevel << ">" << std::endl;

		if (minimumLevel > MAX_NODE_LEVEL)
		{
			std::cout << "Maximum node level is " << MAX_NODE_LEVEL;
			return;
		}

		if (minimumLevel <= 0)
		{
			std::cout << "Given level must be atleast higher than 0 !";
			return;
		}

		BaseNode* current = head;
		int nodeVisitedCounter = 0;
		for (int i = minimumLevel - 1; i >= 0; i--)
		{
			std::cout << "Level [" << i << "]";
			BaseNode* neighbour = current->neighbour[i];
			while (neighbour != NULL)
			{
				std::cout << neighbour->_uniqueKey << "   ";
				if (neighbour->neighbour[i] != NULL)
				{
					neighbour = neighbour->neighbour[i];
					nodeVisitedCounter++;
					if (nodeVisitedCounter >= top)
					{
						std::cout << std::endl << "Stopped visiting at level " << i << " as the number of elements visited has been exceeded." << std::endl;
						return;
					}
				}
				else
				{
					neighbour = NULL;
				}
			}
			std::cout << std::endl;
		}
	}

	/**
	Funkcja zwracajaca liczbe wezlow w liscie.
	**/
	int Size()
	{
		std::cout << "~~~~~~~~~~~~~Count(" << _hashTblSize << ")" << std::endl;
		return _hashTblSize;
	}

	/**
	Funkcja zwracajaca wezly, ktorych poziom jest conajmniej taki jaki przekazany jako minimumLevelRequired.
	**/
	int Size(int minimumLevelRequired)
	{
		std::cout << "~~~~~~~~~~~~~Counting nodes with required level " << minimumLevelRequired << std::endl;
		if (minimumLevelRequired < 0)
		{
			std::cout << "Level below 1 is not acceptable. Level 1 is required atleast" << std::endl;
			return -1;
		}

		if (minimumLevelRequired > MAX_NODE_LEVEL)
		{
			std::cout << "Level above " << MAX_NODE_LEVEL << "is not acceptable." << std::endl;
			return -1;
		}

		BaseNode* current = head;
		int nodeVisitedCounter = 0;
		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			BaseNode* neighbour = current->neighbour[i];
			while (neighbour != NULL)
			{

				if (neighbour->_visited == false &&
					neighbour->_generatedLevel >= minimumLevelRequired)
				{
					neighbour->_visited = true;
					nodeVisitedCounter++;
				}

				if (neighbour->neighbour[i] != NULL)
				{
					neighbour = neighbour->neighbour[i];
				}
				else
				{
					neighbour = NULL;
				}
			}
		}
		SetAllToNotVisitedAgain();
		std::cout << "Nodes with given required level [" << minimumLevelRequired << "] (" << nodeVisitedCounter << ")" << std::endl;
		return nodeVisitedCounter;
	}

	/**
	Funkcja dodajaca element do listy z przeskokami.
	**/
	bool Insert(int _key)
	{
		BaseNode* newNode = new BaseNode(false, _key);
		//std::cout << "~~~~~~~~~~~~~Inserting: " << newNode->_uniqueKey << std::endl;

		BaseNode* current = head;

		BaseNode* jumpHistory[MAX_NODE_LEVEL];
		memset(jumpHistory, 0, sizeof(BaseNode*) * (MAX_NODE_LEVEL));

		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			//Key of the next node is less than key to be inserted 
			//then we keep on moving to next neighbours ---> on the same level
			while (current->neighbour[i] != NULL &&
				newNode->_uniqueKey > current->neighbour[i]->_uniqueKey)
			{
				current = current->neighbour[i];
				//std::cout << "|right|  ";
			}
			//Key of next node is greater than the key to be inserted 
			//then we store the pointer to current node i at history[i]
			jumpHistory[i] = current;
			//std::cout << "|down| ";
		}

		//We get the current's neighbour (it might be null or equal!)
		current = current->neighbour[0];

		if (current == NULL ||
			current->_uniqueKey != newNode->_uniqueKey)
		{

			// We go up to set a new neighbour
			// we.right.neighbour => jumpHistory.right.neighbour
			// jumpHistory.right.neighbour => we
			for (int i = 0; i <= newNode->_generatedLevel; i++)
			{
				newNode->neighbour[i] = jumpHistory[i]->neighbour[i];
				jumpHistory[i]->neighbour[i] = newNode;
			}
			std::cout << "Inserted [" << newNode->_uniqueKey << "]" << " on level [" << newNode->_generatedLevel << "]" << std::endl;
			_hashTblSize++;
			return true;
		}

		//std::cout << "Failed to insert " << newNode->_uniqueKey << "D type will be set." << std::endl;
		newNode->_type = 'D';
		return false;
	}

	/**
	Funkcja ktora wprowadza do SkipListy liczbe wezlow okreslonych w parametzr numberOfNodes.
	**/
	void InsertMany(int numberOfNodes)
	{
		for (int i = 0; i < numberOfNodes; i++)
		{
			Insert(0);
		}
	}

	/**
	Funkcja, ktora przeszukuje skip liste w poszukiwaniu wezla o zadanym kluczu keyToSearch.
	Jesli nie znajdzie - zwraca NULL.
	**/
	BaseNode* Search(int keyToSearch)
	{
		std::cout << "~~~~~~~~~~~~~Searching: " << keyToSearch << std::endl;

		BaseNode* current = head;

		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			while (current->neighbour[i] != NULL &&
				keyToSearch > current->neighbour[i]->_uniqueKey)
			{
				current = current->neighbour[i];
			}

		}
		current = current->neighbour[0];

		// If current node have key equal to 
		// search key, we have found our target node 
		if (current != NULL &&
			current->_uniqueKey == keyToSearch)
		{
			std::cout << "Found node with key: " << keyToSearch << std::endl;
			return current;
		}

		std::cout << "Could not found node with key: " << keyToSearch << std::endl;
		return NULL;
	}

	/**
	Funkcja usuwajaca pojedynczy wezel o zadanym kluczu keyToDelete.
	**/
	bool Delete(int keyToDelete)
	{
		std::cout << "~~~~~~~~~~~~~Deleting: " << keyToDelete << std::endl;

		BaseNode* current = head;

		BaseNode* jumpHistory[MAX_NODE_LEVEL];
		memset(jumpHistory, 0, sizeof(BaseNode*) * (MAX_NODE_LEVEL));

		for (int i = MAX_NODE_LEVEL - 1; i >= 0; i--)
		{
			while (current->neighbour[i] != NULL &&
				keyToDelete > current->neighbour[i]->_uniqueKey)
			{
				current = current->neighbour[i];
			}
			jumpHistory[i] = current;
		}

		current = current->neighbour[0];

		if (current != NULL && current->_uniqueKey == keyToDelete)
		{
			for (int i = 0; i <= MAX_NODE_LEVEL - 1; i++)
			{
				//no need to move further neighbours if there is no our guy here !*/
				if (jumpHistory[i]->neighbour[i] != current)
				{
					break;
				}
				jumpHistory[i]->neighbour[i] = current->neighbour[i];
			}

			delete current;
			std::cout << "Deleted node with key <<" << keyToDelete << ">>" << std::endl;
			_hashTblSize--;
			return true;
		}
		std::cout << "Did not deleted node with key <<" << keyToDelete << ">>" << std::endl;
		return false;
	}

	/**
	Funkcja usuwajaca wszystkie wezly w skip liscie i zwalniajaca pamiec, ktora zostala zarezerwowana przy pomocy slowa new.
	**/
	void Clear()
	{
		std::cout << "~~~~~~~~~~~~~Clear: " << std::endl;

		BaseNode* current = head;
		BaseNode* tmp = NULL;
		int levelToDelete = 0;
		while (current->neighbour[levelToDelete] != NULL)
		{
			tmp = current->neighbour[levelToDelete];
			delete current;
			current = NULL;
			_hashTblSize--;
			current = tmp;
		}
		delete tmp;
	}

	int GetSize()
	{
		return _hashTblSize;
	}

private:

	HeadNode* head;
	TailNode* tail;
	int _hashTblSize;
	void Initialize()
	{
		head = new HeadNode();
		tail = new TailNode();
		_hashTblSize = 0;
		for (int i = 0; i < MAX_NODE_LEVEL; i++)
		{
			head->neighbour[i] = tail->neighbour[i];
		}
	}

};

static class Timer
{

	static clock_t startTime;
	static clock_t endTime;
public:
	static void Start()
	{
		startTime = clock();
	}

	static void Stop()
	{
		endTime = clock();
	}

	static double TimeSpent()
	{
		return (double)(endTime - startTime) / CLOCKS_PER_SEC;
	}
};
clock_t Timer::endTime = 0;
clock_t Timer::startTime = 0;

static class FileReader
{
public:
	static int elementsToBeGenerated;
	static int maxLevel;
	static int k1;
	static int k2;
	static int k3;
	static int k4;
	static int k5;

	static int ReadFile(const char* filePath)
	{
		FILE* fp = fopen(filePath, "r");
		if (fp == NULL)
			return -1;
		fscanf(fp, "%d %d %d %d %d %d %d", &elementsToBeGenerated, &maxLevel, &k1, &k2, &k3, &k4, &k5);
		fclose(fp);
		std::cout << elementsToBeGenerated << " " << maxLevel << " " << k1 << " " << k2 << " " << k3 << " " << k4 << " " << k5 << std::endl;
	}

};

int FileReader::elementsToBeGenerated = 0;
int FileReader::maxLevel = 0;
int FileReader::k1 = 0;
int FileReader::k2 = 0;
int FileReader::k3 = 0;
int FileReader::k4 = 0;
int FileReader::k5 = 0;

int main()
{

	int fileRead = FileReader::ReadFile("C:\\ALG2\\inlab02.txt");

	if (fileRead != -1)
	{
		SkipList* s = new SkipList();
		Timer::Start();
		s->Search(FileReader::k1);

		s->InsertMany(FileReader::elementsToBeGenerated);

		s->Size();
		s->Insert(FileReader::k1);
		s->Insert(FileReader::k2);
		s->Insert(FileReader::k3);
		s->Insert(FileReader::k4);
		s->Insert(FileReader::k5);

		s->Delete(FileReader::k1);
		s->Delete(FileReader::k2);
		s->Delete(FileReader::k3);
		s->Delete(FileReader::k4);
		s->Delete(FileReader::k5);

		s->Clear();
		s->Size();

		Timer::Stop();
	}
	else
	{
		std::cout << "Could not load file on a given path" << std::endl;
	}
	std::cout << "Time: " << Timer::TimeSpent() << std::endl;
}


//BST:
//Find(Node, int key)
//