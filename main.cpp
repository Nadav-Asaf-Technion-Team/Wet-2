//#include "UnionFind.h"
//#include "AVL.h"
//#include "DataCenter.h"
//#include "HashTable.h"
//using std::cout;
//using std::endl;
//
//
//////testing HashTable
////int main() {
////	hashTable<int>* table;
////	table = new hashTable<int>(10);
////	table->print();
////	int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
////	table->add(a, 0);
////	table->add(a+1, 2);
////	table->add(a + 2, 12);
////	table->add(a + 3, 11);
////	table->add(a + 4, 100);
////	table->add(a + 5, 7);
////	table->add(a + 6, 6);
////	table->add(a + 7, 122);
////	table->add(a + 8, 4);
////	table->print();
////	table->add(a + 9, 9);
////	table->print();
////	table->remove(0);
////	table->remove(4);
////	table->remove(6);
////	table->remove(122);
////	table->print();
////	table->remove(100);
////	table->print();
////}
//
////// testing UnionFind
////int main() {
////	UnionFind<int>* UN;
////	UN = new UnionFind<int>(10);
////	UN->print();
////	UN->Union(1, 2);
////	UN->Union(3, 4);
////	UN->Union(3, 2);
////	UN->Union(6, 9);
////	UN->Union(9, 5);
////	UN->Union(1, 9);
////	UN->Union(7, 8);
////	UN->print();
////}
//
//
//////testing AVLtree
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
//	AVLTree* test_tree2 = new AVLTree();
//	test_tree->AddServer(s5);
//	test_tree->AddServer(s2);
//	test_tree->AddServer(s8);
//	test_tree->AddServer(s1);
//	test_tree->AddServer(s4);
//	test_tree->AddServer(s6);
//	test_tree2->AddServer(s10);
//	test_tree2->AddServer(s3);
//	test_tree2->AddServer(s7);
//	test_tree2->AddServer(s9);
//	test_tree2->AddServer(s12);
//	test_tree2->AddServer(s11);
//	test_tree->PrintTree();
//	cout << "========================================================" << endl;
//	test_tree2->PrintTree();
//	cout << "========================================================" << endl;
//	AVLTree* test_tree3 = MergeTrees(test_tree, test_tree2);
//	delete test_tree;
//	delete test_tree2;
//	test_tree3->PrintTree();
//	cout << "========================================================" << endl;
//	delete test_tree3;
//}
////
////	DataCenter* test_dc = new DataCenter(1);
////	test_dc->SetTree(test_tree);
////	cout << test_dc->GetTreeSize() << "\n";
////	cout << test_dc->GetTree()->SumHighestTraffics(3);
////	return 0;
////}