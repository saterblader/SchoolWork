#include "../LIBS/UART/UART.h"
#include "../LIBS/SPI/SPI.h"
#include <unistd.h>
#include <string>
#include <iostream>
#include <cmath>
#include <unistd.h>
int convert(int valuei);
int main()
{
	UART tty01(1),tty02(2);
	SPIDevice _7Seg(1,0);
	bool close= false;
	_7Seg.setMode(_7Seg.MODE0);
	tty01.opendev(9600, false);
	tty02.opendev(9600, false);
	while (true)
	{
		std::cout<<close<<std::endl;
		if (!close)
		{
			for (int i=0; i<20;i++)
			{
				tty02.writemsg("AB1\r");
				std::cout<<"Green\n";
				//usleep(200);
			}
		}
		std::string mesg;
		while ((mesg=tty01.readmsg(6))=="\0"){}
		if(mesg[0]=='R')
		{
			std::string dists=mesg.substr(1,3);
			int dist=strtol(dists.c_str(), NULL, 10);
			double distd=dist*0.39;
			dist=dist*0.39;
			if (dist<12)
			{
				_7Seg.open();
				_7Seg.write(0xff);
				_7Seg.close();
			}
			else if (dist<99)
			{

				int disti=floor(distd);
				int result = convert(disti);
				_7Seg.open();
				_7Seg.write(result);
				_7Seg.close();
				if (dist <36)
					for (int i=0; i<30;i++)
					{
						close=true;
						tty02.writemsg("AB0\r");
						std::cout<<"Red\n";
						//usleep(200);
					}
				if (dist>40)
					close=false;
			}
			else
			{
				_7Seg.open();
				_7Seg.write(0xff);
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
