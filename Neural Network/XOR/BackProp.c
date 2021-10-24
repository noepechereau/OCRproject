#include <stdio.h>
#include <stdlib.h>

#include "Types.h"

double delta(double error, double output, double v)
{
	return error * output * v;
}
