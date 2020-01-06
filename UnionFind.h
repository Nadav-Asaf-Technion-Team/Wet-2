#pragma once

//T need to be a pointer
template <class T>
class UFNode {
public:
	UFNode* father;
	int ID;
	int size;
	T data;
	UFNode(int ID,T data);
	~UFNode();
};

template <class T>
class UnionFind {
private:
	UFNode<T>** array;
	int size;
public:
	UnionFind(int size);
	~UnionFind();
	UFNode<T>* Find(int ID);
	UFNode<T>* Union(int ID1, int ID2);
	void insert(int ID, T data);
	void print();
};

