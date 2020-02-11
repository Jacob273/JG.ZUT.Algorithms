#pragma once

template <typename TValue>
struct Node
{
	Node<TValue>(TValue value)
	{
		_value = value;
		_next = NULL;
	}

	TValue _value;
	Node<TValue>* _next;
};