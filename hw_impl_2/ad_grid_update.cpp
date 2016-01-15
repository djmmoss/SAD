#include "ad.hpp"

void ad_grid_update(stream<axiIndex> &inData, stream<axiRawValues> &outData) {
	#pragma HLS pipeline II=1 enable_flush

	// Current Index
	axiIndex currIndex = {0, 0, 0, 0, 0, 0};

	// Output Values
	axiRawValues currValues = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	// Read Current Index
	inData.read(currIndex);

	// Grids
	static MATHTYPE det_grid[SYM][SYM];
	static MATHTYPE ref_grid[SYM][SYM];

	#pragma HLS ARRAY_PARTITION variable=det_grid complete dim=0
	#pragma HLS ARRAY_PARTITION variable=ref_grid complete dim=0

	// Set Index
	INDEXTYPE det_0 	= currIndex.a;
	INDEXTYPE det_1 	= currIndex.b;
	INDEXTYPE ref_0 	= currIndex.c;
	INDEXTYPE ref_1 	= currIndex.d;
	INDEXTYPE curr_0 	= currIndex.e;
	INDEXTYPE curr_1 	= currIndex.f;

	// VALUES
	MATHTYPE det_det 	= det_grid[det_0][det_1];
	MATHTYPE det_ref 	= det_grid[ref_0][ref_1];
	MATHTYPE det_curr 	= det_grid[curr_0][curr_1];
	MATHTYPE ref_det 	= ref_grid[det_0][det_1];
	MATHTYPE ref_ref 	= ref_grid[ref_0][ref_1];
	MATHTYPE ref_curr 	= ref_grid[curr_0][curr_1];

	// DET PREV
	currValues.det_det_prev 	= det_det;
	currValues.det_ref_prev 	= det_ref;
	currValues.det_curr_prev 	= det_curr;

	// REF PREV
	currValues.ref_det_prev 	= ref_det;
	currValues.ref_ref_prev 	= ref_ref;
	currValues.ref_curr_prev 	= ref_curr;

	// DET CURR
	if ((det_0 == curr_0) && (det_1 == curr_1)) {
		currValues.det_det_curr 	= det_det;
		currValues.det_curr_curr 	= det_curr;
		currValues.det_ref_curr 	= det_ref;
	} else {
		currValues.det_det_curr 	= det_det - 2;
		currValues.det_curr_curr 	= det_curr + 2;
		if ((det_0 == ref_0) && (det_1 == ref_1)) {
			if ((ref_0 == curr_0) && (ref_1 == curr_1)) {
				currValues.det_ref_curr 	= det_curr + 2;
			} else {
				currValues.det_ref_curr 	= det_ref - 2;
			}
		} else {
			if ((ref_0 == curr_0) && (ref_1 == curr_1)) {
				currValues.det_ref_curr 	= det_curr + 2;
			} else {
				currValues.det_ref_curr 	= det_ref;
			}
		}
	}

	// REF CURR
	if ((ref_0 == curr_0) && (ref_1 == curr_1)) {
		currValues.ref_det_curr 	= ref_det;
		currValues.ref_ref_curr 	= ref_ref;
		currValues.ref_curr_curr 	= ref_curr;
	} else {
		currValues.ref_ref_curr 	= ref_ref - 1;
		currValues.ref_curr_curr 	= ref_curr + 1;
		if ((det_0 == ref_0) && (det_1 == ref_1)) {
			if ((det_0 == curr_0) && (det_1 == curr_1)) {
				currValues.ref_det_curr 	= ref_curr + 1;
			} else {
				currValues.ref_det_curr 	= ref_det - 1;
			}
		} else {
			if ((det_0 == curr_0) && (det_1 == curr_1)) {
				currValues.ref_det_curr 	= ref_curr + 1;
			} else {
				currValues.ref_det_curr 	= ref_det;
			}
		}
	}

	outData.write(currValues);

	// UPDATE GRID
	MATHTYPE new_det_det;
	#pragma HLS RESOURCE variable=new_det_det core=AddSubnS
	new_det_det = det_det - 2;

	MATHTYPE new_ref_ref;
	#pragma HLS RESOURCE variable=new_ref_ref core=AddSubnS
	new_ref_ref = ref_ref - 1;

	MATHTYPE new_det_curr;
	#pragma HLS RESOURCE variable=new_det_curr core=AddSubnS
	new_det_curr = det_curr + 2;

	MATHTYPE new_ref_curr;
	#pragma HLS RESOURCE variable=new_ref_curr core=AddSubnS
	new_ref_curr = ref_curr + 1;

	if ((det_0 != curr_0) or (det_1 != curr_1)) {
		det_grid[det_0][det_1] 		= new_det_det;
		det_grid[curr_0][curr_1] 	= new_det_curr;
	}
	if ((ref_0 != curr_0) or (ref_1 != curr_1)) {
		ref_grid[ref_0][ref_1] 		= new_ref_ref;
		ref_grid[curr_0][curr_1] 	= new_ref_curr;
	}
}
