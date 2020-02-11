// Hash map class template
#include "DefaultHashingFunc.h"
#include "Settings.h"
#include "TblNode.h"
#include "string"
#include "AlternativeHashingFunctionInteger.h"

template <typename TKey, typename TNode, typename THashFunc = DefaultHashingFunc<TKey>>
class HashTable
{
public:

	//Construction
	HashTable(Settings::Strategy strategy)
	{
		_hashTblSize = Settings::GlobalHashTableSize;
		_tbl = new TblNode<TKey, TNode>* [_hashTblSize]();
		_strategy = strategy;
		_nodesCounter = 0;
	}

	int Size()
	{
		return _hashTblSize;
	}

	int Count()
	{
		return _nodesCounter;
	}

	//Destruction
	~HashTable()
	{
		for (int i = 0; i < _hashTblSize; ++i)
		{
			TblNode<TKey, TNode>* entry = _tbl[i];
			while (entry != NULL)
			{
				TblNode<TKey, TNode>* prev = entry;
				entry = entry->GetNext();
				delete prev;
				_nodesCounter--;
			}
			_tbl[i] = NULL;
		}
		delete[] _tbl;
	}

	bool TryGet(const TKey& key, TblNode<TKey, TNode>*& outNode)
	{
		unsigned long hashValue = _hashFunc(key);
		TblNode<TKey, TNode>* currentNode = _tbl[hashValue];

		switch (_strategy)
		{
		case Settings::Strategy::Chaining:
		{
			TblNode<TKey, TNode>* node = _tbl[hashValue];

			while (currentNode != NULL)
			{
				if (currentNode->GetKey() == key)
				{
					outNode = currentNode;
					return true;
				}
				currentNode = currentNode->GetNext();
			}
			return false;
			break;
		}

		case Settings::Strategy::LinearProbing:
		{
			//Search for an unused slot and if the index will exceed the hashTableSize then roll back
			int index = hashValue;
			int avoidInfiniteLoopCounter = 0;
			while (_tbl[hashValue] != NULL &&
				_tbl[hashValue]->GetKey() != key &&
				_tbl[hashValue]->IsDummy() != false)
			{
				index = (index + 1) % _hashTblSize;
				avoidInfiniteLoopCounter++;
				if (avoidInfiniteLoopCounter > _hashTblSize)
				{
					break;
				}

			}

			//Check if the element is present in the hash table
			if (_tbl[index] != NULL &&
				_tbl[index]->GetKey() == key)
			{
				outNode = _tbl[index];
				return true;
			}
			else
			{
				outNode = NULL;
				return false;
			}
		}

		case Settings::Strategy::DoubleHashing:
		{
			int stepSize = _alternativeHashFuncForCollisions(key);

			int index = hashValue;
			while (currentNode != NULL)
			{
				if (currentNode->IsDummy() == false &&
					currentNode->GetKey() == key)
				{
					outNode = currentNode;
					return true;
				}

				index = (index + stepSize) % _hashTblSize;
				currentNode = _tbl[index];
			}
			break;
		}
		}
		return false;
	}

	void TryInsert(const TKey& key, const TNode& value)
	{
		unsigned long hashValue = _hashFunc(key);
		TblNode<TKey, TNode>* prev = NULL;
		TblNode<TKey, TNode>* currentNode = NULL;

		switch (_strategy)
		{
		case Settings::Strategy::Chaining:
		{
			currentNode = _tbl[hashValue];

			//Is under the generated index a node and have a DIFFERENT key?
			while (currentNode != NULL
				&& currentNode->GetKey() == key)
			{
				prev = currentNode;
				currentNode = currentNode->GetNext();
			}

			if (currentNode == NULL)
			{
				currentNode = new TblNode<TKey, TNode>(key, value, false);
				_nodesCounter++;
				if (prev == NULL)
				{
					_tbl[hashValue] = currentNode;
				}
				else
				{
					//if predecessor exists, we create a chain
					prev->SetNext(currentNode);
				}
			}//No node found under given index
			else
			{
				currentNode->SetValue(value);
			}
			break;
		}

		case Settings::Strategy::LinearProbing:
		{
			currentNode = new TblNode<TKey, TNode>(key, value, false);

			//Search for an unused slot
			int avoidInfiniteLoopCounter = 0;
			while (_tbl[hashValue] != NULL &&
				_tbl[hashValue]->GetKey() != key &&
				_tbl[hashValue]->IsDummy() == false)
			{
				hashValue++;//we go further...this is occupied!
				hashValue = hashValue % _hashTblSize;//size is the limit!

				avoidInfiniteLoopCounter++;
				if (avoidInfiniteLoopCounter > _hashTblSize)
				{
					break;
				}

			}

			//increase the current number of nodes  if new node is going to be inserted
			if (_tbl[hashValue] == NULL || _tbl[hashValue]->IsDummy() == true)
			{
				_nodesCounter++;
				_tbl[hashValue] = currentNode;
			}
			else
			{
				_nodesCounter--;
				delete currentNode;
				_tbl[hashValue] = _dummyToMarkDeletion;
			}
			break;
		}

		case Settings::Strategy::DoubleHashing:
		{
			//collision! occupied!
			if (_tbl[hashValue] != NULL &&
				_tbl[hashValue]->IsDummy() != false)
			{
				int secondHashValue = _alternativeHashFuncForCollisions(key);//secondary hash function

				int probes = 1;
				while (true)
				{
					int newCalculatedIndex = (hashValue + probes * secondHashValue) % _hashTblSize;

					if (_tbl[newCalculatedIndex]->IsDummy() == true)
					{
						_tbl[newCalculatedIndex] = new TblNode<TKey, TNode>(key, value, false);
						_nodesCounter++;
						break;
					}
					probes++;

					if (probes >= _hashTblSize)
					{
						std::cout << "Number of collision handling:: " << probes << std::endl;
						return;
					}
				}
			}
			else//no collision!
			{
				_tbl[hashValue] = new TblNode<TKey, TNode>(key, value, false);
				_nodesCounter++;
			}
			break;
		}

		default:
			break;
		}
	}

	void Print(int from, int to)
	{
		std::cout << "Printing from " << from << " to " << to << "." << std::endl;
		for (int i = from; i < to; i++)
		{
			TblNode<TKey, TNode>* node = _tbl[i];
			if (node != NULL && !node->IsDummy())
			{
				std::cout << "val:" << node->GetValue() << "  key:" << node->GetKey() << " " << " index:" << i << " isDummy:" << node->IsDummy() << std::endl;
			}
		}
		std::cout << std::endl << std::endl;
	}

	void TryRemove(const TKey& key)
	{
		unsigned long hashValue = _hashFunc(key);
		TblNode<TKey, TNode>* prev = NULL;
		TblNode<TKey, TNode>* currentNode = _tbl[hashValue];

		switch (_strategy)
		{
		case Settings::Strategy::Chaining:
		{
			//Is under the generated index a node and have a DIFFERENT key?
			while (currentNode != NULL &&
				currentNode->GetKey() != key)
			{
				prev = currentNode;
				currentNode = currentNode->GetNext();
			}

			if (currentNode == NULL)
			{
				std::cout << "Couldnt remove node with given id. Node with given key doesnt exist: " << key << std::endl;
				return;
			}
			else
			{
				if (prev == NULL)
				{
					_tbl[hashValue] = currentNode->GetNext();
				}
				else
				{
					//we update the predecessor if it does exists..
					prev->SetNext(currentNode->GetNext());
				}
				delete currentNode;
				_nodesCounter--;
			}
			break;
		}

		case Settings::Strategy::LinearProbing:
		{
			currentNode = _tbl[hashValue];

			int avoidInfiniteLoopCounter = 0;
			while (currentNode != NULL)
			{
				//if node found 
				if (currentNode->GetKey() == key)
				{
					//dummy insertion ! (instead of a real deletion of the node)
					delete currentNode;
					_tbl[hashValue] = _dummyToMarkDeletion;
					_nodesCounter--;
					return;
				}
				hashValue++;
				hashValue = hashValue % _hashTblSize;

				avoidInfiniteLoopCounter++;
				if (avoidInfiniteLoopCounter > _hashTblSize)
				{
					break;
				}

			}
			break;
		}

		case Settings::Strategy::DoubleHashing:
		{
			int stepSize = _alternativeHashFuncForCollisions(key);
			int index = hashValue;

			currentNode = _tbl[index];

			while (currentNode != NULL)
			{
				if (currentNode->IsDummy() == false &&
					currentNode->GetKey() == key)
				{
					delete _tbl[index];
					_tbl[index] = _dummyToMarkDeletion;
					_nodesCounter--;
					return;
				}

				index = (index + stepSize) % _hashTblSize;
				if (index == hashValue)
				{
					break;
				}
			}
			break;
		}
		}
	}

	void ModuloInActionTest()
	{
		int someValue = 0;
		for (int i = 0; i < 2000; i++)
		{
			someValue++;
			someValue = someValue % 1000;
			std::cout << someValue << std::endl;
		}
	}

private:

	TblNode<TKey, TNode>** _tbl;
	THashFunc _hashFunc;
	AlternativeHashingFunctionInteger _alternativeHashFuncForCollisions;
	int _hashTblSize;
	int _nodesCounter;
	Settings::Strategy _strategy = Settings::Chaining;

	//used for indicating that node has been deleted
	TblNode<TKey, TNode>* _dummyToMarkDeletion = new TblNode<TKey, TNode>(true);
};