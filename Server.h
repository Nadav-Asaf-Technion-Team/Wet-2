#include <iostream>
#include <algorithm>

class Server {
private:
	int id;
	int traffic;
	int DC_id;
public:
	Server(int id, int DC_id);
	~Server() = default;
	int GetID();
	int GetTraffic();
	int GetDCID();
};