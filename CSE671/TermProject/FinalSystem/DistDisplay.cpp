#include "../LIBS/UART/UART.h"
#include "../LIBS/SPI/SPI.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <bitset>
#include <cmath>
#include <sstream>
int convert(int valuei);
int main()
{
	UART tty01(1);
	SPIDevice _7Seg(1,0);
	_7Seg.setMode(_7Seg.MODE0);
	tty01.opendev(9600, false);
	while (true)
	{
		std::string mesg;
		while ((mesg=tty01.readmsg(6))=="\0"){}
		if(mesg[0]=='R')
		{
			std::string dists=mesg.substr(1,3);
			int dist=strtol(dists.c_str(), NULL, 10);
			double distd=dist*0.39;
			dist=dist*0.39;
			std::cout<<"double: "<<distd<<std::endl;
			if (dist<99)
			{
				int disti=floor(distd);
				int result = convert(disti);
				_7Seg.open();
				_7Seg.write(result);
				_7Seg.close();
			}
		}
	}
	return 0;
}
int convert(int valuei)
{
	std::string value=std::to_string(valuei);
	int first=0, second=0;
	if (value[0]=='0')
		first=0x00;
	else if (value[0]=='1')
		first=0x10;
	else if (value[0]=='2')
		first=0x20;
	else if (value[0]=='3')
		first=0x30;
	else if (value[0]=='4')
		first=0x40;
	else if (value[0]=='5')
		first=0x50;
	else if (value[0]=='6')
		first=0x60;
	else if (value[0]=='7')
		first=0x70;
	else if (value[0]=='8')
		first=0x80;
	else if (value[0]=='9')
		first=0x90;
	if (value[1]=='0')
		second=0x00;
	else if (value[1]=='1')
		second=0x01;
	else if (value[1]=='2')
		second=0x02;
	else if (value[1]=='3')
		second=0x03;
	else if (value[1]=='4')
		second=0x04;
	else if (value[1]=='5')
		second=0x05;
	else if (value[1]=='6')
		second=0x06;
	else if (value[1]=='7')
		second=0x07;
	else if (value[1]=='8')
		second=0x08;
	else if (value[1]=='9')
		second=0x09;
	int result = first+second;
	return result;
}
