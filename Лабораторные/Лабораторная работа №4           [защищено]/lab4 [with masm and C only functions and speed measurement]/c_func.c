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

double* c_func_c_only(double* inp_arr, int size) {
	double res[11];
	double* ptr;
	int i;
	for (i = 0; i < 11; i++) {
		ptr = inp_arr + i;
		*ptr = (sin(inp_arr[i]) / cos(inp_arr[i]) + sin(inp_arr[i])) / exp(inp_arr[i]);
	}

	return res;
}



