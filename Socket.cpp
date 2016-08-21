#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Socket.h"

Socket::Socket(int value_domain, int value_type, int value_protocol):domain(value_domain), type(value_type), protocol(value_protocol)
{
	fd = socket(domain, type, protocol);
	memset(&addr, 0, sizeof(addr));
}

void Socket::setaddr(sockaddr *value_addr, size_t size)
{
	switch(domain)
	{
		case AF_UNIX: memcpy(&addr.addr_un, value_addr, size); break;
		case AF_INET: memcpy(&addr.addr_in, value_addr, size); break;
		case AF_INET6: memcpy(&addr.addr_in6, value_addr, size); break;
	}
}

int Socket::setbind()
{
	switch(domain)
	{
		case AF_UNIX: return bind(fd, (sockaddr*)&(addr.addr_un), sizeof(addr.addr_un));
		case AF_INET: return bind(fd, (sockaddr*)&(addr.addr_in), sizeof(addr.addr_in));
		case AF_INET6: return bind(fd, (sockaddr*)&(addr.addr_in6), sizeof(addr.addr_in6));
		default: return -1;
	}
}

int Socket::getsock()
{
	return fd;
}


