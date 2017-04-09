#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <fstream>


template <typename T>
class BinarySearchTree;

template <typename T>
struct Node;

template <typename T>
std::ostream& operator<<(std::ostream&, const BinarySearchTree<T>&);

template <typename T>
std::ofstream& operator<<(std::fstream&, const BinarySearchTree<T>&);

template <typename T>
std::ifstream& operator>>(std::fstream&, BinarySearchTree<T>&);


template <typename T>
struct Node {
	Node *leftNode;
	Node *rightNode;
	T value;

	Node()
		: value(value), leftNode(nullptr), rightNode(nullptr) {}


	Node(const T& value, Node* leftNode = nullptr, Node* rightNode = nullptr)
		: value(value), leftNode(leftNode), rightNode(rightNode) {}
};


template <typename T>
class BinarySearchTree
{
private:
	Node<T>* _root;

	void _deleteElements(Node<T>*);
	Node<T>* _deleteRoot(Node<T>*);

	unsigned int _count(const Node<T>*) const;

	void swap(BinarySearchTree<T>&);

public:
	BinarySearchTree();
	~BinarySearchTree();

	unsigned int count() const;

	void insertElement(const T&);
	bool findElement(const T&) const;
	void deleteElement(const T&);

	std::ostream& inorderTraversal(std::ostream&) const;
	std::ostream& preorderTraversal(std::ostream&) const;

	std::ifstream& inFile(std::ifstream&);
	std::ofstream& outFile(std::ofstream&) const;

	friend std::ifstream& operator>> <> (std::ifstream&, BinarySearchTree<T>&);

	friend std::ofstream& operator<< <> (std::ofstream&, const BinarySearchTree<T>&);

	friend std::ostream& operator<< <> (std::ostream&, const BinarySearchTree<T>&);

};


template <typename T>
BinarySearchTree<T>::BinarySearchTree()
{
	_root = nullptr;
}


template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	_deleteElements(_root);
}


template <typename T>
void BinarySearchTree<T>::swap(BinarySearchTree<T>& other)
{
	if (_root != other._root)
	{
		Node<T>* tmp = _root;
		_root = other._root;
		other._root = tmp;
	}
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
void BinarySearchTree<T>::insertElement(const T& val)
{
	if (_root)
	{
		Node<T>* cur = _root;

		while (cur)
		{
			if (val < cur->value)
			{
				if (!cur->leftNode)
				{
					cur->leftNode = new Node<T>(val);
					break;
				}
				else
				{
					cur = cur->leftNode;
				}
			}
			else
			{
				if (!cur->rightNode)
				{
					cur->rightNode = new Node<T>(val);
					break;
				}
				else
				{
					cur = cur->rightNode;
				}
			}
		}
	}
	else
	{
		_root = new Node<T>(val);
	}
}


template <typename T>
bool BinarySearchTree<T>::findElement(const T& val) const
{
	if (!_root)
		throw "Binary Search Tree is empty or not initialized\n";

	Node<T>* cur = _root;

	while (cur)
	{
		if (cur->value == val)
			return true;
		if (val < cur->value)
			cur = cur->leftNode;
		else
			cur = cur->rightNode;
	}

	return false;
}


template <typename T>
void BinarySearchTree<T>::_deleteElements(Node<T>* node)
{
	if (!node)
		return;

	_deleteElements(node->leftNode);
	_deleteElements(node->rightNode);

	delete node;
}


template <typename T>
Node<T>* BinarySearchTree<T>::_deleteRoot(Node<T>* head)
{
	Node<T>* cur, *parent;
	cur = head->rightNode;
	if (!cur)
	{
		cur = head->leftNode;
	}
	else
	{
		if (cur->leftNode)
		{
			parent = head;
			while (cur->leftNode)
			{
				parent = cur;
				cur = cur->leftNode;
			}
			parent->leftNode = cur->rightNode;
			cur->rightNode = head->rightNode;
		}
		cur->leftNode = head->leftNode;
	}
	
	delete head;
	return cur;
}


template <typename T>
void BinarySearchTree<T>::deleteElement(const T& val)
{
	Node<T>* cur = _root, *parent;
	if (_root->value == val)
	{
		_root = _deleteRoot(_root);
	}
	else
	{
		parent = _root;
		if (val < parent->value) cur = parent->leftNode;
		else cur = parent->rightNode;
		while (cur)
		{
			if (cur->value == val)
			{
				if (val < parent->value) parent->leftNode = _deleteRoot(parent->leftNode);
				else parent->rightNode = _deleteRoot(parent->rightNode);
				return;
			}
			parent = cur;
			if (val < parent->value) cur = parent->leftNode;
			else cur = parent->rightNode;
		}
	}
}


template <typename T>
std::ostream& BinarySearchTree<T>::inorderTraversal(std::ostream& os) const
{
	if (!_root)
		throw "Binary Search Tree is empty or not initialized\n";

	Node<T>* cur = _root, *pre;

	while (cur)
	{
		if (!cur->leftNode)
		{
			os << cur->value << " ";
			cur = cur->rightNode;
		}
		else
		{
			pre = cur->leftNode;
			while (pre->rightNode && pre->rightNode != cur)
				pre = pre->rightNode;

			if (!pre->rightNode)
			{
				pre->rightNode = cur;
				cur = cur->leftNode;
			}
			else
			{
				pre->rightNode = nullptr;
				os << cur->value << " ";
				cur = cur->rightNode;
			}
		}
	}

	return os;
}


template <typename T>
std::ostream& BinarySearchTree<T>::preorderTraversal(std::ostream& os) const
{
	if (!_root)
		throw "Binary Search Tree is empty or not initialized\n";
	
	Node<T>* root = _root;

	while (root)
	{
		if (!root->leftNode)
		{
			os << root->value << " ";
			root = root->rightNode;
		}
		else
		{
			Node<T>* cur = root->leftNode;
			while (cur->rightNode && cur->rightNode != root)
				cur = cur->rightNode;

			if (cur->rightNode == root)
			{
				cur->rightNode = nullptr;
				root = root->rightNode;
			}
			else
			{
				os << root->value << " ";
				cur->rightNode = root;
				root = root->leftNode;
			}
		}
	}

	return os;
}


template <typename T>
std::ifstream& BinarySearchTree<T>::inFile(std::ifstream& is)
{
	BinarySearchTree<T> other;
	unsigned int count;
	T el;
	is >> count;

	while (count--)
	{
		is >> el;
		other.insertElement(el);
	}

	swap(other);
	return is;
}


template <typename T>
std::ofstream& BinarySearchTree<T>::outFile(std::ofstream& os) const
{
	if (!_root)
		throw "Binary Search Tree is empty or not initialized\n";

	os << count() << " ";
	preorderTraversal(os);

	return os;
}


template <typename T>
std::ifstream& operator>>(std::ifstream& is, BinarySearchTree<T>& bst)
{
	return bst.inFile(is);
}


template <typename T>
std::ofstream& operator<<(std::ofstream& os, const BinarySearchTree<T>& bst)
{
	return bst.outFile(os);
}


template <typename T>
std::ostream& printV(std::ostream& os, const Node<T>* node, unsigned int level)
{
	if (!node)
		return os;

	printV(os, node->rightNode, level + 1);
	for (unsigned int i = 0; i < level; i++)
		os << "\t";
	os << node->value << std::endl;
	printV(os, node->leftNode, level + 1);

	return os;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst)
{
	if (!bst._root)
		throw "Binary Search Tree is empty or not initialized\n";

	printV(os, bst._root, 0);

	return os;
}

#endif
