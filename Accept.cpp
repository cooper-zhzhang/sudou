#include "Accept.h"
#include <sys/socket.h>

int Accept::Accept(int value_domain, int value_fd): domain(value_domain), fd(value_fd), clientds(0){}

void Accept::setfd(value_fd)
{
	fd = value_fd;
}

int Accept::getclientfd()
{
	return clientfd;
}

int Accept::setaccept()
{
	return clientfd = accept(fd, NULL, NULL);
}


 
