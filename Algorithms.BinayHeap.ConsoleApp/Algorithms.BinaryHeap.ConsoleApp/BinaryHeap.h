//Kopiec:
//	a) Wartosc klucza przodka(PRZ) jest nie mniejsza niz wartosc klucz jego potomkow
//			 (30) PRZ
//			/	 \ 
//		LP (15)	 (29) PP
//
//	b) Wszystkie poziomy sa wypelnione liscmi, a ostatni od lewej
//	c) Lewy potomek (LP) <= Prawy potomek (PP)
//	d) Dokladnie wywazony: najmniejsza mozliwa liczba poziomow
//	e) Moga istniec	wezly z taka sama wartoscia!
//	f) To taka kolejka...w ktorej wszyscy sa ustawieni wg. wartosci

#include "List.h"
#include "utility"
template <typename TNode>

//Minimum oriented
class BinaryHeap
{
public:

	BinaryHeap()
	{
		_nodesCount = 0;
		_list = new List<TNode>();
	}

	~BinaryHeap()
	{
		delete _list;
		_list = NULL;
	}




	void Insert(TNode* node)
	{
		if (_list == NULL)
		{
			_list = new List<TNode>();
		}

		_list->InsertNode(node);
		int i = _list->Count() - 1;//we start from the end

		//std::cout << std::endl <<  "prev " << std::endl;
		//_list->Display();
		//std::cout << std::endl;

		//Przekopcowanie
		while (GetNodeAt(i) != NULL && !_list->IsHead(node) &&
			ParentOf(i)->_value > GetNodeAt(i)->_value)
		{
			int childrenIndex = i;
			int parentIndex = (i - 1) / 2;
			SwapNodes(childrenIndex, parentIndex);
			node = ParentOf(i);
		}
		//std::cout << std::endl << "after " << std::endl;
		//_list->Display();
	}

	// Method to remove minimum element (or root) from min heap 
	void RemoveRoot()
	{
		if (_list->Count() <= 0)
			return;

		_list->DeleteNode(0);
		ConvertMin(0);
	}

	void Clear()
	{
		delete _list;
		_list = NULL;
	}

	void Display()
	{
		TNode* temp = GetNodeAt(0);
		while (temp != NULL)
		{
			std::cout << temp->_value << "  ";
			temp = temp->_next;
		}
	}


private:

	List<TNode>* _list;
	int _nodesCount;

	void SwapNodes(int child, int parent)
	{
		_list->SwapNodes(child, parent);
	}

	TNode* ParentOf(int index)
	{
		return _list->GetNodeAt((index - 1) / 2);
	}

	TNode* GetNodeAt(int index)
	{
		return _list->GetNodeAt(index);
	}

	void ConvertMin(int index)
	{
		int leftIndex = (2 * index + 1);
		int rightIndex = (2 * index + 2);
		int smallest = index;

		if (leftIndex < _list->Count() && _list->GetNodeAt(leftIndex)->_value < _list->GetNodeAt(smallest)->_value)
		{
			smallest = leftIndex;
		}

		if (rightIndex < _list->Count() && _list->GetNodeAt(rightIndex)->_value < _list->GetNodeAt(smallest)->_value)
		{
			smallest = rightIndex;
		}

		if (smallest != index)
		{
			_list->SwapNodes(index, smallest);
			ConvertMin(smallest);
		}
	}


};