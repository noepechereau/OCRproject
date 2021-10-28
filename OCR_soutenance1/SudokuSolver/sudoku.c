#include "sudoku.h"
#include <stdbool.h>
#include <stdio.h>

enum Bool { False = 0, True = 1 };


int absentOnLine( int k, int grid[9][9], int i)
{
	for ( int j = 0 ; j <= 8 ; j++)
	{
		if (grid[i][j] == k)
		{
			return 0;
		}
	}
	return 1;
}


int absentOnColumn( int k, int grid[9][9], int j)
{
	for ( int i = 0 ; i <= 8 ; i++)
	{
		if (grid[i][j] == k)
		{
			return 0;
		}
	}
	return 1;
}		


int absentOnBlock( int k, int grid[9][9], int i , int j )
{
	int i2 = i - (i%3);
	int j2 = j - (j%3);
	
	for ( i = i2 ; i < i2 + 3 ; i++)
	{
		for ( j = j2 ; j < j2 + 3 ; j++ )
		{
			if (grid[i][j] == k)
			{
				return 0;
			}
		}
	}
	return 1;
}

int isValid(int grid[9][9] , int pos ) 
{
	if ( pos == 82 )
	{
		return 1;
	}
	
	int i = pos/9 ;
	int j = pos%9 ;
	
	if ( grid[i][j] != 0 )
	{
		return isValid(grid, pos + 1);
	}
	
	for (int k = 1 ; k <= 9 ; k ++ )
	{
		if (absentOnLine(k,grid,i) && absentOnColumn(k,grid,j) && absentOnBlock(k,grid,i,j))
		{
			grid[i][j] = k;
			
			if ( isValid( grid, pos + 1 ))
			{
				return 1;
			}
		}
		
		
	}
	grid[i][j] = 0;
	return 0;
	
}

void printGrid(int grid[9][9])
{
	for (int i=0; i<9; i++)
    	{
		for (int j=0; j<9; j++)
		{
		    printf( ((j+1)%3) ? "%d " : "%d|", grid[i][j]);
		}
		printf("\n");
		if ( i == 2 || i == 5 )
		{
			printf("------------------\n");
		}
	}
}




int DemoSolver() 
{
	printf("\n\n");
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














			
			
			
			
			
			
			
			
			
			
			
			
			
			










