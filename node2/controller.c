#include "controller.h"
#include <stdio.h>

int Kp = 5;
int Ki = 1;
int Tt = 20/1000;

unsigned long total_error = 0;

int controller(int reference, int encoder_value) {
	int e = reference - encoder_value;
	total_error = total_error + e;
	unsigned int u = Kp*e + Tt*Ki*total_error;
	int k_ledd = Kp*e;
	int i_ledd = Tt*Ki*total_error;
	printf("total_error: %lu K-ledd: %d I-ledd: %d ", total_error, k_ledd, i_ledd);
	return u;
}
