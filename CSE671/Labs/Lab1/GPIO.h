#ifndef BB_GPIO_H
#define BB_GPIO_H

#include <string>
class GPIO
{
	public:
		GPIO();
		GPIO(int pin);
		void Set(int value);
		int Get();
		void Mode(std::string mode);
		~GPIO();
	private:
		int _pin;
		int _mode;
		int _value;
};
#endif
