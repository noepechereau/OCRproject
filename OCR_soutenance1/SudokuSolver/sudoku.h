#ifndef sudoku_h
#define sudoku_h

int absentOnLine(int k, int grid[9][9] , int i );
int absentOnColumn(int k, int grid[9][9] , int j);
int absentOnBlock(int k, int grid[9][9] , int i, int j);
void printGrid( int grid[9][9] );
int isValid (int grid[9][9], int pos);
int DemoSolver();

#endif
