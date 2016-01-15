//Precomputed Sin and Cos functions for HW LUT implementation
#include "cosLUT.h"
#include "hw_trig.h"
//#include "stdio.h"


//hw_sin(k,N) = sin(2*pi*k/N)
short hw_sin(short k){
	return sinLUT[k];
}

//hw_cos(k,N) = cos(2*pi*k/N)
short hw_cos(short k){
	return cosLUT[k];
}

