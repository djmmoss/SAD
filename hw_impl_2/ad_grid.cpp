#include "ad.hpp"

void ad_grid(stream<axiRawValues> &inData, stream<axiValues> &outData){
	#pragma HLS pipeline II=1 enable_flush

	// Current Raw Values
	axiRawValues currRawValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Current Values
	axiValues currValues = {0, 0, 0, 0, 0, 0};

	// Read In Values
	inData.read(currRawValues);

	MATHTYPE det_det_prev 	= currRawValues.det_det_prev;
	MATHTYPE det_ref_prev 	= currRawValues.det_ref_prev;
	MATHTYPE det_curr_prev 	= currRawValues.det_curr_prev;

	MATHTYPE ref_det_prev	= currRawValues.ref_det_prev;
	MATHTYPE ref_ref_prev	= currRawValues.ref_ref_prev;
	MATHTYPE ref_curr_prev	= currRawValues.ref_curr_prev;

	MATHTYPE det_det_curr	= currRawValues.det_det_curr;
	MATHTYPE det_ref_curr	= currRawValues.det_ref_curr;
	MATHTYPE det_curr_curr	= currRawValues.det_curr_curr;

	MATHTYPE ref_det_curr	= currRawValues.ref_det_curr;
	MATHTYPE ref_ref_curr	= currRawValues.ref_ref_curr;
	MATHTYPE ref_curr_curr	= currRawValues.ref_curr_curr;

	// Remove det_window[0], det_window[1]
	MATHTYPE det_rm;
	#pragma HLS RESOURCE variable=det_rm core=AddSubnS
	det_rm = (det_det_prev - ref_det_prev);

	// Remove ref_window[0], ref_window[1]
	MATHTYPE ref_rm;
	#pragma HLS RESOURCE variable=ref_rm core=AddSubnS
	ref_rm = (det_ref_prev - ref_ref_prev);

	// Remove currWord.data, det_window[DET_W-2]
	MATHTYPE curr_rm;
	#pragma HLS RESOURCE variable=curr_rm core=AddSubnS
	curr_rm = (det_curr_prev - ref_curr_prev);

	// Add det_window[0], det_window[1]
	MATHTYPE det_add;
	#pragma HLS RESOURCE variable=det_add core=AddSubnS
	det_add = (det_det_curr - ref_det_curr);

	// Add ref_window[0], ref_window[1]
	MATHTYPE ref_add;
	#pragma HLS RESOURCE variable=ref_add core=AddSubnS
	ref_add = (det_ref_curr - ref_ref_curr);

	// Add currWord.data, det_window[DET_W-2]
	MATHTYPE curr_add;
	#pragma HLS RESOURCE variable=curr_add core=AddSubnS
	curr_add = (det_curr_curr - ref_curr_curr);

	currValues.det_rm 	= det_rm;
	currValues.ref_rm 	= ref_rm;
	currValues.curr_rm 	= curr_rm;
	currValues.det_add 	= det_add;
	currValues.ref_add 	= ref_add;
	currValues.curr_add = curr_add;

	outData.write(currValues);

}






