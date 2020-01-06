#include "AVL.h"
#include "HashTable.h"
#include "UnionFind.h"
#include "DataCenter.h"
#include "ReturnValues.h"

class DCManager {
private:
	AVLTree* traffic_servers;
	hashTable<Server>* ServersTable;
	UnionFind<DataCenter*>* DCs_UF;
	int UFsize;
public:
	DCManager(int n);
	~DCManager();
	Status MergeDataCenters(int id1, int id2);
	Status AddServer(int DCid, int id);
	Status RemoveServer(int id);
	Status SetTraffic(int id, int traffic);
	Status SumHighestTrafficServers(int DCid, int k, int* sum);
};