/*----------------------------------------------------------------\
@ Embedded Controller by Yuseong Chu - Handong Global University
Author           : Yuseong Chu
Created          : 09-20-2024
Modified         : 09-24-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO_7segment_problem 1
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecGPIO2_student.h"
#include "ecRCC2_student.h"

char segment[4] = {PA_7, PB_6, PC_7, PA_9};


// button pin define
#define BUTTON_PIN PC_13


void setup(void);


int main(void) { 
    // Initialiization --------------------------------------------------------
    setup();
    unsigned int cnt = 0;
    int last_btn_state = 1;

    // Infinite Loop ----------------------------------------------------------
    while(1) {
        sevensegment_display(cnt % 10);
        
        
        
        if (last_btn_state == 1 && GPIO_read(BUTTON_PIN) == 0) {
            cnt++; 
            if (cnt > 9) cnt = 0;
        }
        
        last_btn_state = GPIO_read(BUTTON_PIN);
    }
}


// Initialization 
void setup(void) {
    RCC_HSI_init();	
    GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
		GPIO_pupd(BUTTON_PIN, EC_PU);  // pull-up
	
    sevensegment_display_init(PA_7, PB_6, PC_7, PA_9);  // Decoder input A,B,C,D
		
		for (int i = 0; i<4; i++){
			
			GPIO_otype(segment[i], Output_push_pull); //push-pull
			GPIO_pupd(segment[i], EC_NO_PUPD);        //no pull up, pull down
			GPIO_ospeed(segment[i], EC_MEDIUM_SPEED); //Midium speed
		}
}




