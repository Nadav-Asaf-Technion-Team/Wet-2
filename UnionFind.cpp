#include <iostream>
#include <math.h>
#include "UnionFind.h"
#include "DataCenter.h"

using std::cout;
using std::cin;
using std::endl;

template <class T>
UFNode<T>::UFNode(int ID, T data):
	father(NULL), ID(ID), size(1), data(data) {
}

template <class T>
UFNode<T>::~UFNode(){
	delete data;
}

template <class T>
UnionFind<T>::UnionFind(int size) : size(size) {
	array = new UFNode<T>*[size];
	for (int i = 0; i < size; i++) {
		array[i] = new UFNode<T>(i, NULL);
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
UFNode<T>* UnionFind<T>::Find(int ID) {
	UFNode<T>* node = array[ID];
	if (node->father == NULL) return node;
	UFNode<T>* anccestor = node;
	UFNode<T>* temp = node->father;
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
UFNode<T>* UnionFind<T>::Union(int ID1, int ID2) {
	UFNode<T>* node1 = Find(ID1);
	UFNode<T>* node2 = Find(ID2);
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
	Find(ID - 1)->data = data;
}

template <class T>
void UnionFind<T>::print() {
	cout << "the singeltons are:" << endl;
	for (int i = 0; i < size; i++) {
		UFNode<T>* temp = array[i];
		cout << '{' << temp->ID;
		cout << '}';
	}
	cout << endl;
	cout << "the groups are:" << endl;
	UFNode<T>** tempArray = new UFNode<T>*[size];
	for (int k = 0; k < size; k++) {
		tempArray[k] = array[k];
	}
	for (int i = 0; i < size; i++) {
		while (tempArray[i] == NULL) i++;
		if (i >= size) break;
		cout << '{';
		UFNode<T>* node = tempArray[i];
		UFNode<T>* common_anccestor = node;
		UFNode<T>* temp = node->father;
		while (common_anccestor->father != NULL) {
			common_anccestor = common_anccestor->father;
		}
		;
		for (int j = i; j < size; j++) {
			while (tempArray[j] == NULL) j++;
			if (j >= size) break;
			UFNode<T>* anccestor = tempArray[j];
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

template class UnionFind<DataCenter*>;
