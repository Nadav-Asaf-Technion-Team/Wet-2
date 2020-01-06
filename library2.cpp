#include "library2.h"
#include "DCManager.h"

void* Init(int n) {
	DCManager* DS = new DCManager(n);
	return (void*)DS;
}

StatusType MergeDataCenters(void* DS, int dataCenter1, int dataCenter2) {
	if (DS == NULL)
		return INVALID_INPUT;
	return (StatusType)(((DCManager*)DS)->MergeDataCenters(dataCenter1, dataCenter2));
}

StatusType AddServer(void* DS, int dataCenterID, int serverID) {
	if (DS == NULL)
		return INVALID_INPUT;
	return (StatusType)(((DCManager*)DS)->AddServer(dataCenterID, serverID));
}

StatusType RemoveServer(void* DS, int serverID) {
	if (DS == NULL)
		return INVALID_INPUT;
	return (StatusType)(((DCManager*)DS)->RemoveServer(serverID));
}

StatusType SetTraffic(void* DS, int serverID, int traffic) {
	if (DS == NULL)
		return INVALID_INPUT;
	return (StatusType)(((DCManager*)DS)->SetTraffic(serverID, traffic));
}

StatusType SumHighestTrafficServers(void* DS, int dataCenterID, int k, int* traffic) {
	if (DS == NULL)
		return INVALID_INPUT;
	return (StatusType)(((DCManager*)DS)->SumHighestTrafficServers(dataCenterID, k, traffic));
}

void Quit(void** DS) {
	delete ((DataCenter*)* DS);
	*DS = NULL;
}


