#include "sudoku.h"

Sudoku::Sudoku(int ValueElement[])
{
	int i;
	int j;
	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
			Sudoku::element[i][j] = ValueElement[i * 9 + j];
}

int* Sudoku::GetResult()
{
	return (int*)element;
}

bool Sudoku::IsSudoku()
{
	int i;
	int j;
	for(i = 0; i < 9; ++i)
		for(j = 0; j < 9; ++j)
		{
			if(check(i, j, Sudoku::element[i][j]) == false)
				return false;
		}

		return true;
}

void Sudoku::Solve()
{
	fill(1);
}

bool Sudoku::check(int x, int y, int b)
{
	int i;
	int j;
	for(j = 0; j < 9; ++j)
	 {
		 if(j != x)
		{
			if(b == element[j][y])
				return false;
		}

		if(j != y)
		{
			if(b == element[x][j])
				return false;
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
			if(b == element[i][j])
				return false;
		}
		return true; 
}

bool Sudoku::fill(int count)
{
	int i;
	int x;
	int y;
	if(count > 81)
		return true;
	x = (count - 1) / 9;
	y = (count - 1) % 9;

	if(element[x][y] != 0)
	{
		if(fill(count+1))
			return true;
		return false;
	}
	else
	{
		for(i = 1; i <= 9; ++i)
		{
			if(check(x, y, i))
			{
				element[x][y] = i;
				if(fill(count+1))
					return true;
				element[x][y] = 0;
			}
		}
	}
		return false;
}


