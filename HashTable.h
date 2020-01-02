#pragma once
template <class T>
class Node {
public:
	T* data;
	int ID;
	Node* next;
	Node* prev;
	Node(T* data, int ID);
	~Node();
	Node* endOfList();
};

template<class T>
class hashTable {
private:
	Node<T>** array;
	int size;
	int actualSize;
public:
	hashTable(int size);
	~hashTable();
	T* find(int ID);
	void add(T* data, int ID);
	void remove(int ID);
	int getSize();
	bool isEmpty();
};