#include "rdft_ad.h"
#include "hw_trig.h"
#include <limits.h>
#include <time.h>

#define MULT(A,B) ((short)((int)A * B >> 15))

#define _N 8
#define _ANO_W 9
#define _REF_W 33
#define WF 32603
#define NORM_H 164


short hls_top(short x, short dt);

int main() {
    //struct timespec tic, toc;
	int i;
	int count = 15;

    short x_ts[TEST];
    short dt_ts[TEST];
    for (i = 0; i < TEST; i++) {
		/*Generate an Interesting Signal*/
		short dt = i%5 == 0 ? 2 : i%3 == 0 ? 14 : 8;
		short x = i%5 == 0 ? 4 : i%3 == 0 ? 2 : 10;

		/*Anomaly Injection*/
		if (count < 5) {
			x = 0.99;
			dt = 1;
		}
		count = count < 200 ? count+1 : 0;
    }

    //clock_gettime(CLOCK_MONOTONIC, &tic);
    short score;
    for (i = 0; i < TEST; i++) {
    	short x = x_ts[i];
    	short dt = dt_ts[i];
    	score = hls_top(x, dt);
    }

    //clock_gettime(CLOCK_MONOTONIC, &toc);
    //double total_time = ((double)(toc.tv_nsec-tic.tv_nsec))/((double)1000000000) + (double)(toc.tv_sec-tic.tv_sec);
    //printf("Elapsed time(s): %e. Time per prediction(s): %e., CLOCK RATE: %e\n", total_time, total_time/TEST, (double)TEST/total_time);
    return 0;
}

short hls_top(short x, short dt) {
#if defined (__SYNTHESIS__)
#pragma HLS inline region recursive
#pragma HLS pipeline II=10
#endif /*__SYNTHESIS__*/
    /*Number of Letters in the Alphabet*/
    /*Alphabet will range from values of 0 to 7.*/
    int n = _N;
    int i,j,k = 0;
    static short ret;

    /*F_REAL, F_IMAG and Power Array*/
    static short Fre = 0;
    static short Fim = 0;
    static short P = 0;

    /*Anomaly Detector Sliding Window Size*/
    short ano_w = _ANO_W;

    /*Reference Sliding Window Size*/
    short ref_w = _REF_W;

    /*Anomaly Alphabet Grid*/
    static short grid[_N][_N] = {0};

    /*Anomaly and Reference Sliding Windows Array*/
    static int ano_x[_ANO_W] = {0};
    static int ref_x[_REF_W] = {0};
    short ano_start = 0;
    short ano_end = ano_w-1;
    short ref_start = 0;
    short ref_end = ref_w-1;

    /*Perform RDFT*/
	//Weighting factor, area to converge to 1.
	short x_adj = MULT(x,  NORM_H);

	short shift_re = hw_cos(dt);
    short shift_im = hw_sin(dt);

    short Fre_prev = Fre;
    Fre = MULT(MULT(Fre, shift_re) - MULT(Fim, shift_im), WF) + x_adj;
    Fim = MULT(MULT(Fre_prev, shift_im) + MULT(Fim, shift_re), WF);

        /*Calculate the Power*/
    P = MULT(Fre, Fre) + MULT(Fim, Fim);

    /*Perform Anomaly Detection*/
    short ano_prev_start = ano_start;
    short ano_prev_next = ano_prev_start == ano_w-1 ? 0 : ano_prev_start+1;
    short ref_prev_start = ref_start;
    short ref_prev_next = ref_prev_start == ref_w-1 ? 0 : ref_prev_start+1;
    short ano_prev_end = ano_end;
    short ref_prev_end = ref_end;
    ano_end = ano_end == ano_w-1 ? 0 : ano_end+1;
    ref_end = ref_end == ref_w-1 ? 0 : ref_end+1;
    ano_start = ano_start == ano_w-1 ? 0 : ano_start+1;
    ref_start = ref_start == ref_w-1 ? 0 : ref_start+1;

    /*The values of x will only be between 0 and 0.99.*/
    /*Therefore to determine the letter its x*n.*/
    short letter = P>>11;
    short before1 = grid[ano_x[ano_prev_start]][ano_x[ano_prev_next]];
    short before2 = grid[ref_x[ref_prev_start]][ref_x[ref_prev_next]];
    short before3 = grid[ano_x[ano_prev_end]][ano_x[ano_end]];

        /*Remove Start Frequency*/
    grid[ano_x[ano_prev_start]][ano_x[ano_prev_next]] -= ano_w;
    grid[ref_x[ref_prev_start]][ref_x[ref_prev_next]] += ref_w;

        /*Write Letter into Windows*/
    ano_x[ano_end] = letter;
    ref_x[ref_end] = letter;

        /*Add New Frequency*/
    grid[ano_x[ano_prev_end]][ano_x[ano_end]] += ano_w;
    grid[ref_x[ref_prev_end]][ref_x[ref_end]] -= ref_w;

    short after1 = grid[ano_x[ano_prev_start]][ano_x[ano_prev_next]];
    short after2 = grid[ref_x[ref_prev_start]][ref_x[ref_prev_next]];
    short after3 = grid[ano_x[ano_prev_end]][ano_x[ano_end]];

    short change1 = MULT(before1, before1) - MULT(after1, after1);
    short change2 = MULT(before2, before2) - MULT(after2, after2);
    short change3 = MULT(before3, before3) - MULT(after3, after3);

    ret = ret + change1 + change2 + change3;

    return ret;
}
