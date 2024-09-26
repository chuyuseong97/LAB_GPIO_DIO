#include "stm32f411xe.h"
#include "ecRCC2_student.h"
#include "ecGPIO2_student.h"

#define MCU_CLK_PLL 84000000
#define MCU_CLK_HSI 16000000
#define LED_PIN PA_5
#define BUTTON_PIN PC_13

volatile uint32_t msTicks = 0;
volatile uint32_t curTicks;

void setup(void);
void LED_toggle(void);

int main(void) {
	
// System CLOCK, GPIO Initialiization ----------------------------------------
	setup();

// SysTick Initialiization ------------------------------------------------------				
	//  SysTick Control and Status Register
	SysTick->CTRL &= ~1;		// Disable SysTick IRQ and SysTick Counter

	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |= (1<<2);

	// uint32_t MCU_CLK=EC_SYSTEM_CLK
	// SysTick Reload Value Register
	SysTick->LOAD = 83999; 				// 1ms

	// Clear SysTick Current Value 
	SysTick->VAL = 0;

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	SysTick->CTRL |= (1<<1);
		
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= 1;
		
	NVIC_SetPriority(SysTick_IRQn, 16);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);			    // Enable interrupt in NVIC

		
// While loop ------------------------------------------------------				
	msTicks = 0;

	while(1){
		curTicks = msTicks;
		while ((msTicks - curTicks) < 1000);	
		msTicks = 0;
		LED_toggle();
	}
}

int led_state = 0;

void LED_toggle(void){
	
	
	led_state =! led_state;
	
	if (led_state){
		GPIO_write(LED_PIN,HIGH);
	}
	else{
		GPIO_write(LED_PIN,LOW);
	}
}


void SysTick_Handler(void){
	msTicks++;
}

void setup(void)
{
	RCC_PLL_init();              // System Clock = 84MHz	
	GPIO_init(BUTTON_PIN, INPUT);
	GPIO_init(PA_5, OUTPUT);     // calls RCC_GPIOA_enable()	
}
