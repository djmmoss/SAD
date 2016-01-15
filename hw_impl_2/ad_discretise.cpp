#include "ad.hpp"

void ad_discretise(stream<axiInOut> &inData, stream<axiInIndex> &outData) {
	#pragma HLS pipeline II=1 enable_flush

	// Current Data Sample
	axiInOut currData = {0};

	// New Index
	axiInIndex currIndex = {0};

	inData.read(currData);

	// Implement Custom Discretisation
	currIndex.ind = currData.data & ((1 << MASK) - 1);

	outData.write(currIndex);

}
