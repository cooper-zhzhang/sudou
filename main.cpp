#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Socket.h"

int main(int argc, char **argv)
{
	int mes[10];
	int num;
	Socket sock(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in seraddr;
	memset(&seraddr, 0, sizeof(seraddr));
	seraddr.sin_port = htons(1024);
	seraddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr);
	sock.setaddr((struct sockaddr*)&seraddr, sizeof(seraddr));
	sock.setbind();
	int fd = sock.getsock();
//	std::cout << fd << std::endl;
	if(-1 !=  listen(fd, 5))
		std::cout << "listen success" << std::endl;
	int clifd;
	if(-1 != (clifd = accept(fd, NULL, NULL)))
		std::cout << "accept success" << std::endl;
	if((num = read(clifd, mes, sizeof(mes))) != -1)
	{
		for(int i = 0; i < num/sizeof(int); ++i)
		std::cout << mes[i] << std::endl;
	}
	else
		std::cout << "rev mes error" << std::endl;
	return 0;
}

