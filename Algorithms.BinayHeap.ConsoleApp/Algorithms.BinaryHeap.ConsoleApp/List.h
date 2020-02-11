#pragma once

#include "Node.h"

template <typename TNode>
class List
{

private:
	TNode* _head, * _tail;
	int _nodesCount;

public:

	List()
	{
		_head = NULL;
		_tail = NULL;
		_nodesCount = 0;
	}

	~List()
	{
		TNode* curr = _head;
		while (curr != NULL)
		{
			TNode* _next = curr->_next;
			delete curr;
			curr = _next;
		}

		_head = NULL;
		_tail = NULL;
		_nodesCount = 0;
	}

	void InsertNode(TNode* node)
	{

		if (_head == NULL)
		{
			_head = node;
			_tail = node;
			_nodesCount++;
			return;
		}

		_tail->_next = node;
		_tail = node;
		_nodesCount++;
	}

	void InsertNodeAtBeggining(TNode* node)
	{
		node->_next = _head;
		_head = node;
		_nodesCount++;
	}

	int Count()
	{
		return _nodesCount;
	}

	void Display()
	{
		TNode* temp = _head;
		while (temp != NULL)
		{
			std::cout << temp->_value << "\t";
			temp = temp->_next;
		}
	}

	void SwapNodes(int childrenX, int parentY)
	{
		if (childrenX == parentY || childrenX > Count() - 1 || parentY > Count() - 1)
		{
			return;
		}

		// Search for children
		TNode* followerX = NULL, * currentX;
		currentX = _head;
		int i = 0;

		while (currentX != NULL)
		{
			if (i == childrenX)
			{
				break;
			}
			else
			{
				followerX = currentX;
				currentX = currentX->_next;
				i++;
			}
		}


		// Search for parent
		TNode* followerY = NULL, * currentY;
		currentY = _head;
		int j = 0;
		while (currentY != NULL)
		{
			if (j == parentY)
			{
				break;
			}
			else
			{
				followerY = currentY;
				currentY = currentY->_next;
				j++;
			}
		}

		if (currentX == NULL || currentY == NULL)
		{
			return;
		}

		//follower is null, which means that the current
		//we make new head
		if (followerX != NULL)
		{
			if (followerX->_next == _tail)
			{
				_tail = currentY;
			}
			followerX->_next = currentY;//swapping next
		}
		else
		{
			_head = currentY;
		}

		if (followerY != NULL)
		{
			if (followerY->_next == _tail)
			{
				_tail = currentX;
			}
			followerY->_next = currentX;//swapping next
		}
		else
		{
			// follower is null, which means that the current is head
			//we make new head
			_head = currentX;
		}

		//we're at the end
		if (currentX->_next == NULL)
		{
			_tail = currentY;
		}

		if (currentY->_next == NULL)
		{
			_tail = currentX;
		}

		// Swap next pointers  
		TNode* temp = currentY->_next;
		currentY->_next = currentX->_next;
		currentX->_next = temp;
	}

	bool Exists(TNode* node)
	{
		Node* current = _head;

		while (current != NULL)
		{
			if (current->node == node)
			{
				return true;
			}
			current = current->_next;
		}
		return false;
	}

	void DeleteNode(TNode* nodeToBeDeleted)
	{
		//if head needs to be deleted
		if (_head == nodeToBeDeleted)
		{
			if (_head->_next == NULL)
			{
				//The list cannot be made empty!
				return;
			}

			//rearrange head with next
			//head has value from next
			//nodeToBeDeleted is ponting to next
			_head->_value = _head->_next->_value;
			nodeToBeDeleted = _head->_next;
			_head->_next = _head->_next->_next;

			// releasing the memory
			delete nodeToBeDeleted;
			_nodesCount--;
			return;
		}

		TNode* prev = _head;

		//We iterate until NULL or if nodeToBeDeleted is found
		while (prev->_next != NULL)
		{
			prev = prev->_next;

			if (prev->_next == nodeToBeDeleted)
			{
				prev = prev->_next;
				break;
			}
		}

		// Is it null?
		if (prev->_next == NULL)
		{
			return;
		}

		// Remove node from List  
		prev->_next = prev->_next->_next;

		//Release the memory
		delete nodeToBeDeleted;
		_nodesCount--;
		return;
	}

	bool IsHead(TNode* node)
	{
		return node == _head;
	}

	TNode* GetNodeAt(int index)
	{
		if (_head == NULL)
		{
			return NULL;
		}

		if (index > _nodesCount - 1)
		{
			return NULL;
		}

		TNode* temp = _head;
		for (int i = 0; i <= index; i++)
		{
			if (i == index)
			{
				return temp;
			}
			temp = temp->_next;
		}
		return temp;
	}

	void DeleteNode(int index)
	{
		//If is empty 
		if (_head == NULL)
		{
			return;
		}

		if (index > _nodesCount - 1)
		{
			return;
		}

		TNode* temp = _head;

		// head is going to be removed!
		if (index == 0)
		{
			_head = temp->_next;
			delete temp;
			_nodesCount--;
			return;
		}

		// Find prev node of the node to be deleted
		for (int i = 0; temp != NULL &&
			i < index - 1; i++)
		{
			temp = temp->_next;
		}

		// temp->next is the node to be deleted 
		TNode* _next = temp->_next->_next;

		// Unlink the node from linked list and release
		delete temp->_next;
		_nodesCount--;
		temp->_next = _next;  // Unlink the deleted node from list 
	}
};
