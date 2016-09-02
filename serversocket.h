#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include "inetaddress.h"

class serversocket
{
public:
	serversocket() = default;
	serversocket(int port);
	serversocket(int port, int backlog);
	serversocket(int port, int backlog, inetaddress, address);
};
#endif // SERVERSOCKET_H
