#include "ecRCC2_student.h"
#include "ecGPIO2_student.h"

#define BUTTON_PIN PC_13

#define LED0_PIN PA_5
#define LED1_PIN PA_6
#define LED2_PIN PA_7
#define LED3_PIN PB_6

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
	GPIO_init(BUTTON_PIN, INPUT);
	GPIO_pupd(BUTTON_PIN, EC_PU);
	
	GPIO_otype(LED0_PIN,Output_push_pull);
	GPIO_otype(LED1_PIN,Output_push_pull);
	GPIO_otype(LED2_PIN,Output_push_pull);
	GPIO_otype(LED3_PIN,Output_push_pull);
	
	GPIO_pupd(LED0_PIN, EC_PU);
	GPIO_pupd(LED1_PIN, EC_PU);
	GPIO_pupd(LED2_PIN, EC_PU);
	GPIO_pupd(LED3_PIN, EC_PU);

	GPIO_init(LED0_PIN, OUTPUT);
	GPIO_init(LED1_PIN, OUTPUT);
	GPIO_init(LED2_PIN, OUTPUT);
	GPIO_init(LED3_PIN, OUTPUT);
}

int main(void) {
setup();


int currentLED = 0;
int lastButtonState = HIGH;

while (1) {
    int buttonState = GPIO_read(BUTTON_PIN);
	
		if (buttonState != lastButtonState){
			Delay_us(200);
			buttonState = GPIO_read(BUTTON_PIN);
		}
	
    if (buttonState == LOW && lastButtonState == HIGH) {
     
        GPIO_write(LED0_PIN, LOW);
        GPIO_write(LED1_PIN, LOW);
        GPIO_write(LED2_PIN, LOW);
        GPIO_write(LED3_PIN, LOW);
        
        switch (currentLED) {
            case 0:
                GPIO_write(LED0_PIN, HIGH);
                break;
            case 1:
                GPIO_write(LED1_PIN, HIGH);
                break;
            case 2:
                GPIO_write(LED2_PIN, HIGH);
                break;
            case 3:
                GPIO_write(LED3_PIN, HIGH);
                break;
        }

        
        currentLED = (currentLED + 1) % 4;
    }

    
    lastButtonState = buttonState;
}
}

