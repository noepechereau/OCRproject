#include <stdio.h>
#include <stdlib.h>
#include "matrix.h" 

int matrixMult( int m1[2][2], int m2[2][2])
{ 
	int res[2][2];
	for ( int i = 0 ; i < 2 ; i ++ )
		{
			for ( int j = 0 ; j < 2 ; j ++ )
				{
					for ( int k = 0 ; k < 2 ; k ++ ) 
						{
							res[i][j] += m1[i][k] * m2[k][j] ;
						}
				}
		}
	return res;
}

				
		
int main () {
	int t1[2][2] = {{1,2},{3,4}} ;
	int t2[2][2] = {{3,4},{1,2}} ;
	
	int res[2][2] = matrixMult(t1,t2) ;
	
	for ( int i = 0 ; i < 2 ; i ++ ) 
	{
		for ( int j = 0 ; j < 2 ; j ++ )
		{
			printf("%d  ", (res[i][j]));
		}
		printf("\d");
	}
}
