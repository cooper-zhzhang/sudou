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
	
	while(waitpid(-1, NULL, WNOHANG) > 0);
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

//	printf("%d %d %p \n", x, y, &a[0][0]);
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
	int serfd;
	int clifd;
	int num = 0;
	int a[9][9];
	int mes[MAX_MES];

	/*for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
		{
			scanf("%d", &a[i][j]);
			if(a[i][j] != 0)
				sum++;
		}
	
	printf("begin:\n");
	int count = 1;
	if(fun(a, count))
	{
		printf("answer:\n");
		for(i = 0; i < 9; ++i)
		{
			for(j = 0; j < 9; ++j)
			{
				printf("%2d", a[i][j]);
			}
			printf("\n");
		}
	}
	else
		printf("no answer\n");
		*/
	
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle;
	if(sigaction(SIGCHLD, &sa, NULL) == -1)
		exit(-1);

	serfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	//inet_pton(AF_INET, "127.0.0.1", &(seraddr.sin_addr));
	inet_pton(AF_INET, "0.0.0.0", &(seraddr.sin_addr));
	seraddr.sin_port = htons(PORT);
	
	if(bind(serfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
	{
		printf("bind error\n");
		exit(-1);
	}

	if(listen(serfd, 5) == -1)
	{
		printf("listen error\n");
		exit(-1);
	}

	while(1)
	{
		clifd = accept(serfd, NULL, NULL);
		switch(fork())
		{
			case -1:
				printf("fork error\n");
				exit(-1);
			case 0:
				close(serfd);
				if((num = read(clifd, mes, sizeof(int) * MAX_MES)) == -1)
				{
					printf("%ld read error\n", (long)getpid());
					exit(-1);
				}
				//memcpy(a, mes, num);
				for(int i = 0; i < 81; ++i)
				{
					a[i/9][i%9] = ntohs(mes[i]);
				}

				if(fun(a, 1))
				{
				//memcpy(mes, a, num);
					for(int i = 0; i < 81; ++i)
					{
						mes[i] = htons(a[i/9][i%9]);
					}
				}
				if((num = write(clifd, mes, sizeof(int) * MAX_MES)) == -1)
				{
					printf("%ld write error\n", (long)getpid());
					exit(-1);
				}
				exit(0);
			
			default:
				close(clifd);
				break;
		}
	}

	
	return 0;
}
	
