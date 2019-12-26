#include "AVL.h"
#include <iostream>
#include <math.h>

template <class T>
Node<T>::Node(int key, T data) :
	key(key), data(data), height(0), left(NULL), right(NULL) {
}

template <class T>
AVLTree<T>::AVLTree() : root(NULL), size(0), height(-1) {}

template <class T>
static void PostOrderDelete(Node<T>* node) {
	if (!node) return;
	PostOrderDelete(node->left);
	PostOrderDelete(node->right);
	delete node;
}

template <class T>
AVLTree<T>::~AVLTree() {
	PostOrderDelete(root);
}

template <class T>
static Node<T>* rotateLL(Node<T>* root) {
	Node<T>* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root->height -= 2;
	return newRoot;
}


template <class T>
static Node<T>* rotateRR(Node<T>* root) {
	Node<T>* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root->height -= 2;
	return newRoot;
}

template <class T>
static Node<T>* rotateLR(Node<T>* root) {
	Node<T>* newRoot = root->left->right;
	root->left->right = newRoot->left;
	newRoot->left = root->left;
	root->left = newRoot->right;
	newRoot->right = root;
	root->height -= 2;
	newRoot->height += 1;
	return newRoot;
}

template <class T>
static Node<T>* rotateRL(Node<T>* root) {
	Node<T>* newRoot = root->right->left;
	root->right->left = newRoot->right;
	newRoot->right = root->right;
	root->right = newRoot->left;
	newRoot->left = root;
	root->height -= 2;
	newRoot->height += 1;
	return newRoot;
}

template <class T>
Node<T>* CheckAndRotate(Node<T>* root) {
	if (root->left->height - root->right->height == 2) {
		if (root->left->left->height - root->left->right->height >= 0)
			return rotateLL(root);
		else return rotateLR(root);
	}
	else if (root->left->height - root->right->height == -2) {
		if (root->right->left->height - root->right->right->height <= 0)
			return rotateRR(root);
		else return rotateRL(root);
	}
	else
		return root;
}

template <class T>
Node<T>* insert(int key, T data, Node<T>* root) {
	if (!root) {
		root = new Node<T>;
		root->data = data;
		root->key = key;
	}
	else if (key < root->key) {
		root->left = insert(key, data, root->left);
		root = CheckAndRotate(root);
	}
	else if (key > root->key) {
		root->right = insert(key, data, root->right);
		root = CheckAndRotate(root);
	}
	root->height = max(root->left->height, root->right->height) + 1;
	return root;
	
}

template <class T>
void AVLTree<T>::AddNode(int key, T data) {
	if (FindNode(key)); //return failure
	insert(key, data, root);
}


// TODO: static find min and max
// TODO: static get balance factor
// TODO: rotation
