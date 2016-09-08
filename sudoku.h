#ifndef SUDOKU_H
#define SUDOKU_H

#define MAX_SUDOKU 81

class Sudoku
{
public:
	Sudoku(int ValueElement[]);
	bool IsSudoku();
	void Solve();
	int* GetResult();

private:
	bool check(int x, int y, int b);
	bool fill(int count);
	int element[9][9];
};

#endif //SUDOKU_H
