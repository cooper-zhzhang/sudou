#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include "inetaddress.h"
#include "socket.h"

class serversocket
{
public:
	serversocket() = default;
	serversocket(int port);
	serversocket(int port, int backlog);
	serversocket(int port, int backlog, inetaddress, address);

	socket accept();
	inetaddress getinetaddress();
	int getlocalport();
	void bind(socketaddress address);
	bool isbound();
	bool iscolse();
	void close();


};
#endif // SERVERSOCKET_H
