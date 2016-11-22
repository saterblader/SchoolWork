#include "../LIBS/UART/UART.h"
#include <unistd.h>
int main()
{
	UART tty02(2);
	bool flip=0;
	tty02.opendev(9600, false);
	while (true)
	{
		for(int i=0;i<20;i++)
		{
			if(flip)
				tty02.writemsg("AB1\r");
			else if(!flip)
				tty02.writemsg("AB0\r");
			usleep(5000);
		}
		flip=!flip;
	}
	return 0;
}
