#include "ad.hpp"
#include "ad_discretise.hpp"
#include "ad_window.hpp"
#include "ad_grid_update.hpp"
#include "ad_grid.hpp"
#include "ad_update.hpp"

void ad(stream<axiInOut> &inData, stream<axiInOut> &outData) {
    #pragma VHLS dataflow interval=1
	#pragma HLS pipeline II=1 enable_flush

	#pragma HLS INTERFACE port=return ap_ctrl_none
    #pragma HLS INTERFACE port=inData axis
    #pragma HLS INTERFACE port=outData axis

	static stream<axiInIndex> inIndex;
	static stream<axiIndex> indices;
	static stream<axiRawValues> rawValues;
	static stream<axiValues> values;

	#pragma HLS STREAM variable=inIndex depth=4
	#pragma HLS STREAM variable=indices depth=4
	#pragma HLS STREAM variable=rawValues depth=4
	#pragma HLS STREAM variable=values depth=4

	ad_discretise(inData, inIndex);
	ad_window(inIndex, indices);
	ad_grid_update(indices, rawValues);
	ad_grid(rawValues, values);
	ad_update(values, outData);
}
