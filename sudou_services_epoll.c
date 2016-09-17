#include <sys/epoll.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_MES 81
#define PORT 4096

void handle(int sig)
{

}

int check(int (*a)[9], int x, int y, int b)
{
	int i;
	int j;
	for(j = 0; j < 9; ++j)
	 {
		 if(j != x)
		{
			if(b == a[j][y])
				return 0;
		}

		if(j != y)
		{
			if(b == a[x][j])
				return 0;
		}

	}

	i = x - x % 3;
	j = y - y % 3;
	int loo1 = i;
	int loo2 = j;

	for(i = loo1; i < loo1 + 3; ++i)
		for(j = loo2; j < loo2 + 3; ++j)
		{
			if(i == x && j == y)
				continue;
			if(b == a[i][j])
				return 0;
		}
		return 1;
}

int fun(int (*a)[9], int count)
{
	int i;
	int x;
	int y;
	if(count > 81)
		return 1;
	x = (count - 1) / 9;
	y = (count - 1) % 9;

	if(a[x][y] != 0)
	{
		if(fun(a, count+1))
			return 1;
		return 0;
	}
	else
	{
		for(i = 1; i <= 9; ++i)
		{
			if(check(a, x, y, i))
			{
				a[x][y] = i;
				if(fun(a, count+1))
					return 1;
				a[x][y] = 0;
			}
		}
	}
		return 0;
}

int main(int argc, char **argv)
{
	int i;
	int ready;
	int epfd;
	int serfd;
	int clifd;
	int num = 0;
	int a[9][9];
	int mes[MAX_MES];
	struct epoll_event ev;
	struct epoll_event evlist[100];

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle;
	if(sigaction(SIGPIPE, &sa, NULL) == -1)
		exit(-1);

	serfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	inet_pton(AF_INET, "0.0.0.0", &(seraddr.sin_addr));
	seraddr.sin_port = htons(PORT);
	
	if(bind(serfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
	{
		printf("bind error\n");
		exit(-1);
	}

	if(listen(serfd, 10) == -1)
	{
		printf("listen error\n");
		exit(-1);
	}

	epfd = epoll_create(100);
	ev.events = EPOLLIN;
	ev.data.fd = serfd;
	if(-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, serfd, &ev))
	{
		printf("epoll_ctl() error\n");
		exit(-1);
	}

	while(1)
	{

		if((ready = epoll_wait(epfd, evlist, 100, -1)) == -1)
		{
			printf("epoll_wait() error\n");
			exit(-1);
		}

		for(int j = 0; j < ready; ++j)
		{
			if(serfd == evlist[j].data.fd)//if fd is service socket serfd, will accept connection
			{
				clifd = accept(serfd, NULL, NULL);
				ev.events = EPOLLIN | EPOLLOUT;
				ev.data.fd = clifd;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clifd, &ev);
				continue;
			}

			clifd = evlist[j].data.fd;
			if(evlist[j].events & EPOLLIN)
			;
			else
				continue;
			if(clifd < 0)
				continue;
			else
			{

				num = read(clifd, mes, sizeof(int) * MAX_MES);
				if(num == -1)
				{
					printf("read() error \n");
					exit(-1);
				}
				if(num == 0)//client socket has colsed
				{
					continue;
					close(clifd);
				}

				for(i = 0; i < 9; ++i)
				{
					for(j = 0; j < 9; ++j)
					{
						a[i][j] = ntohs(mes[i * 9 + j]);
					}
				}

				fun(a, 1);

				for(i = 0; i < 9; ++i)
				{
					for(j = 0; j < 9; ++j)
					{
						mes[i * 9 + j] = htons(a[i][j]);
					}
				}

				if(-1 == write(clifd, mes, sizeof(int) * MAX_MES))
				{
					printf("server write error\n");
					printf("errno: %d\n", errno);
					exit(-1);
				}
//			close(clifd);
			}
		}

	}

	
	return 0;
}
	
