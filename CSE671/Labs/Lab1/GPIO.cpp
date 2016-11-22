#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <string>
#include "GPIO.h"

GPIO::GPIO(){}

GPIO::GPIO(int pin)
{
	if (getuid()!=0)
	{
		std::cout<<"Please rerun as root!\n";
		exit(1);
	}
	_pin=pin;
  	std::fstream in;
	in.open("/sys/class/gpio/export",std::ios::out);
	if (!in.good())
  	{
    		std::cout << "can't open file /sys/class/gpio/export\n";
  	}
  	in<<pin;
  	in.close();
  	
}

GPIO::~GPIO()
{
	if (getuid()!=0)
	{
		std::cout<<"Please rerun as root!\n";
		exit(1);
	}
  	std::fstream in;
	in.open("/sys/class/gpio/unexport",std::ios::out);
	if (!in.good())
  	{
    		std::cout << "can't open file /sys/class/gpio/unexport\n";
  	}
  	in<<_pin;
  	in.close();
  	
}

void GPIO::Set(int value)
{
	char val[50];
	_value=value;
    	sprintf(val,"/sys/class/gpio/gpio%d/value",_pin);
  	std::fstream in(val,std::fstream::out);
  	if (!in.good())
  	{
    		std::cout << "can't open file " << val << "\n";
  	}
  	in<<value;
  	in.close();
}
int GPIO::Get()
{
	char val[50];
    sprintf(val,"/sys/class/gpio/gpio%d/value",_pin);
  	std::fstream in(val,std::fstream::in);
  	if (!in.good())
  	{
    	std::cout << "can't open file " << val << "\n";
    	return 1;
  	}
  	in>>_value;
  	in.close();
	return _value;
}
void GPIO::Mode(std::string mode)
{
	char direc[50];
    	sprintf(direc,"/sys/class/gpio/gpio%d/direction",_pin);
  	std::fstream in(direc,std::fstream::out);
  	if (!in.good())
  	{
    		std::cout << "can't open file " << direc<< "\n";
    		return;
  	}
	for (size_t i = 0; i < mode.length(); i++)
		mode[i] = tolower(mode[i]);
  	in<<mode;
  	in.close();
	return;
}
#ifdef TEST_GPIO
int main()
{
	GPIO LED(60);
	LED.Mode("OUT");
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
