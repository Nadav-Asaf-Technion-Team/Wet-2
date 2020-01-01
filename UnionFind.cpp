#include <iostream>
#include <math.h>
#include "UnionFind.h"

using std::cout;
using std::cin;
using std::endl;

template <class T>
Node<T>::Node(int ID, T data):
	father(NULL), ID(ID), size(1), data(data) {
}

template <class T>
UnionFind<T>::UnionFind(int size) : size(size) {
	array = new Node<T>*[size];
	for (int i = 0; i < size; i++) {
		array[i] = new Node<T>(i, NULL);
	}
}

template <class T>
UnionFind<T>::~UnionFind() {
	for (int i = 0; i < size; i++) {
		delete (array[i]);
		delete[] array;
	}
}

template <class T>
Node<T>* UnionFind<T>::Find(int ID) {
	Node<T>* node = array[ID];
	if (node->father == NULL) return node;
	Node<T>* anccestor = node;
	Node<T>* temp = node->father;
	while (anccestor->father != NULL) {
		anccestor = anccestor->father;
	}
	while (node->father != anccestor) {
		temp = node->father;
		node->father = anccestor;
		node = temp;
	}
	return anccestor;
}

template<class T>
Node<T>* UnionFind<T>::Union(int ID1, int ID2) {
	Node<T>* node1 = Find(ID1);
	Node<T>* node2 = Find(ID2);
	if (node1 == node2) return node1;
	if (node1->size >= node2->size) {
		node1->size += node2->size;
		node2->father = node1;
		return node1;
	}
	node2->size += node1->size;
	node1->father = node2;
	return node2;
}

template <class T>
void UnionFind<T>::insert(int ID, T data) {
	Find(ID)->data = data;
}

template <class T>
void UnionFind<T>::print() {
	cout << "the singeltons are:" << endl;
	for (int i = 0; i < size; i++) {
		Node<T>* temp = array[i];
		cout << '{' << temp->ID;
		cout << '}';
	}
	cout << endl;
	cout << "the groups are:" << endl;
	Node<T>** tempArray = new Node<T>*[size];
	for (int k = 0; k < size; k++) {
		tempArray[k] = array[k];
	}
	for (int i = 0; i < size; i++) {
		while (tempArray[i] == NULL) i++;
		if (i >= size) break;
		cout << '{';
		Node<T>* node = tempArray[i];
		Node<T>* common_anccestor = node;
		Node<T>* temp = node->father;
		while (common_anccestor->father != NULL) {
			common_anccestor = common_anccestor->father;
		}
		;
		for (int j = i; j < size; j++) {
			while (tempArray[j] == NULL) j++;
			if (j >= size) break;
			Node<T>* anccestor = tempArray[j];
			while (anccestor->father != NULL) {
				anccestor = anccestor->father;
			}
			if (anccestor == common_anccestor) {
				if (i != j) cout << ',';
				cout << array[j]->ID;
				tempArray[j] = NULL;
			}
		}
		cout << '}';
	}
	cout << endl;
	delete[] tempArray;
}

template class UnionFind<int>;
