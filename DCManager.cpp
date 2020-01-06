#include "DCManager.h"
using std::cout;
using std::endl;

static bool InRange(int x, int range) {
	return (x > 0 && x <= range);
}

DCManager::DCManager(int n) : UFsize(n) {
	traffic_servers = new AVLTree();
	ServersTable = new hashTable<Server>(n);
	DCs_UF = new UnionFind<DataCenter*>(n);
	for (int i = 1; i <= n; i++) {
		DataCenter* dc = new DataCenter(i);
		DCs_UF->insert(i, dc);
	}
}

DCManager::~DCManager() {
	delete traffic_servers;
	delete DCs_UF;
	delete ServersTable;
}

Status DCManager::MergeDataCenters(int id1, int id2) {
	if (!InRange(id1, UFsize) || !InRange(id2, UFsize))
		return _INVALID_INPUT;
	DataCenter* dc1 = DCs_UF->Find(id1)->data;
	DataCenter* dc2 = DCs_UF->Find(id2)->data;
	AVLTree* t1 = dc1->GetTree();
	AVLTree* t2 = dc2->GetTree();
	DCs_UF->Union(id1, id2);
	AVLTree* newTree = MergeTrees(t1, t2);
	delete t1;
	delete t2;
	dc1->SetTree(NULL);
	dc2->SetTree(NULL);
	DataCenter* dc = DCs_UF->Find(id1)->data;
	dc->SetTree(newTree);
	return _SUCCESS;
}

Status DCManager::AddServer(int DCid, int id) {
	if (!InRange(DCid, UFsize) || id <= 0)
		return _INVALID_INPUT;
	else if (ServersTable->find(id) != NULL)
		return _FAILURE;
	Server* new_server = new Server(id, DCid);
	ServersTable->add(new_server, id);
	return _SUCCESS;
}

Status DCManager::RemoveServer(int id) {
	if (id <= 0)
		return _INVALID_INPUT;
	Server* to_remove = ServersTable->find(id);
	if (to_remove == NULL)
		return _FAILURE;
	if (to_remove->GetTraffic() > 0) {
		DataCenter* dc = DCs_UF->Find(to_remove->GetDCID())->data;
		dc->GetTree()->RemoveNode(to_remove);
		traffic_servers->RemoveNode(to_remove);
	}
	ServersTable->remove(id);
	return _SUCCESS;
}

Status DCManager::SetTraffic(int id, int traffic) {
	if (id <= 0 || traffic < 0)
		return _INVALID_INPUT;
	if (ServersTable->find(id) == NULL)
		return _FAILURE;
	Server* to_set = ServersTable->find(id);
	int DCid = to_set->GetDCID();
	DataCenter* DC = DCs_UF->Find(DCid)->data;
	if (to_set->GetTraffic() > 0) {
		traffic_servers->RemoveNode(to_set);
		DC->GetTree()->RemoveNode(to_set);
	}
	to_set->SetTraffic(traffic);
	if (traffic > 0) {
		traffic_servers->AddServer(to_set);
		DC->GetTree()->AddServer(to_set);
	}
	return _SUCCESS;
}

Status DCManager::SumHighestTrafficServers(int DCid, int k, int* sum) {
	if (k < 0 || DCid < 0 || DCid > UFsize) {
		return _INVALID_INPUT;
	}

	if (DCid == 0) {
		*sum = traffic_servers->SumHighestTraffics(k);
	}
	else {
		DataCenter* DC = DCs_UF->Find(DCid)->data;
		*sum = DC->GetTree()->SumHighestTraffics(k);
	}
	return _SUCCESS;
}
