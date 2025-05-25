#include <stdio.h>
#include <math.h>

//extern float asm_func(float inp);
//extern float func1(float inp);


double c_function(double inp) {
	double res = 0;

	if (inp != 0) {
		//res = (tan(inp) + sin(inp)) / exp(inp);
		res = (sin(inp)/cos(inp) + sin(inp)) / exp(inp);
	}
	return res;
}



