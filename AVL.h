#include <iostream>
#include "Server.h"

class Node {
public:
	int key;
	Server* data;
	int height;
	Node* left;
	Node* right;
	int subtree_size;
	int traffic_sum;
	Node(int key, Server* data);
};

class AVLTree {
private:
	Node* root;
public:
	AVLTree();
	~AVLTree();
	void AddServer(Server* data);
	Server* FindServer(int key); //need to fix this and use in RemoveNode
	int SumHighestTraffics(int k);
	void RemoveNode(Server* data);
	int GetSize();
	void PrintTree();
};

