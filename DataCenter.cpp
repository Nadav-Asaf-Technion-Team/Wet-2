#include "DataCenter.h"

DataCenter::DataCenter(int id) : id(id) {
	traffic_servers = new AVLTree();
}

DataCenter::~DataCenter() {
	delete traffic_servers;
}

int DataCenter::GetTreeSize() {
	return traffic_servers->GetSize();
}

AVLTree* DataCenter::GetTree() {
	return traffic_servers;
}

void DataCenter::SetTree(AVLTree* new_tree) {
	traffic_servers = new_tree;
}