#include "library2.h"
#include "DCManager.h"

void* Init(int n) {
	DCManager* DS = new DCManager(n);
	return (void*)DS;
}

StatusType MergeDataCenters(void* DS, int dataCenter1, int dataCenter2) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		return (StatusType)(((DCManager*)DS)->MergeDataCenters(dataCenter1, dataCenter2));
	}
	catch (std::bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

StatusType AddServer(void* DS, int dataCenterID, int serverID) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		return (StatusType)(((DCManager*)DS)->AddServer(dataCenterID, serverID));
	}
	catch (std::bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

StatusType RemoveServer(void* DS, int serverID) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		return (StatusType)(((DCManager*)DS)->RemoveServer(serverID));
	}
	catch (std::bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

StatusType SetTraffic(void* DS, int serverID, int traffic) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		return (StatusType)(((DCManager*)DS)->SetTraffic(serverID, traffic));
	}
	catch (std::bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

StatusType SumHighestTrafficServers(void* DS, int dataCenterID, int k, int* traffic) {
	if (DS == NULL)
		return INVALID_INPUT;
	try {
		return (StatusType)(((DCManager*)DS)->SumHighestTrafficServers(dataCenterID, k, traffic));
	}
	catch (std::bad_alloc) {
		return ALLOCATION_ERROR;
	}
}

void Quit(void** DS) {
	delete ((DCManager*)* DS);
	*DS = NULL;
}


