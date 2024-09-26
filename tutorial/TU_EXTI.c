/**
******************************************************************************
* @author  SSSLAB
* @Mod	   2024-09-26 by YuseongChu
* @brief   Embedded Controller:  Tutorial EXTI
*
*
******************************************************************************
*/

void LED_toggle(void);

//#include "ecSTM32F4v2.h"
#include "ecRCC2_student.h"
#include "ecGPIO2_student.h"

#define LED_PIN   PA_5
#define BUTTON_PIN PC_13

void setup(void);

int main(void) {

	// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();


	// EXTI Initialiization ------------------------------------------------------	

	RCC->AHB1ENR |= (1<<2);
	// SYSCFG peripheral clock enable
	RCC->APB2ENR |= (1<<4);

	// Connect External Line to the GPIO
	// Button: PC_13 -> EXTICR3(EXTI13)
	SYSCFG->EXTICR[3] &= ~(15<<4);
	SYSCFG->EXTICR[3] |= (2<<4);

	// Falling trigger enable (Button: pull-up)
	EXTI->FTSR |= (1UL << 13);

	// Unmask (Enable) EXT interrupt
	EXTI->IMR |= (1UL << 13);

	// Interrupt IRQn, Priority
	NVIC_SetPriority(EXTI15_10_IRQn, 0);  		// Set EXTI priority as 0	
	NVIC_EnableIRQ(EXTI15_10_IRQn); 			// Enable EXTI 


	while (1);
	
}


void EXTI15_10_IRQHandler(void) {
	if ((EXTI->PR & EXTI_PR_PR13) == EXTI_PR_PR13) {
		LED_toggle();
		EXTI->PR |= EXTI_PR_PR13; // cleared by writing '1'
	}
}

void LED_toggle(void){
	
	static int led_state = 0;
	
	led_state =! led_state;
	
	if (led_state){
		GPIO_write(LED_PIN,HIGH);
	}
	else{
		GPIO_write(LED_PIN,LOW);
	}
}


// Initialiization 
void setup(void)
{
	RCC_PLL_init();                         // System Clock = 84MHz
	// Initialize GPIOA_5 for Output
	GPIO_init(LED_PIN, OUTPUT);    // calls RCC_GPIOA_enable()	
	// Initialize GPIOC_13 for Input Button
	GPIO_init(BUTTON_PIN, INPUT);  // calls RCC_GPIOC_enable()
}
