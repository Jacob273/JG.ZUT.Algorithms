#pragma once

#include "iostream"

template <typename TKey, typename TNode>
class TblNode
{

public:
	TblNode(const TKey& key, const TNode& value, bool isDummy) :
		_key(key), _value(value), _next(NULL), _isDummy(isDummy)
	{

	}

	TblNode(bool isDummy) : _isDummy(isDummy)
	{

	}

	TKey GetKey()
	{
		return _key;
	}

	TNode GetValue()
	{
		return _value;
	}

	void SetValue(TNode _value)
	{
		TblNode::_value = _value;
	}

	TblNode* GetNext()
	{
		return _next;
	}

	void SetNext(TblNode* _next)
	{
		TblNode::_next = _next;
	}

	bool IsDummy()
	{
		return _isDummy;
	}

private:
	TKey _key;
	TNode _value;
	TblNode* _next;
	bool _isDummy;
};

