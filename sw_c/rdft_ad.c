#include "rdft_ad.h"


int main() {
    //struct timespec tic, toc;

    /*Number of Letters in the Alphabet*/
    /*Alphabet will range from values of 0 to 7.*/
    int i = 0;

    /*F_REAL, F_IMAG and Power Array*/
    int Fre = 0;
    int Fim = 0;
    int P = 0;
    int P_max = 2094247488;
    int P_min = 0;

    /*Anomaly Alphabet Grids*/
    int det_grid[SYM][SYM] = {0};
    int ref_grid[SYM][SYM] = {0};

    /*Anomaly and Reference Sliding Windows Array*/
    int det_window[DET_W] = {0};
    int ref_window[REF_W] = {0};

	int count = 15;
    MATHTYPE score = 0;
    //clock_gettime(CLOCK_MONOTONIC, &tic);

    for (i = 0; i < TEST; i++) {
		/*Generate an Interesting Signal*/
		int dt = i%5 == 0 ? 2 : i%3 == 0 ? 14 : 8;
        int x = i%5 == 0 ? 4 : i%3 == 0 ? 2 : 1;
		/*Anomaly Injection*/
		if (count < 35) {
        	x = 7;
			dt = 1;
		}
        if (count > 200) count = 0;
        count++;

        /*Perform RDFT*/
        //Weighting factor, area to converge to 1.
        int x_adj = x*NORM_H;

        int shift_re = cos(2*PI*dt);

        int shift_im = sin(2*PI*dt);


        int Fre_prev = Fre;
        Fre = (Fre*shift_re - Fim*shift_im)*WF + x_adj;
        Fim = (Fre_prev*shift_im + Fim*shift_re)*WF;

        /*Calculate the Power*/
        P = Fre*Fre + Fim*Fim;

        /* Scale P to [0, 8] */
        int letter = 7.0*((double) P - (double) P_min) / ((double) P_max - (double) P_min);
        // int letter = x;
        
        MATHTYPE det_0 = det_window[0];
        MATHTYPE ref_0 = ref_window[0];
        MATHTYPE curr_0 = det_window[DET_W-1];

        // DET SHIFT REGISTER
        for (int i = 0; i < DET_W-1; i++) {
            det_window[i] = det_window[i+1];
        }
        det_window[DET_W-1] = letter;

        // REF SHIFT REGISTER
        for (int i = 0; i < REF_W-1; i++) {
            ref_window[i] = ref_window[i+1];
        }
        ref_window[REF_W-1] = letter;

        MATHTYPE det_1 = det_window[0];
        MATHTYPE ref_1 = ref_window[0];
        MATHTYPE curr_1 = letter;

        // VALUES
        MATHTYPE det_det    = det_grid[det_0][det_1];
        MATHTYPE det_ref    = det_grid[ref_0][ref_1];
        MATHTYPE det_curr   = det_grid[curr_0][curr_1];
        MATHTYPE ref_det    = ref_grid[det_0][det_1];
        MATHTYPE ref_ref    = ref_grid[ref_0][ref_1];
        MATHTYPE ref_curr   = ref_grid[curr_0][curr_1];

        MATHTYPE    det_det_prev;
        MATHTYPE    det_ref_prev;
        MATHTYPE    det_curr_prev;
        MATHTYPE    ref_det_prev;
        MATHTYPE    ref_ref_prev;
        MATHTYPE    ref_curr_prev;
        MATHTYPE    det_det_curr;
        MATHTYPE    det_ref_curr;
        MATHTYPE    det_curr_curr;
        MATHTYPE    ref_det_curr;
        MATHTYPE    ref_ref_curr;
        MATHTYPE    ref_curr_curr;

        // DET PREV
        det_det_prev     = det_det;
        det_ref_prev     = det_ref;
        det_curr_prev    = det_curr;

        // REF PREV
        ref_det_prev     = ref_det;
        ref_ref_prev     = ref_ref;
        ref_curr_prev    = ref_curr;

        // DET CURR
        if ((det_0 == curr_0) && (det_1 == curr_1)) {
            det_det_curr     = det_det;
            det_curr_curr    = det_curr;
            det_ref_curr     = det_ref;
        } else {
            det_det_curr     = det_det - 2;
            det_curr_curr    = det_curr + 2;
            if ((det_0 == ref_0) && (det_1 == ref_1)) {
                if ((ref_0 == curr_0) && (ref_1 == curr_1)) {
                    det_ref_curr     = det_curr + 2;
                } else {
                    det_ref_curr     = det_ref - 2;
                }
            } else {
                if ((ref_0 == curr_0) && (ref_1 == curr_1)) {
                    det_ref_curr     = det_curr + 2;
                } else {
                    det_ref_curr     = det_ref;
                }
            }
        }

        // REF CURR
        if ((ref_0 == curr_0) && (ref_1 == curr_1)) {
            ref_det_curr     = ref_det;
            ref_ref_curr     = ref_ref;
            ref_curr_curr    = ref_curr;
        } else {
            ref_ref_curr     = ref_ref - 1;
            ref_curr_curr    = ref_curr + 1;
            if ((det_0 == ref_0) && (det_1 == ref_1)) {
                if ((det_0 == curr_0) && (det_1 == curr_1)) {
                    ref_det_curr     = ref_curr + 1;
                } else {
                    ref_det_curr     = ref_det - 1;
                }
            } else {
                if ((det_0 == curr_0) && (det_1 == curr_1)) {
                    ref_det_curr     = ref_curr + 1;
                } else {
                    ref_det_curr     = ref_det;
                }
            }
        }

        // UPDATE GRID
        MATHTYPE new_det_det = det_det - 2;
        MATHTYPE new_ref_ref = ref_ref - 1;
        MATHTYPE new_det_curr = det_curr + 2;
        MATHTYPE new_ref_curr = ref_curr + 1;

        if ((det_0 != curr_0) || (det_1 != curr_1)) {
            det_grid[det_0][det_1]      = new_det_det;
            det_grid[curr_0][curr_1]    = new_det_curr;
        }
        if ((ref_0 != curr_0) || (ref_1 != curr_1)) {
            ref_grid[ref_0][ref_1]      = new_ref_ref;
            ref_grid[curr_0][curr_1]    = new_ref_curr;
        }

        // Remove det_window[0], det_window[1]
        MATHTYPE det_rm = (det_det_prev - ref_det_prev);
        // Remove ref_window[0], ref_window[1]
        MATHTYPE ref_rm = (det_ref_prev - ref_ref_prev);
        // Remove currWord.data, det_window[DET_W-2]
        MATHTYPE curr_rm = (det_curr_prev - ref_curr_prev);
        // Add det_window[0], det_window[1]
        MATHTYPE det_add = (det_det_curr - ref_det_curr);
        // Add ref_window[0], ref_window[1]
        MATHTYPE ref_add = (det_ref_curr - ref_ref_curr);
        // Add currWord.data, det_window[DET_W-2]
        MATHTYPE curr_add = (det_curr_curr - ref_curr_curr);

        MATHTYPE det_rm2 = det_rm*det_rm;
        MATHTYPE ref_rm2 = ref_rm*ref_rm;
        MATHTYPE curr_rm2 = curr_rm*curr_rm;
        MATHTYPE det_add2 = det_add*det_add;
        MATHTYPE ref_add2 = ref_add*ref_add;
        MATHTYPE curr_add2 = curr_add*curr_add;
        MATHTYPE rm_total = det_rm2 + ref_rm2 + curr_rm2;
        MATHTYPE add_total = det_add2 + ref_add2 + curr_add2;
        MATHTYPE total = add_total - rm_total;

        score += total;

        printf("%d: %d\n", i, score);

    }

    //clock_gettime(CLOCK_MONOTONIC, &toc);
    //double total_time = ((double)(toc.tv_nsec-tic.tv_nsec))/((double)1000000000) + (double)(toc.tv_sec-tic.tv_sec);
    //printf("Elapsed time(s): %e. Time per prediction(s): %e., CLOCK RATE: %e\n", total_time, total_time/TEST, (double)TEST/total_time);
    return 0;
}
