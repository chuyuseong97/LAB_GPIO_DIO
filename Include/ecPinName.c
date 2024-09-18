/*----------------------------------------------------------------\
@ Embedded Controller by Yuseong Chu - Handong Global University
Author           : Yuseong Chu
Created          : 09-10-2024
Modified         : 09-10-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#include "ecPinNames.h"

void ecPinmap(PinName_t pinName, GPIO_TypeDef** GPIOx, unsigned int* pin)
{

	unsigned int pinNum = pinName & (0x000F);
	*pin = pinNum;

	unsigned int portNum = (pinName >> 4);


	if (portNum == 0)
		*GPIOx = GPIOA;
	else if (portNum == 1)
		*GPIOx = GPIOB;
	else if (portNum == 2)
		*GPIOx = GPIOC;
	else if (portNum == 3)
		*GPIOx = GPIOD;
	else if (portNum == 7)
		*GPIOx = GPIOH;
	else
		*GPIOx = GPIOA;
}
