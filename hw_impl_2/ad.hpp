#ifndef AD_H_
#define AD_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

#include <ap_int.h>
#include <hls_stream.h>


#define DET_W 1000 + 2
#define REF_W 2000 + 2
#define SYM 4
#define MASK 2
#define MATHTYPE ap_uint<16>
#define INDEXTYPE ap_uint<6>

using namespace hls;

struct axiInOut {
	MATHTYPE	data;
};

struct axiInIndex {
	INDEXTYPE	ind;
};

struct axiIndex {
	INDEXTYPE	a;
	INDEXTYPE	b;
	INDEXTYPE	c;
	INDEXTYPE	d;
	INDEXTYPE	e;
	INDEXTYPE	f;
};

struct axiRawValues {
	MATHTYPE	det_det_prev;
	MATHTYPE	det_ref_prev;
	MATHTYPE	det_curr_prev;
	MATHTYPE	ref_det_prev;
	MATHTYPE	ref_ref_prev;
	MATHTYPE	ref_curr_prev;
	MATHTYPE	det_det_curr;
	MATHTYPE	det_ref_curr;
	MATHTYPE	det_curr_curr;
	MATHTYPE	ref_det_curr;
	MATHTYPE	ref_ref_curr;
	MATHTYPE	ref_curr_curr;
};

struct axiValues {
	MATHTYPE	det_rm;
	MATHTYPE	ref_rm;
	MATHTYPE	curr_rm;
	MATHTYPE	det_add;
	MATHTYPE	ref_add;
	MATHTYPE	curr_add;
};



void ad(stream<axiInOut> &inData, stream<axiInOut> &outData);

#endif
