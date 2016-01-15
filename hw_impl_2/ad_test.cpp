#include "ad.hpp"

using namespace hls;
using namespace std;

int main(int argc, char *argv[]) {

	axiInOut inData = {0};
	axiInOut outData = {0};
	stream<axiInOut>	inDataFIFO("inDataFIFO");
	stream<axiInOut> outDataFIFO("outDataFIFO");

	static int count = 105;
	int i = 0;
	int j = -2;

	cout << "Making Input" << endl;
	for (i = 0; i < count; i++) {
		//inData.data = i%5 == 0 ? 4 : i%3 == 0 ? 5 : 9;
		inData.data = 1;
		inDataFIFO.write(inData);
	}
	for (i = 0; i < count; i++) {
		//inData.data = i%5 == 0 ? 7 : i%3 == 0 ? 3 : 6;
		inData.data = 2;
		inDataFIFO.write(inData);
	}

	cout << "Running AD" << endl;
	for (i = 0; i < count*2; i++) {
		ad(inDataFIFO, outDataFIFO);
	}

	cout << "Checking Output" << endl;
	while (!outDataFIFO.empty()) {
		outDataFIFO.read(outData);
		if (outData.data == j*j) {
			cout << outData.data <<  " ." << endl;
		} else {
			cout << outData.data << " X" << endl;
		}
		j++;
	}
	cout << endl << "Finished" << endl;
}
