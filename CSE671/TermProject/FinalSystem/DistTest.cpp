#include "../LIBS/UART/UART.h"
#include <unistd.h>
#include <string>
#include <iostream>
int main()
{
	UART tty01(1);
	tty01.opendev(9600, false);
	while (true)
	{
		std::string mesg;
		while ((mesg=tty01.readmsg(6))=="\0"){}
		std::cout<<mesg<<std::endl;
		if(mesg[0]=='R')
		{
			std::string dists=mesg.substr(1);
			int dist=atoi(dists.c_str());
			std::cout<<dist<<std::endl;
		}
	}
	return 0;
}
