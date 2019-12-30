#include "Server.h"

Server::Server(int id, int DC_id) : id(id), traffic(0), DC_id(DC_id) {}

int Server::GetID() {
	return id;
}

int Server::GetTraffic() {
	return traffic;
}

int Server::GetDCID() {
	return DC_id;
}
