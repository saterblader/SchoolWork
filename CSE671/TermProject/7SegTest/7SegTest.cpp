#include "../LIBS/SPI/SPI.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	long out = strtol(argv[1], NULL, 16);
	SPIDevice _7Seg(1,0);
	_7Seg.setMode(_7Seg.MODE0);
	_7Seg.open();
	_7Seg.write(out);
	_7Seg.close();
	return 0;
}
