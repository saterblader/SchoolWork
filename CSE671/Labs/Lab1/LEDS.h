#ifndef BB_LED_H
#define BB_LED_H

#include <string>
class LEDS
{
	public:
		LEDS();
		LEDS(int pin);
		void Set(int value);
		~LEDS();
	private:
		int _pin;
};
#endif
