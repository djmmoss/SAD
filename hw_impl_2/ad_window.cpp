#include "ad.hpp"

void ad_window(stream<axiInIndex> &inData, stream<axiIndex> &outData) {
	#pragma HLS pipeline II=1 enable_flush

	// Current Word
	axiInIndex	currWord = {0};

	// Score
	axiIndex currIndex	 = {0, 0, 0, 0, 0, 0};

	// Read Data
	inData.read(currWord);

	// DET SHIFT REGISTER
	static INDEXTYPE det_window[DET_W];
	#pragma HLS ARRAY_PARTITION variable=det_window complete dim=0

	for (int i = 0; i < DET_W-1; i++) {
		#pragma HLS unroll
		det_window[i] = det_window[i+1];
	}
	det_window[DET_W-1] = currWord.ind;


	// REF SHIFT REGISTER
	static INDEXTYPE ref_window[REF_W];
	#pragma HLS ARRAY_PARTITION variable=ref_window complete dim=0
	for (int i = 0; i < REF_W-1; i++) {
		#pragma HLS unroll
		ref_window[i] = ref_window[i+1];
	}
	ref_window[REF_W-1] = currWord.ind;


	currIndex.a = det_window[0];
	currIndex.b = det_window[1];

	currIndex.c = ref_window[0];
	currIndex.d = ref_window[1];

	currIndex.e = det_window[DET_W-2];
	currIndex.f = currWord.ind;

	outData.write(currIndex);

}
