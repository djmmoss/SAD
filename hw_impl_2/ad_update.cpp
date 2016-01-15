#include "ad.hpp"

void ad_update(stream<axiValues> &inData, stream<axiInOut> &outData){
	#pragma HLS pipeline II=1 enable_flush

	// Score
	static MATHTYPE score;

	// Score Out
	axiInOut scoreOut = {0};

	// Current Values
	axiValues currValues = {0, 0, 0, 0, 0, 0};

	// Read In Values
	inData.read(currValues);

	MATHTYPE det_rm 	= currValues.det_rm;
	MATHTYPE ref_rm 	= currValues.ref_rm;
	MATHTYPE curr_rm 	= currValues.curr_rm;
	MATHTYPE det_add 	= currValues.det_add;
	MATHTYPE ref_add 	= currValues.ref_add;
	MATHTYPE curr_add 	= currValues.curr_add;

	MATHTYPE det_rm2;
	#pragma HLS RESOURCE variable=det_rm2 core=MulnS
	det_rm2 = det_rm*det_rm;

	MATHTYPE ref_rm2;
	#pragma HLS RESOURCE variable=ref_rm2 core=MulnS
	ref_rm2 = ref_rm*ref_rm;

	MATHTYPE curr_rm2;
	#pragma HLS RESOURCE variable=curr_rm2 core=MulnS
	curr_rm2 = curr_rm*curr_rm;

	MATHTYPE det_add2;
	#pragma HLS RESOURCE variable=det_add2 core=MulnS
	det_add2 = det_add*det_add;

	MATHTYPE ref_add2;
	#pragma HLS RESOURCE variable=ref_add2 core=MulnS
	ref_add2 = ref_add*ref_add;

	MATHTYPE curr_add2;
	#pragma HLS RESOURCE variable=curr_add2 core=MulnS
	curr_add2 = curr_add*curr_add;

	MATHTYPE rm_total;
	#pragma HLS RESOURCE variable=rm_total core=AddSubnS
	rm_total = det_rm2 + ref_rm2 + curr_rm2;

	MATHTYPE add_total;
	#pragma HLS RESOURCE variable=add_total core=AddSubnS
	add_total = det_add2 + ref_add2 + curr_add2;

	MATHTYPE total;
	#pragma HLS RESOURCE variable=total core=AddSubnS
	total = add_total - rm_total;

	#pragma HLS RESOURCE variable=score core=AddSubnS
	score += total;

	scoreOut.data = score;

	outData.write(scoreOut);
}
