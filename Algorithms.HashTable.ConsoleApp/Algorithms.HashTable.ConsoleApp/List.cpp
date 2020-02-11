#include "List.h"
#include<iostream>

using namespace std;
using namespace JG_Collections;

List::List()
{
	_head = NULL;
	_tail = NULL;
	_hashTblSize = 0;
}

List::~List()
{
	Node* curr = _head;
	while (curr != NULL)
	{
		Node* _next = curr->_next;
		delete curr;
		curr = _next;
	}

	_head = NULL;
	_tail = NULL;
	_hashTblSize = 0;
}

void List::InsertNode(int _key)
{
	Node* temp = new Node();
	temp->_key = _key;
	temp->_next = NULL;

	if (_head == NULL)
	{
		_head = temp;
		_tail = temp;
		temp = NULL;
		_hashTblSize++;
		return;
	}

	_tail->_next = temp;
	_tail = temp;
	_hashTblSize++;
}

void List::Display()
{
	Node* temp = new Node();
	temp = _head;
	while (temp != NULL)
	{
		cout << temp->_key << "\t";
		temp = temp->_next;
	}
}

void List::InsertNodeAtBeggining(int _key)
{
	Node* temp = new Node();
	temp->_key = _key;

	temp->_next = _head;
	_head = temp;
	_hashTblSize++;
}

bool List::Exists(int _key)
{
	Node* current = _head;

	while (current != NULL)
	{
		if (current->_key == _key)
		{
			return true;
		}
		current = current->_next;
	}
	return false;
}

void List::DeleteNode(Node* nodeToBeDeleted)
{
	// IF head needs to be deleted
	if (_head == nodeToBeDeleted)
	{
		if (_head->_next == NULL)
		{
			//The list can't be made empty!
			return;
		}

		_head->_key = _head->_next->_key;
		nodeToBeDeleted = _head->_next;
		_head->_next = _head->_next->_next;

		// releasing the memory
		delete nodeToBeDeleted;
		_hashTblSize--;
		return;
	}

	Node* prev = _head;

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
	_hashTblSize--;
	return;
}

void List::DeleteNode(int positionToBeDeleted)
{
	// If linked list is empty 
	if (_head == NULL)
	{
		return;
	}

	if (positionToBeDeleted > _hashTblSize - 1)
	{
		return;
	}

	Node* temp = _head;

	// Head is going to be removed!
	if (positionToBeDeleted == 0)
	{
		_head = temp->_next;
		delete temp;
		_hashTblSize--;
		return;
	}

	// Find previous node of the node to be deleted
	for (int i = 0; temp != NULL &&
		i < positionToBeDeleted - 1; i++)
	{
		temp = temp->_next;
	}

	// temp->next is the node to be deleted 
	Node* _next = temp->_next->_next;

	// Unlink the node from linked list 
	//Release
	delete temp->_next;
	_hashTblSize--;
	temp->_next = _next;  // Unlink the deleted node from list 
}
