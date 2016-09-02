#ifndef SOCKET_H
#define SOCKET_H
#include <string>
#include "inetaddress.h"
#include <iostream>

class socket
{
public:
	socket(string host, int port);
	socket(inetaddress host, in tport);
	inetaddress getinetaddress();
	int getlocalport();
	istream& getinputstream();
	ostream& ouputstream();
	void close();
};

#endif //socket.h
