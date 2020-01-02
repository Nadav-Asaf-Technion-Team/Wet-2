#include <iostream>
#include <math.h>
#include "HashTable.h"

template<class T>
Node<T>::Node(T* data, int ID): data(data),ID(ID), next(NULL), prev(NULL){}

template<class T>
Node<T>::~Node() {
	delete data;
}

template <class T>
Node<T>* Node<T>::endOfList() {
	Node<T>* res = *this;
	while (res->next != NULL) {
		res = res->next;
	}
	return res;
}

static int hash(int num, int size) {
	return num % size;
}
template <class T>
hashTable<T>::hashTable(int size): size(size), actualSize(0){
	array = new Node<T>*[size];
}

template <class T>
hashTable<T>::~hashTable() {
	for (int i = 0; i < size; i++) {
		delete array[i];
	}
	delete[] array;
}

template<class T>
T* hashTable<T>::find(int ID) {
	Node** temp = array[hash(ID, size)];
	while (temp->ID != ID && temp != NULL) {
		temp = temp->next;
	}
	return temp;
}
	
template<class T>
static void resizeAndRehash(Node<T>** oldArray, int oldSize, int newSize) {
	Node<T>** newArray = new Node<T>*[newSize];
	for (int i = 0; i < oldSize; i++) {
		if (newArray[hash(i, newSize)] == NULL) {
			newArray[hash(i, newSize)] = oldArray[hash(i, oldSize)];
		}
		else {
			newArray[hash(i, newSize)]->endOfList()->next = oldArray[hash(i, oldSize)];
		}
	}
	delete[] oldArray;
	oldArray = newArray;
}


//does not allow duplicate IDs
template <class T>
void hashTable<T>::add(T* data, int ID) {
	if (find(ID) != NULL) return;
	Node<T>* tempNode = new Node<T>(data);
	array[hash(ID, size)]->endOfList()->next = tempNode;
	actualSize++;
	if (actualSize == size) {
		resizeAndRehash(array, size, size * 2);
		size = size * 2;
	}

}

template <class T>
void hashTable<T>::remove(int ID) {
	if (find(ID) == NULL) return;
	//deleting node
	actualSize--;
	 if (actualSize <= size / 4) {
		resizeAndRehash(array, size, size / 2);
		size = size / 2;
	}
}

template<class T>
int hashTable<T>::getSize() {
	return size;
}

template<class T>
bool hashTable<T>::isEmpty() {
	return (size == 0);
}