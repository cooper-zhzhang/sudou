#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Socket.h"

Socket::Socket(int value_domain, int value_type, int value_protocol, char *str, int value_port):domain(value_domain), type(value_type), protocol(value_protocol)
{
	fd = socket(domain, type, protocol);
	memset(&addr, 0, sizeof(addr));
	switch(domain)
	{
		case AF_UNIX: addr.addr_un.sun_family = value_domain; memcpy(addr.addr_un.sun_path, str, sizeof(addr.addr_un.sun_path)); break;
		case AF_INET: addr.addr_in.sin_family = value_domain; addr.addr_in.sin_port = htons(value_port); inet_pton(value_domain, str, &(addr.addr_in.sin_addr));
		case AF_INET6: addr.addr_in6.sin6_family = value_domain; addr.addr_in6.sin6_port = htons(value_port); inet_pton(value_domain, str, &(addr.addr_in6.sin6_addr));
		default: return;
	}

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

int Socket::getfd()
{
	return fd;
}

int Socket::setlisten(int backlog)
{
	return listen(fd, backlog);
}



