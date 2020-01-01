#include "AVL.h"

int main() {
	Server* s1 = new Server(1, 1);
	Server* s2 = new Server(2, 1);
	Server* s3 = new Server(3, 1);
	Server* s4 = new Server(4, 1);
	Server* s5 = new Server(5, 1);
	Server* s6 = new Server(6, 1);
	Server* s7 = new Server(7, 1);
	s1->SetTraffic(1);
	s2->SetTraffic(2);
	s3->SetTraffic(3);
	s4->SetTraffic(3);
	s5->SetTraffic(5);
	s6->SetTraffic(6);
	s7->SetTraffic(7);
	AVLTree* test_tree = new AVLTree();
	return 0;
}

//#include "UnionFind.h"
//
//int main() {
//	UnionFind<int>* UN;
//	UN = new UnionFind<int>(10);
//	UN->print();
//	UN->Union(1, 2);
//	UN->Union(3, 4);
//	UN->Union(3, 2);
//	UN->Union(6, 9);
//	UN->Union(9, 5);
//	UN->Union(1, 9);
//	UN->Union(7, 8);
//	UN->print();
//}