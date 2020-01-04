#pragma once
template <class T>
class ChainNode {
public:
	T* data;
	int ID;
	ChainNode* next;
	ChainNode* prev;
	ChainNode(T* data, int ID);
	~ChainNode();
	ChainNode* endOfList();
};

template<class T>
class hashTable {
private:
	ChainNode<T>** array;
	int size;
	int actualSize;
	ChainNode<T>* findNode(int ID);
public:
	hashTable(int size);
	~hashTable();
	T* find(int ID);
	void add(T* data, int ID);
	void remove(int ID);
	int getSize();
	bool isEmpty();
	void print();
};