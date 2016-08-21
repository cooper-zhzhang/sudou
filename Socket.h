#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket
{
private:
	int domain;
	int type;
	int protocol;
	union
	{
		struct sockaddr addr_un;
		struct sockaddr_in addr_in;
		struct sockaddr_in6 addr_in6;
	}addr;

public:
	Socket(int value_domain, int value_type, int value_protocol);
	void Socket::setaddr(sockaddr *value_addr, size_t size);
	int Socket::setbind();
	int Socket::getsock();
};


