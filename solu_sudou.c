#include <stdio.h>

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
	int a[9][9];
	int i;
	int j;

	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
		{
			scanf("%d", &a[i][j]);
		}
	
	printf("begin:\n");
	if(fun(a, 1))
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
	return 0;
}
