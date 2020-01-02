#pragma once

//T need to be a pointer...?
template <class T>
class Node {
public:
	Node* father;
	int ID;
	int size;
	T data;
	Node(int ID,T data);
};

template <class T>
class UnionFind {
private:
	Node<T>** array;
	int size;
public:
	UnionFind(int size);
	~UnionFind();
	Node<T>* Find(int ID);
	Node<T>* Union(int ID1, int ID2);
	void insert(int ID, T data);
	void print();
};

