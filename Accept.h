#ifndef ACCEPT_h
#define ACCEPT_h
class Accept
{
public:
	Accept(int value_domain, int value_fd);
	int getclientfd();
	//int getclientaddr();
	void setfd();
	int setaccept();

private:
	int clientfd;
	int domain;
	int fd;
	union
	{
		struct sockaddr_un addr_un;
		struct sockaddr_in addr_in;
		struct sockaddr_in6 addr_in6;
	}addr;

};

#endif
