#include "UnionFind.h"

int main() {
	UnionFind<int>* UN;
	UN = new UnionFind<int>(10);
	UN->print();
	UN->Union(1, 2);
	UN->Union(3, 4);
	UN->Union(3, 2);
	UN->Union(6, 9);
	UN->Union(9, 5);
	UN->Union(1, 9);
	UN->Union(7, 8);
	UN->print();
}

//#include "AVL.h"
//
//int main() {
//	Server* s1 = new Server(1, 1);
//	Server* s2 = new Server(2, 1);
//	Server* s3 = new Server(3, 1);
//	Server* s4 = new Server(4, 1);
//	Server* s5 = new Server(5, 1);
//	Server* s6 = new Server(6, 1);
//	Server* s7 = new Server(7, 1);
//	Server* s8 = new Server(8, 1);
//	Server* s9 = new Server(9, 1);
//	Server* s10 = new Server(10, 1);
//	Server* s11 = new Server(11, 1);
//	Server* s12 = new Server(12, 1);
//	s1->SetTraffic(1);
//	s2->SetTraffic(2);
//	s3->SetTraffic(3);
//	s4->SetTraffic(4);
//	s5->SetTraffic(5);
//	s6->SetTraffic(6);
//	s7->SetTraffic(7);
//	s8->SetTraffic(8);
//	s9->SetTraffic(9);
//	s10->SetTraffic(10);
//	s11->SetTraffic(11);
//	s12->SetTraffic(12);
//	AVLTree* test_tree = new AVLTree();
//	test_tree->AddServer(s5);
//	test_tree->AddServer(s2);
//	test_tree->AddServer(s8);
//	test_tree->AddServer(s1);
//	test_tree->AddServer(s4);
//	test_tree->AddServer(s6);
//	test_tree->AddServer(s10);
//	test_tree->AddServer(s3);
//	test_tree->AddServer(s7);
//	test_tree->AddServer(s9);
//	test_tree->AddServer(s12);
//	test_tree->AddServer(s11);
//	test_tree->PrintTree();
//	return 0;
//}