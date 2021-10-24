#include <stdio>
#include <stdlib> 
#include "matrix.h"

int main () {
	int t1[2][2] = {{1,2},{3,4}} ;
	int t2[2][2] = {{3,4},{1,2}} ;
	
	res = matrixMult(t1,t2) ;
	
	for ( int i = 0 ; i < res[0].length ; i ++ ) 
	{
		for ( int j = 0 ; j < res.length ; j ++ )
		{
			printf("%d"+" " (res[i][j]));
		}
		printf("\d");
	}
}
	
	
