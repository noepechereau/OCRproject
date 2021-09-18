#include <stdio.h>
#include "sudoku.h"

int main () 
{
	int grid[9][9] = 
	{
		{9,0,0,1,0,0,0,0,5},
		{0,0,5,0,9,0,2,0,1},
		{8,0,0,0,4,0,0,0,0},
		{0,0,0,0,8,0,0,0,0},
		{0,0,0,7,0,0,0,0,0},
		{0,0,0,0,2,6,0,0,9},
		{2,0,0,3,0,0,0,0,6},
		{0,0,0,2,0,0,9,0,0},
		{0,0,1,9,0,4,5,7,0},
	};
	/*
	printf ("%d\n",absentOnLine( 4, grid, 0)) ;
	
	printf ("%d\n",absentOnColumn( 4, grid, 4)) ;
	
	printf ("%d\n",absentOnBlock( 2, grid, 4,4)) ;
	
	printGrid(grid);
	*/
	printf("Grid before : \n");
	printGrid(grid);
	printf("\n");
	isValid(grid, 0) ;
	
	printf("Final Grid ! \n");
	printGrid(grid);
	printf("\n");
	
	
	
	
	
return 0;


}
