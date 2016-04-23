#pragma once

#include <cstdint>

using byte = std::uint8_t;

byte const DEFAULT_HEIGHT = 1;

template <class T>
class Node
{
	template <class V>
	friend class AVLTree;
public:
	Node(T const & value);
	Node(Node const & node);
	~Node();

private:
	Node * left_child;
	Node * right_child;
	T value;
	byte height;
};

template <typename T>
class AVLTree
{
public:
	AVLTree();
	AVLTree(AVLTree const & avl_tree);
	~AVLTree();

	void insert(T const & value);
	void remove(T const & value);
	bool exists(T const & value) const;
	void clear();

private:

	Node<T> * root;
	size_t tree_size;

	byte insert(Node<T> *& node , T const & value);
	byte remove(Node<T> *& node , T const & value);
	bool exists(Node<T> * node , T const & valeu) const;
};

template<class T>
inline Node<T>::Node(T const & value)
	: value(value) , height(DEFAULT_HEIGHT) , left_child(nullptr) , right_child(nullptr)
{
}

template<class T>
inline Node<T>::Node(Node const & node)
	: value(node.value) , height(node.height) 
	, left_child((node.left_child == nullptr) ? nullptr : new Node(node.left_child)) 
	, right_child((node.right_child == nullptr) ? nullptr : new Node(node.right_child))
{
}

template<class T>
inline Node<T>::~Node()
{
	if (left_child != nullptr)
		delete left_child;
	if (right_child != nullptr)
		delete right_child;
}

template<typename T>
inline byte AVLTree<T>::insert(Node<T>*& node , T const & value)
{
	if (node == nullptr)
	{
		node = new Node<T>(value);
		++tree_size;
		return 1;
	}
	if (node->value == value)
		return 0;
	byte child_height;
	if (value < node->value)
		child_height = insert(node->left_child , value);
	else
		child_height = insert(node->right_child , value);
	if (child_height == node->height)
		++node->height;
	return node->height;
}

template<typename T>
inline bool AVLTree<T>::exists(Node<T> * node , T const & value) const
{
	if (node == nullptr)
		return false;
	if (value == node->value)
		return true;
	if (value < node->value)
		return exists(node->left_child , value);
	else
		return exists(node->right_child , value);
}

template<typename T>
inline byte AVLTree<T>::remove(Node<T>*& node , T const & value)
{
	if (node == nullptr)
		return 0;
	if (value == node->value)
	{

		--tree_size;
		return DEFAULT_HEIGHT;
	}
	if (value < node->value)
		remove(node->left_child , value);
	else
		remove(node->right_child , value);
}

template<typename T>
inline AVLTree<T>::AVLTree()
	: root(nullptr) , tree_size(0)
{
}

template<typename T>
inline AVLTree<T>::AVLTree(AVLTree const & avl_tree)
	: root(new Node<T>(avl_tree.root)) , tree_size(avl_tree.tree_size)
{
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	delete root;
}

template<typename T>
void AVLTree<T>::insert(T const & value)
{
	insert(root , value);
}

template<typename T>
inline void AVLTree<T>::remove(T const & value)
{
	remove(root , value);
}

template<typename T>
inline bool AVLTree<T>::exists(T const & value) const
{
	exists(root , value);
}

template<typename T>
inline void AVLTree<T>::clear()
{
	delete root;
	tree_size = 0;
}