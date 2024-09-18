/*----------------------------------------------------------------\
@ Embedded Controller by Yuseong Chu - Handong Global University
Author           : Yuseong Chu
Created          : 09-10-2024
Modified         : 09-10-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2_student.h"
#include "ecPinNames.h"

#define INPUT  0x00
#define OUTPUT 0x01
#define AF     0x02
#define ANALOG 0x03

#define Output_open_drain 0x01
#define Output_push_pull  0x00

// Pull-up/Pull-down Definitions
#define EC_NO_PUPD 0x00   // No pull-up/pull-down
#define EC_PU      0x01   // Pull-up
#define EC_PD      0x02   // Pull-down

// output speed Definitions
#define EC_LOW_SPEED    0x00
#define EC_MEDIUM_SPEED 0x01
#define EC_FAST_SPEED   0x02
#define EC_HIGH_SPEED   0x03

#define HIGH 1
#define LOW  0

#define LED_PIN PA_5  //Find LED Port&Pin and Fill the blank	
#define BUTTON_PIN PC_13 //Find BTN Port&Pin and Fill the blank

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
void GPIO_init(PinName_t pinName, uint32_t mode);     
void GPIO_write(PinName_t pinName, int Output);
int  GPIO_read(PinName_t pinName);
void GPIO_mode(PinName_t pinName, uint32_t mode);
void GPIO_ospeed(PinName_t pinName, int speed);
void GPIO_otype(PinName_t pinName, int type);
void GPIO_pupd(PinName_t pinName, int pupd);


 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
