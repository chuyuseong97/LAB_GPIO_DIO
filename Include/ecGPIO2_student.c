/*----------------------------------------------------------------\
@ Embedded Controller by Yuseong Chu - Handong Global University
Author           : Yuseong Chu
Created          : 09-10-2024
Modified         : 09-22-2024
Language/ver     : C++ in Keil uVision

Description      : Distributed to Students for LAB_GPIO
/----------------------------------------------------------------*/

#include "stm32f4xx.h"
#include "stm32f411xe.h"
#include "ecGPIO2_student.h"

#define NUM_VAL_decoder 4
#define NUM_VAL_MCU_decoder 7

int val_global[NUM_VAL_decoder];
int val_MCU_global[NUM_VAL_MCU_decoder];

char decoder_output[10][NUM_VAL_decoder] = {
	{0,0,0,0},
	{0,0,0,1},
	{0,0,1,0},
	{0,0,1,1},
	{0,1,0,0},
	{0,1,0,1},
	{0,1,1,0},
	{0,1,1,1},
	{1,0,0,0},
	{1,0,0,1}
};


char mcu_decoder_output[10][NUM_VAL_MCU_decoder] = {
	{1,0,0,0,0,0,0}, // 0
	{1,1,1,1,0,0,1}, // 1
	{0,1,0,0,1,0,0}, // 2
	{0,1,1,0,0,0,0}, // 3
	{0,0,1,1,0,0,1}, // 4
	{0,0,1,0,0,1,0}, // 5
	{0,0,0,0,0,1,0}, // 6
	{1,1,1,1,0,0,0}, // 7
	{0,0,0,0,0,0,0}, // 8
	{0,0,1,1,0,0,0}  // 9    
};

PinName_t Pin_G;
PinName_t Pin_F;
PinName_t Pin_E;
PinName_t Pin_D;
PinName_t Pin_C;
PinName_t Pin_B;
PinName_t Pin_A;


void GPIO_init(PinName_t pinName, uint32_t mode){     
	GPIO_TypeDef * Port;
	unsigned int pin;
	ecPinmap(pinName, &Port, &pin);
	
	// mode  : Input(0), Output(1), AlterFunc(2), Analog(3)   
	if (Port == GPIOA)
		RCC_GPIOA_enable();
	if (Port == GPIOB)
		RCC_GPIOB_enable();
	if (Port == GPIOC)
		RCC_GPIOC_enable();
	
	//[TO-DO] YOUR CODE GOES HERE
	// Make it for GPIOB, GPIOD..GPIOH

	// You can also make a more general function of
	// void RCC_GPIO_enable(GPIO_TypeDef *Port); 

	GPIO_mode(pinName, mode);
}


// GPIO Mode          : Input(00), Output(01), AlterFunc(10), Analog(11)
void GPIO_mode(PinName_t pinName, uint32_t mode){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName,&Port,&pin);
   Port->MODER &= ~(3UL<<(2*pin));     
   Port->MODER |= mode<<(2*pin);
}


// GPIO Speed          : Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
void GPIO_ospeed(PinName_t pinName, int speed){
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName, &Port, &pin);
   Port->OSPEEDR &= ~(3UL << (2 * pin));  
   Port->OSPEEDR |= (speed << (2 * pin)); 
	
}

// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
void GPIO_otype(PinName_t pinName, int type){
	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName, &Port, &pin);
   Port->OTYPER &= ~(1UL << pin);    
   Port->OTYPER |= (type << pin);    
	
}

// GPIO Push-Pull    : No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
void GPIO_pupd(PinName_t pinName, int pupd){
   	 GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName, &Port, &pin);
   Port->PUPDR &= ~(3UL << (2 * pin));  
   Port->PUPDR |= (pupd << (2 * pin));  
	
}

void GPIO_write(PinName_t pinName, int Output){
   GPIO_TypeDef * Port;
   unsigned int pin;
   ecPinmap(pinName, &Port, &pin);

   if (Output == HIGH)
       Port->ODR |= (1UL << pin);       
   else
       Port->ODR &= ~(1UL << pin ); 
}

int GPIO_read(PinName_t pinName){
   	GPIO_TypeDef * Port;
    unsigned int pin;
    ecPinmap(pinName, &Port, &pin);
    
    if(Port->IDR & (1UL << pin)){
			return 1;
		}
		else{
			return 0;
		}
			
}


void sevensegment_display_init(PinName_t pinNameD, PinName_t pinNameC, PinName_t pinNameB, PinName_t pinNameA) {
	
    Pin_A = pinNameA;
    Pin_B = pinNameB; 
    Pin_C = pinNameC;
    Pin_D = pinNameD;

    GPIO_init(Pin_A, OUTPUT);
    GPIO_init(Pin_B, OUTPUT);
    GPIO_init(Pin_C, OUTPUT);
    GPIO_init(Pin_D, OUTPUT);
}

void sevensegment_display(uint8_t num){

		GPIO_write(Pin_D, decoder_output[num][0]);
    GPIO_write(Pin_C, decoder_output[num][1]);
    GPIO_write(Pin_B, decoder_output[num][2]);
    GPIO_write(Pin_A, decoder_output[num][3]);

}



void sevensegment_decoder_init(void){
	
		Pin_A = PA_5;
    Pin_B = PA_6;
    Pin_C = PA_7;
    Pin_D = PB_6;
    Pin_E = PC_7;
    Pin_F = PA_9;
    Pin_G = PA_8;
		
		GPIO_init(Pin_A, OUTPUT);
    GPIO_init(Pin_B, OUTPUT);
    GPIO_init(Pin_C, OUTPUT);
    GPIO_init(Pin_D, OUTPUT);
    GPIO_init(Pin_E, OUTPUT);
    GPIO_init(Pin_F, OUTPUT);
    GPIO_init(Pin_G, OUTPUT);
		
}

void sevensegment_decoder(uint8_t num){

		GPIO_write(Pin_G, mcu_decoder_output[num][0]);
    GPIO_write(Pin_F, mcu_decoder_output[num][1]);
    GPIO_write(Pin_E, mcu_decoder_output[num][2]);
    GPIO_write(Pin_D, mcu_decoder_output[num][3]);
		GPIO_write(Pin_C, mcu_decoder_output[num][4]); 
    GPIO_write(Pin_B, mcu_decoder_output[num][5]); 
    GPIO_write(Pin_A, mcu_decoder_output[num][6]);
	
	
}

