#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <cstdlib>
#include<algorithm>
#include "ctime"

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

static class RandomNumbersGenerator
{

public:

	static bool _isInitialized;

	RandomNumbersGenerator(int size)
	{
		Initialize(0, size);
	}

	static void Initialize(int from, int to)
	{
		_hashTblSize = to - from + 1;
		_arrOfRandoms = new int[_hashTblSize];
		Fill(_arrOfRandoms, from, to);
		Shuffle(_arrOfRandoms, _hashTblSize);
		_isInitialized = true;
	}

	static void Release()
	{
		_currentIndex = 0;
		_hashTblSize = 0;
		_isInitialized = false;
		_arrOfRandoms = NULL;
	}

	static int GetNext()
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

	static void PrintUniqueIds()
	{
		for (int i = 0; i < _hashTblSize; i++)
		{
			std::cout << " " << _arrOfRandoms[i] << " ";
		}
	}

private:
	static int _currentIndex;
	static int _hashTblSize;
	static int* _arrOfRandoms;

	static void Fill(int*& arr, int from, int to)
	{
		int i = 0;
		bool hasRootValue = false;
		for (int j = from; j <= to + 1; j++)
		{
			if (j == 0)
			{
				hasRootValue = true;
			}
			arr[i++] = j;
		}

		if (hasRootValue)
		{
			for (int i = from; i <= to + 1; i++)
			{
				if (arr[i] == 0)
				{
					arr[i] = to + 1;
				}
			}
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

static class Converter
{
public:

	static char* IntToCharArray(int number)
	{
		if (number <= 0)
		{
			return NULL;
		}

		int numberOfDigits = log10(number) + 1;
		char* numberArray = (char*)calloc(numberOfDigits, sizeof(char) + 1);
		sprintf(numberArray, "%ld", number);
		return numberArray;
	}
};


class Node
{
public:
	int _key = 0;
	Node* _left = NULL;
	Node* _right = NULL;
	char* _digits;

	Node(int key)
	{
		_key = key;
		_left = NULL;
		_right = NULL;
		_digits = Converter::IntToCharArray(_key);
	}

	Node(int key, Node* left, Node* right)
	{
		_key = key;
		_left = left;
		_right = right;
		_digits = Converter::IntToCharArray(_key);
	}

	~Node()
	{
		std::cout << "Deleted:::::: " << _key << std::endl;
		delete _digits;
	}

	Node* Remove(int keyToDelete, Node* parent)
	{
		//if keyToDelete is smaller than current
		//we go further left!
		if (keyToDelete < this->_key)
		{
			if (_left != NULL)
			{
				return _left->Remove(keyToDelete, this);
			}
			else
			{
				return NULL;//unless there is no left child
			}

		}//if keyToDelete is larger than current, we go further right
		else if (keyToDelete > this->_key)
		{
			if (_right != NULL)
			{
				return _right->Remove(keyToDelete, this);
			}
			else
			{
				return NULL;//unless there is no right child
			}
		}
		else
		{
			//we are going to be deleted and we have 2 childs
			//we should go and find a minimum in the right three, and replace the current _key
			if (_left != NULL && _right != NULL)
			{
				Node* minNode = _right->GetMinValueNode();
				int tmpKey = this->_key;
				this->_key = minNode->_key;
				minNode->_key = tmpKey;

				return _right->Remove(this->_key, this);
			}//we are going to be deleted and we have single child, if we're left children, we set new children to our left or our right children
			else if (parent->_left == this)
			{
				parent->_left = (_left != NULL) ? _left : _right;
				return this;
			}//we are going to be deleted and we have single child, if we're right children, we set new children to our left or our right children
			else if (parent->_right == this)
			{
				parent->_right = (_left != NULL) ? _left : _right;
				return this;
			}
		}

	}

	Node* GetMinValueNode()
	{

		if (_left == NULL)
		{
			return _left;//we're returning a guy not just a key!
		}

		return _left->GetMinValueNode();
	}

};

static class ConsolePrinter
{
public:

	static void Print(char*& array)
	{
		for (int i = 0; i < strlen(array); i++)
		{
			std::cout << array[i];
		}
	}

	static int InOrderNodesVisitedCount;
	static void Inorder(Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		InOrderNodesVisitedCount++;
		Inorder(node->_left);
		std::cout << node->_key << " ";
		Inorder(node->_right);

		if (node->_key == 0)
		{
			std::cout << std::endl << "Visited>>" << InOrderNodesVisitedCount << "<<" << std::endl;
			InOrderNodesVisitedCount = 0;
		}
	}

	static int PreOrderNodesVisitedCount;
	static void Preorder(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		PreOrderNodesVisitedCount++;
		std::cout << node->_key << " ";
		Preorder(node->_left);//rec left
		Preorder(node->_right);//rec right

		if (node->_key == 0)
		{
			std::cout << std::endl << "Visited>>" << PreOrderNodesVisitedCount << "<<" << std::endl;
			PreOrderNodesVisitedCount = 0;
		}
	}

	static int PostOrderNodesVisitedCount;
	//"bottom-up"
	static void PostOrder(Node* node)
	{
		if (node == NULL)
		{
			return;
		}

		PostOrderNodesVisitedCount++;
		PostOrder(node->_left);//rec left
		PostOrder(node->_right);//rec right	
		std::cout << node->_key << " ";

		if (node->_key == 0)
		{
			std::cout << std::endl << "Visited>>" << PostOrderNodesVisitedCount << "<<" << std::endl;
			PostOrderNodesVisitedCount = 0;
		}
	}


};
int ConsolePrinter::PostOrderNodesVisitedCount = 0;
int ConsolePrinter::PreOrderNodesVisitedCount = 0;
int ConsolePrinter::InOrderNodesVisitedCount = 0;

class BalancedBinarySearchTree
{

public:
	Node* _root = NULL;
	int _nodesNumber = 0;
	BalancedBinarySearchTree(Node* root = NULL)
	{
		if (root == NULL)
		{
			_root = new Node(0);
		}
		else
		{
			_root = root;
		}
		_nodesNumber++;
	}

	Node* GetRoot()
	{
		return _root;
	}

	int NodesCount()
	{
		return _nodesNumber;
	}

	bool Insert(Node* newNode)
	{
		Node* curr = _root;
		Node* follower = NULL;

		while (curr != NULL)
		{
			follower = curr;
			if (newNode->_key < curr->_key)
			{
				curr = curr->_left;
			}
			else
			{
				curr = curr->_right;
			}
		}

		if (newNode->_key < follower->_key)
		{
			follower->_left = newNode;
		}
		else
		{
			follower->_right = newNode;
		}

		_nodesNumber++;
		return true;
	}

	bool InsertMany(int rangeFrom, int rangeTo)
	{
		if (!RandomNumbersGenerator::_isInitialized)
		{
			RandomNumbersGenerator::Initialize(rangeFrom, rangeTo);
		}

		int numberOfNodesToInsert = 0;
		if (rangeFrom < 0)
		{
			numberOfNodesToInsert = abs(rangeFrom) + rangeTo + 1;
		}
		else
		{
			numberOfNodesToInsert = rangeTo - rangeFrom + 1;
		}

		bool inserted = false;
		for (int i = 0; i < numberOfNodesToInsert; i++)
		{
			int generatedKey = RandomNumbersGenerator::GetNext();
			inserted = Insert(new Node(generatedKey));
			if (!inserted)
			{
				throw "Could not insert key with " + generatedKey;
			}
		}

		return true;
	}

	Node* Search(int keyToFind)
	{
		Node* current = _root;

		while (current != NULL)
		{
			if (keyToFind > current->_key)
			{
				current = current->_right;
			}
			else if (keyToFind < current->_key)
			{
				current = current->_left;
			}
			else if (keyToFind == current->_key)
			{
				return current;
			}
		}
		return current;
	}

	bool Remove(int keyToDelete)
	{
		if (_root == NULL)
		{
			return false;
		}
		else
		{
			if (_root->_key == keyToDelete)
			{
				Node* auxRoot = new Node(0);
				auxRoot->_left = _root;

				Node* removedNode = _root->Remove(keyToDelete, auxRoot);
				_root = auxRoot->_left;

				if (removedNode != NULL)
				{
					delete removedNode;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				Node* removedNode = _root->Remove(keyToDelete, NULL);

				if (removedNode != NULL)
				{
					delete removedNode;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
	}


	bool Delete(int keyToDelete)
	{
		Node* current, * parent;
		current = _root;
		parent = NULL;

		//Search node which has keyToDelete
		while (current->_key != keyToDelete)
		{
			parent = current;
			if (keyToDelete < current->_key)
			{
				current = current->_left;
			}
			else if (keyToDelete > current->_key)
			{
				current = current->_right;
			}
			if (current == NULL)
			{
				std::cout << keyToDelete << "   was not found" << std::endl;
				return false;//not found
			}
		}

		///Option1: Node having two child
		if (current->_left != NULL && current->_right != NULL)
		{
			Node* prev = current;
			Node* successor = SearchSuccessor(current->_right);

			int tmp = current->_key;
			current->_key = successor->_key;
			successor->_key = tmp;

			if (successor->_right != NULL)
			{
				if (prev != current)
				{
					prev->_left = successor->_right;//przepisanie do poprzednika/parenta obecnego, nowego prawego z nastepnika
				}
				else
				{
					prev->_right = successor->_right;
				}
			}//nastepnik nie ma dziecka
			else
			{
				if (prev != current)
				{
					prev->_left = NULL;
				}
				else
				{
					prev->_right = NULL;
				}
			}
			delete successor;
			_nodesNumber--;
		}
		/*Option2: When Node is not root node */
		else if (parent != NULL)
		{
			bool left = false;
			if (keyToDelete < parent->_key)
			{
				left = true;
			}
			if (current->_left == NULL && current->_right == NULL) //LEAF!!
			{
				if (left == true)
				{
					parent->_left = NULL;
				}
				else
				{
					parent->_right = NULL;
				}
			}
			else if (current->_right == NULL) // ONE CHILD!!
			{
				if (left == true)
				{
					parent->_left = current->_left;
				}
				else
				{
					parent->_right = current->_left;
				}
			}
			else if (current->_left == NULL) // ONE CHILD!!
			{
				if (left == true)
				{
					parent->_left = current->_right;
				}
				else
				{
					parent->_right = current->_right;
				}
			}
			delete current;
			_nodesNumber--;
			return true;
		}
		/*Option3: Root Node having single or no child */
		else if (parent == NULL)
		{
			if (current->_left == NULL && current->_right == NULL)
			{
				_root = NULL;
			}
			else if (current->_left == NULL)
			{
				_root = current->_right;
			}
			else if (current->_right == NULL)
			{
				_root = current->_left;
			}
		}
	}

	Node* SearchSuccessor(Node* startingNode)
	{
		Node* current = startingNode;

		while (current && current->_left != NULL)
		{
			current = current->_left;
		}
		return current;
	}

	void MakeBackboneTurnedRight()
	{
		int rotationCounter = 0;

		Node* grandfather = NULL;
		Node* tmp = _root;
		while (tmp != NULL)
		{
			if (tmp->_left != NULL) //root replacement will be done in the rotation ;)
			{
				Node* tmp2 = tmp->_left;
				RotateRight(grandfather, tmp, tmp->_left);
				tmp = tmp2;
			}
			else
			{
				grandfather = tmp;
				tmp = tmp->_right;
			}
		}
	}

	void MakeBackboneTurnedLeft()
	{
		int rotationCounter = 0;

		Node* grandfather = NULL;
		Node* tmp = _root;
		while (tmp != NULL)
		{
			if (tmp->_right != NULL) //root replacement will be done in the rotation ;)
			{
				Node* tmp2 = tmp->_right;
				RotateLeft(grandfather, tmp, tmp->_right);
				tmp = tmp2;
			}
			else
			{
				grandfather = tmp;
				tmp = tmp->_left;
			}
		}
	}


	void BalanceTheBackBone()
	{
		int count = NodesCount();

		Node* grandfather = NULL;
		Node* tmp = _root;
		Node* tmp2 = NULL;

		//nalezy wykonac count - m rotacji, :::: gdzie m mozna policzyc za pomoca ponizszej petli
		int m = 1;
		while (m <= count)
		{
			m = 2 * m + 1;
		}
		m = m / 2;

		for (int i = 0; i < (count - m); i++)
		{
			tmp2 = tmp->_right;
			if (tmp2 != NULL)
			{
				RotateLeft(grandfather, tmp, tmp->_right);
				grandfather = tmp2;
				tmp = tmp2->_right;
			}
		}

		while (m > 1)
		{
			m = m / 2;
			grandfather = NULL;
			tmp = _root;
			for (int i = 0; i < m; i++)
			{
				tmp2 = tmp->_right;
				RotateLeft(grandfather, tmp, tmp->_right);
				grandfather = tmp2;
				tmp = tmp2->_right;
			}
		}

	}

	void RotateRight(Node* grandfather, Node* parent, Node* child)
	{
		if (grandfather != NULL)
		{
			if (grandfather->_right == parent)
			{
				grandfather->_right = child;
			}
			else
			{
				grandfather->_left = child;
			}
		}
		else
		{
			_root = child;
		}
		Node* tmp = child->_right;
		child->_right = parent;
		parent->_left = tmp;
	}

	void RotateLeft(Node* grandfather, Node* parent, Node* child)
	{
		if (grandfather != NULL)
		{
			if (grandfather->_left == parent)
			{
				grandfather->_left = child;
			}
			else
			{
				grandfather->_right = child;
			}
		}
		else
		{
			_root = child;
		}
		Node* tmp = child->_left;
		child->_left = parent;
		parent->_right = tmp;
	}

	int GetHeight()
	{
		return GetHeight(_root);
	}

private:

	// Recursive function to calculate height of given binary tree
	int GetHeight(Node* root)
	{
		// Base case: empty tree has height 0
		if (root == NULL)
		{
			return 0;
		}
		// recur for left and right subtree and consider maximum depth
		return 1 + std::max(GetHeight(root->_left), GetHeight(root->_right));
	}

};

static class FileReader
{
public:
	static int elementsToBeGenerated1;
	static int elementsToBeGenerated2;

	static int ReadFile(const char* filePath)
	{
		FILE* fp = fopen(filePath, "r");
		if (fp == NULL)
			return -1;
		fscanf(fp, "%d %d", &elementsToBeGenerated1, &elementsToBeGenerated2);
		fclose(fp);
		std::cout << elementsToBeGenerated1 << " " << " " << elementsToBeGenerated2 << " " << std::endl;
	}

};

int FileReader::elementsToBeGenerated1 = 0;
int FileReader::elementsToBeGenerated2 = 0;

int main()
{
	int fileRead = FileReader::ReadFile("C:\\ALG2\\inlab04.txt");
	if (fileRead != -1)
	{
		//*************
		//Tree testing - part 1
		//*************
		Timer::Start();

		RandomNumbersGenerator::Initialize(0, FileReader::elementsToBeGenerated1);

		Node* root = new Node(0);
		BalancedBinarySearchTree* bin = new BalancedBinarySearchTree(root);

		bin->InsertMany(0, FileReader::elementsToBeGenerated1);

		std::cout << std::endl << "NodesCount():::: " << bin->NodesCount() << " ";
		std::cout << std::endl << "1. Height BEFORE Day-Stout-Warren balancing: " << bin->GetHeight() << " ";

		bin->MakeBackboneTurnedRight();
		bin->BalanceTheBackBone();

		std::cout << std::endl << "2. Height AFTER Day-Stout-Warren balancing: " << bin->GetHeight() << " ";
		RandomNumbersGenerator::Release();
		std::cout << std::endl << std::endl;
		std::cout << "~~ part 1 ended~~" << std::endl;
		
		//*************
		//Tree testing (different nodes) - part 2
		//*************

		RandomNumbersGenerator::Initialize(0, FileReader::elementsToBeGenerated2);
		Node* root2 = new Node(0);
		BalancedBinarySearchTree* bin2 = new BalancedBinarySearchTree(root2);
		bin2->InsertMany(0, FileReader::elementsToBeGenerated2);
		std::cout << std::endl << "NodesCount():::: " << bin2->NodesCount() << " ";

		std::cout << std::endl << "3. Height BEFORE Day-Stout-Warren balancing: " << bin2->GetHeight() << " ";
		bin2->MakeBackboneTurnedRight();
		bin2->BalanceTheBackBone();
		std::cout << std::endl << "4. Height AFTER Day-Stout-Warren balancing: " << bin2->GetHeight() << " ";

		Timer::Stop();
		std::cout << "Time: (part 1 + part 2) " << Timer::TimeSpent();
		RandomNumbersGenerator::Release();
		std::cout << std::endl << std::endl;
		std::cout << "~~ part 2 ended~~" << std::endl;
	}
	else
	{
		std::cout << "Could not load file on a given path" << std::endl;
	}
	return 0;
}


// 12 Stycznia - Tablica mieszajaca
// 19/26 Stycznia - Kopiec Binarny 