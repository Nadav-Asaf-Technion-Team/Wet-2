#include <iostream>
#include <math.h>
#include "HashTable.h"
#include "Server.h"
using std::cout;
using std::endl;


template<class T>
ChainNode<T>::ChainNode(T* data, int ID): data(data),ID(ID), next(NULL), prev(NULL){}

template<class T>
ChainNode<T>::~ChainNode() {
	delete data;
}

template <class T>
ChainNode<T>* ChainNode<T>::endOfList() {
	ChainNode<T>* res = this;
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
	array = new ChainNode<T>*[size];
	for (int i = 0; i < size; i++) {
		array[i] = NULL;
	}
}

template <class T>
hashTable<T>::~hashTable() {
	for (int i = 0; i < size; i++) {
		if (array[i] == NULL) continue;
		ChainNode<T>* temp = array[i]->endOfList();
		while (temp != array[i])
		{
			temp = temp->prev;
			delete temp->next;
		}
		delete array[i];
	}
	delete[] array;
}


template<class T>
ChainNode<T>* hashTable<T>::findNode(int ID) {
	ChainNode<T>* temp = array[hash(ID, size)];
	while (temp != NULL && temp->ID != ID ) {
		temp = temp->next;
	}
	return temp;
}

template<class T>
T* hashTable<T>::find(int ID) {
	ChainNode<T>* temp = findNode(ID);
	if (temp == NULL)
		return NULL;
	return temp->data;
}

//need revisment
template<class T>
static void resizeAndRehash(ChainNode<T>** &oldArray, int oldSize, int newSize) {
	ChainNode<T>** newArray = new ChainNode<T> * [newSize];
	for (int i = 0; i < newSize; i++) {
		newArray[i] = NULL;
	}
	ChainNode<T>* temp = NULL;
	for (int i = 0; i < oldSize; i++) {
		temp = oldArray[i];
		while (temp != NULL) {
			//first node in list
			if (newArray[hash(temp->ID, newSize)] == NULL) {
				newArray[hash(temp->ID, newSize)] = temp;
				temp->prev = NULL;	
			}
			//adding node to an existing list
			else {
				temp->prev = newArray[hash(temp->ID, newSize)]->endOfList();
				newArray[hash(temp->ID, newSize)]->endOfList()->next = temp;
			}
			temp = temp->next;
			//cutting from former chain
			if(temp != NULL) temp->prev->next = NULL;
		}
	}
	delete[] oldArray;
	oldArray = newArray;
}


//does not allow duplicate IDs
template <class T>
void hashTable<T>::add(T* data, int ID) {
	if (findNode(ID) != NULL) return;
	ChainNode<T>* tempNode = new ChainNode<T>(data, ID);
	if (array[hash(ID, size)] == NULL) {
		array[hash(ID, size)] = tempNode;
	}
	else {
		tempNode->prev = array[hash(ID, size)]->endOfList();
		array[hash(ID, size)]->endOfList()->next = tempNode;
	}
	actualSize++;
	if (actualSize == size) {
		resizeAndRehash(array, size, size * 2);
		size = size * 2;
	}

}

template <class T>
void hashTable<T>::remove(int ID) {
	ChainNode<T>* temp = findNode(ID);
	if (temp == NULL) return;
	//	middle of the list
	if (temp->prev != NULL && temp->next != NULL) {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	// beggining of the list
	else if (temp->prev == NULL  && temp->next != NULL) {
		array[hash(ID, size)] = temp->next;
		temp->next->prev = NULL;
	}
	// end of the list
	else if (temp->prev != NULL && temp->next == NULL) {
		temp->prev->next = NULL;
	}
	// only one object in list
	else {
		array[hash(ID, size)] = NULL;
	}
	delete temp;
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

template<class T>
void hashTable<T>::print(){
	cout << "HashTable status:" << endl;
	cout << "-----------------" << endl;
	cout << "size: " << size << endl << "actualSize: " << actualSize << endl;
	for (int i = 0; i < size; i++) {
		cout << "[ID:" << i << "|";
		if (array[i] == NULL) {
			cout << "NULL";
		}
		else{
			ChainNode<T>* temp = array[i];
			while (temp != NULL) {
				cout << temp->ID;
				temp = temp->next;
				if (temp != NULL) cout << "->";
			}
		}
		cout << "]" << endl;
	}
	cout << "-----------------" << endl;
}

template class hashTable<Server>;
