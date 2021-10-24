#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errx.h>

#include "MathsFunc.h"
#include "Types.h"

int main(int argc, char *argv)
{
	if (argc != 3)
	{
		errx(1, "2 arguments are required");
	}
	
	double x = argv[1];
	double y = argv[2];
	
	double *hInputs = {x, y};
	Node h = newNode(hInputs, 2);
	
	double *zInputs = {x, y, n->activation};
	Node z = newNode(hInputs, 3);
}
