/*----------------------------------------------------------------\
@ Embedded Controller by Yuseong Chu - Handong Global University
Author           : Yuseong Chu
Created          : 09-10-2024
Modified         : 09-10-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecRCC2_student.h"
#include "ecGPIO2_student.h"

void Delay_us(uint32_t us) {  
    if (us > 1) {
        uint32_t count = us * 16; 
        while (count--); 
    } else {
        uint32_t count = 16; 
        while (count--); 
    }
}

void setup(void) {
    RCC_HSI_init();
	
    // initialize the pushbutton pin as an input:
    GPIO_init(BUTTON_PIN, INPUT);  
    // initialize the LED pin as an output:
    GPIO_init(LED_PIN, OUTPUT);
    
    GPIO_pupd(BUTTON_PIN, EC_PU);  // Pull-Up for button
    GPIO_pupd(LED_PIN, EC_PU); // Pull-Up for LED
    GPIO_ospeed(LED_PIN, EC_MEDIUM_SPEED);
		GPIO_otype(LED_PIN, Output_open_drain);
}


int main(void) {
    setup();
	

		int last_BtnState = HIGH;
    int led_State = LOW;
	
		

    while (1) {
        int btn_State = GPIO_read(BUTTON_PIN);
			
				if (btn_State != last_BtnState) {
            Delay_us(200); 
            btn_State = GPIO_read(BUTTON_PIN); 
        }

        if (btn_State == LOW && last_BtnState == HIGH) {
            led_State = !led_State; 
            GPIO_write(LED_PIN, led_State);
        }
				
        last_BtnState = btn_State;	
    }
}
