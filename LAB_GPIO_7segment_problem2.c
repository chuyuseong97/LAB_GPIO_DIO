/*----------------------------------------------------------------\
@ Embedded Controller by Yuseong Chu - Handong Global University
Author           : Yuseong Chu
Created          : 09-20-2024
Modified         : 09-24-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO_7segment_problem 2
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "ecGPIO2_student.h"
#include "ecRCC2_student.h"
#include <stdio.h>

// using stm32 Pin
char segment[9] = {PA_5, PA_6, PA_7, PB_6, PC_7, PA_9, PA_8, PB_10};

// button pin define
#define BUTTON_PIN PC_13


void setup(void);

int main(void){
	
	setup();
	unsigned int cnt = 0;
	int last_btn_state = 1; // last state for debouncing
	
	while(1){
		
		sevensegment_decoder(cnt%10);
		
		if(last_btn_state == 1 && GPIO_read(BUTTON_PIN) == LOW){
			cnt++;
			if (cnt>9) cnt = 0;
		}
		
		last_btn_state = GPIO_read(BUTTON_PIN);
	}
}

// initialization function setup
void setup(void){
	RCC_HSI_init();
	
	GPIO_init(BUTTON_PIN, INPUT);
	GPIO_pupd(BUTTON_PIN, EC_PU);
	
	sevensegment_decoder_init();
	
	for (int i = 0; i<10; i++){
		
		GPIO_otype(segment[i],Output_push_pull);
		GPIO_pupd(segment[i],EC_NO_PUPD);
		GPIO_ospeed(segment[i],EC_MEDIUM_SPEED);
	}
	

}
