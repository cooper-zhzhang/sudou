#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Socket.h"

int main(int argc, char **argv)
{
	Socket sock(AF_INET, SOCK_STREAM, 0, (char*)"0.0.0.0", 4444);
	struct sockaddr_in seraddr;
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_port = htons(1024);
	seraddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr);
	sock.setaddr((struct sockaddr*)&seraddr, sizeof(seraddr));
	sock.setbind();
	int fd = sock.getfd();
	std::cout << fd << std::endl;
	return 0;
}

