#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include "LEDS.h"

LEDS::LEDS(){}

LEDS::LEDS(int pin)
{
	if (getuid()!=0)
	{
		std::cout<<"Please rerun as root!\n";
		exit(1);
	}
	if(pin<0|| pin>4)
	{
		std::cout<<"value out of range!\n";
		exit(1);
	}
	_pin=pin;  	
}

LEDS::~LEDS(){}
void LEDS::Set(int value)
{
	char val[50];
    	sprintf(val,"/sys/class/leds/beaglebone:green:usr%d/brightness",_pin);
  	std::fstream in(val,std::fstream::out);
  	if (!in.good())
  	{
    		std::cout << "can't open file " << val << "\n";
  	}
  	in<<value;
  	in.close();
}
#ifdef TEST_LEDS
int main()
{
	LEDS LED(1);
	for(int i=0;i<10;i++)
	{
		LED.Set(1);
		usleep(250000);
		LED.Set(0);
		usleep(250000);
	}
	for(int i=0;i<20;i++)
	{
		LED.Set(1);
		usleep(50000);
		LED.Set(0);
		usleep(50000);
	}
	return 0;
}
#endif

