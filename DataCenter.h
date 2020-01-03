#ifndef DATACENTER_H_
#include "AVL.h"

class DataCenter {
private:
	int id;
	AVLTree* traffic_servers;
public:
	DataCenter(int id); //alocates empty tree.
	~DataCenter(); //should delete tree
	int GetTreeSize(); //returns size of tree of servers with traffic
	AVLTree* GetTree(); //returns a pointer to the tree of the DC. 
	void SetTree(AVLTree* new_tree); //sets a new tree for the DC to point to.
};

#endif


