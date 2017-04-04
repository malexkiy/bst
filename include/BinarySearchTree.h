#pragma once

#include <iostream>
#include <fstream>

template <typename T>
struct Node {
	Node *leftNode;
	Node *rightNode;
	T value;
	unsigned int level;

	Node()
	{
		value = 0;
		level = 0;
		leftNode = nullptr;
		rightNode = nullptr;
	}


	Node(T value)
	{
		this->value = value;
		level = 0;
		leftNode = nullptr;
		rightNode = nullptr;
	}


	Node(T value, Node* leftNode, Node* rightNode)
	{
		this->value = value;
		level = 0;
		this->leftNode = leftNode;
		this->rightNode = rightNode;
	}
};


template <typename T>
class BinarySearchTree
{
private:
	Node<T>* _root;
	unsigned int _height;

	void _insertElement(Node<T>*, T);
	bool _findElement(const Node<T>*, const T&) const;
	void _deleteElements(Node<T>*);
	Node<T>* _deleteElement(Node<T>*, const T&);

	std::ostream& _inorderTraversal(std::ostream&, const Node<T>*) const;
	std::ostream& _preorderTraversal(std::ostream&, const Node<T>*) const;
	std::ostream& _postorderTraversal(std::ostream&, const Node<T>*) const;

	Node<T>* min(Node<T>*) const;

	unsigned int _count(const Node<T>*) const;

	unsigned int count() const;
	unsigned int height() const;

public:
	BinarySearchTree();
	~BinarySearchTree();
	
	void insertElement(T);
	bool findElement(const T&) const;
	void deleteElement(const T&);

	std::ostream& inorderTraversal(std::ostream&) const;
	std::ostream& preorderTraversal(std::ostream&) const;
	std::ostream& postorderTraversal(std::ostream&) const;

	template <typename T>
	friend std::ifstream& operator>>(std::ifstream&, BinarySearchTree<T>&);
	template <typename T>
	friend std::ofstream& operator<<(std::ofstream&, const BinarySearchTree<T>&);

	template <typename T>
	friend std::ostream& operator<<(std::ostream&, const BinarySearchTree<T>&);

};


template <typename T>
T max(T a, T b)
{
	return (a > b ? a : b);
}


template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	_root = nullptr;
	_height = 0;
}


template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	_deleteElements(_root);
}


template <typename T>
unsigned int BinarySearchTree<T>::height() const
{
	return _height;
}


template <typename T>
unsigned int BinarySearchTree<T>::_count(const Node<T>* r) const
{
	if (!r)
		return 0;

	return (r->leftNode != 0) + (r->rightNode != 0) + _count(r->leftNode) + _count(r->rightNode);
}


template <typename T>
unsigned int BinarySearchTree<T>::count() const
{
	if (_root)
		return _count(_root) + 1;
	return 0;
}


template <typename T>
void BinarySearchTree<T>::_insertElement(Node<T>* r, T val)
{
	if (val < r->value)
	{
		if (r->leftNode == nullptr)
		{
			r->leftNode = new Node<T>(val);
			r->leftNode->level = r->level + 1;
			_height = max(_height, r->leftNode->level);
		}
		else
			_insertElement(r->leftNode, val);
	}
	else
	{
		if (r->rightNode == nullptr)
		{
			r->rightNode = new Node<T>(val);
			r->rightNode->level = r->level + 1;
			_height = max(_height, r->rightNode->level);
		}
		else
			_insertElement(r->rightNode, val);
	}
}


template <typename T>
void BinarySearchTree<T>::insertElement(T val)
{
	if (_root == nullptr)
	{
		_root = new Node<T>(val);
	}
	else
		_insertElement(_root, val);
}


template <typename T>
bool BinarySearchTree<T>::_findElement(const Node<T>* r, const T& val) const
{
	if (!r)
		return false;
	if (r->value == val)
		return true;

	if (val < r->value)
		return _findElement(r->leftNode, val);
	else
		return _findElement(r->rightNode, val);
}


template <typename T>
bool BinarySearchTree<T>::findElement(const T& val) const
{
	if (!_root)
		throw "Binary Search Tree is empty\n";

	return _findElement(_root, val);
}


template <typename T>
std::ostream& BinarySearchTree<T>::_inorderTraversal(std::ostream& os, const Node<T>* r) const
{
	if (r)
	{
		_inorderTraversal(os, r->leftNode);
		os << r->value << " ";
		_inorderTraversal(os, r->rightNode);
	}
	return os;
}


template <typename T>
std::ostream& BinarySearchTree<T>::inorderTraversal(std::ostream& os) const
{
	if (!_root)
		throw "Binary Search Tree is empty\n";

	return _inorderTraversal(os, _root);
}


template <typename T>
std::ostream& BinarySearchTree<T>::_preorderTraversal(std::ostream& os, const Node<T>* r) const
{
	if (r)
	{
		os << r->value << " ";
		_preorderTraversal(os, r->leftNode);
		_preorderTraversal(os, r->rightNode);
	}
	return os;
}


template <typename T>
std::ostream& BinarySearchTree<T>::preorderTraversal(std::ostream& os) const
{
	if (!_root)
		throw "Binary Search Tree is empty\n";

	return _preorderTraversal(os, _root);
}


template <typename T>
std::ostream& BinarySearchTree<T>::_postorderTraversal(std::ostream& os, const Node<T>* r) const
{
	if (r)
	{
		_postorderTraversal(os, r->leftNode);
		_postorderTraversal(os, r->rightNode);
		os << r->value << " ";
	}
	return os;
}


template <typename T>
std::ostream& BinarySearchTree<T>::postorderTraversal(std::ostream& os) const
{
	if (!_root)
		throw "Binary Search Tree is empty\n";

	return _postorderTraversal(os, _root);
}


template <typename T>
std::ifstream& operator>>(std::ifstream& is, BinarySearchTree<T>& bst)
{
	unsigned int count;
	T el;
	is >> count;

	if (bst._root)
	{
		bst._deleteElements(bst._root);
		bst._root = nullptr;
		bst._height = 0;
	}

	while (count--)
	{
		is >> el;
		bst.insertElement(el);
	}
	return is;
}


template <typename T>
std::ofstream& operator<<(std::ofstream& os, const BinarySearchTree<T>& bst)
{
	if (!bst._root)
		throw "Binary Search Tree is empty\n";

	os << bst.count() << " ";
	bst.preorderTraversal(os);
	return os;
}


template <typename T>
std::ostream& printV(std::ostream& os, const Node<T>* r)
{
	if (!r)
		return os;

	printV(os, r->rightNode);
	for (unsigned int i = 0; i < r->level; i++)
		os << "\t";
	os << r->value << std::endl;
	printV(os, r->leftNode);

	return os;
}


template <typename T>
std::ostream& printH(std::ostream& os, const Node<T>* r, unsigned int level, unsigned int width)
{
	if (!r)
		return os;

	if (level == 1)
	{
		/*for (unsigned int i = 0; i < width; i++)
			os << "    ";*/
		os << r->value << " ";
		/*for (unsigned int i = 0; i < width; i++)
			os << "    ";*/
	}
	else if (level > 1)
	{
		printH(os, r->leftNode, level - 1, width);
		printH(os, r->rightNode, level - 1, width);
	}

	return os;
}


template <typename T>
Node<T>* BinarySearchTree<T>::min(Node<T>* r) const
{
	if(!r->leftNode)
		return r;

	return min(r->leftNode);
}


template <typename T>
void BinarySearchTree<T>::_deleteElements(Node<T>* r)
{
	if (!r)
		return;

	_deleteElements(r->leftNode);
	_deleteElements(r->rightNode);

	delete r;
	r = nullptr;
}


template <typename T>
Node<T>* BinarySearchTree<T>::_deleteElement(Node<T>* r, const T& val)
{
	if (!r)
		return r;

	if (val < r->value)
		r->leftNode = _deleteElement(r->leftNode, val);

	else if (val > r->value)
		r->rightNode = _deleteElement(r->rightNode, val);

	else if (r->leftNode && r->rightNode)
	{
		r->value = min(r->rightNode)->value;
		r->rightNode = _deleteElement(r->rightNode, r->value);
	}

	else
	{
		if (r->leftNode)
			r = r->leftNode;
		else
			r = r->rightNode;
	}
	return r;
}


template <typename T>
void BinarySearchTree<T>::deleteElement(const T& val)
{
	_deleteElement(_root, val);
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst)
{
	if (!bst._root)
		throw "Binary Search Tree is empty\n";

	/*printV(os, bst._root);*/
	for (unsigned int i = 1; i <= bst._height + 1; i++)
	{
		printH(os, bst._root, i, (1 << (bst._height - i + 1)));
		os << std::endl;
	}

	return os;
}

