---
description: EC_HAL API
---


# Embedded Controller - STM32f411 HAL API

Documentation for HAL functions

Written by:   YuseongChu

Course:  Imbedded controller

Program: C/C++

IDE/Compiler: Keil uVision 5

OS: WIn10

MCU:  STM32F411RE (Nucleo-64)



---

[TOC]

  * [GPIO Digital In/Out](#gpio-digital-inout)
    + [Header File](#header-file)
    + [GPIO_init\(\)](#gpio_init)
    + [GPIO_mode\(\)](#gpio_mode)
    + [GPIO_write\(\)](#gpio_write)
    + [GPIO_read\(\)](#gpio_read)
    + [GPIO_ospeed\(\)](#gpio_ospeed)
    + [GPIO_otype\(\)](#gpio_otype)
    + [GPIO_pupd\(\)](#gpio_pupd)

---

## GPIO Digital InOut 

### Header File

 `#include "ecGPIO.h"`


```c++
#ifndef __ECGPIO2_H
#define __ECGPIO2_H

#include "stm32f411xe.h"
#include "ecRCC2_student.h"
#include "ecPinName.h"

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

void sevensegment_display_init(PinName_t pinNameA, PinName_t pinNameB, PinName_t pinNameC, PinName_t pinNameD); 
void sevensegment_display(uint8_t  num);

void sevensegment_decoder_init(void); 
void sevensegment_decoder(uint8_t  num);


 
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // __ECGPIO2_H
```




### GPIO_init\(\)

Initializes GPIO pins with default setting and Enables GPIO Clock. Mode: In/Out/AF/Analog

```c++
void GPIO_init(PinName_t pinName, uint32_t mode);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH

* **pin**:  pin number (int) 0~15

* **mode**:   INPUT(0), OUTPUT(1),  AF(02), ANALOG (03)

  

**Example code**

```c++
GPIO_init(GPIOA, 5, OUTPUT);
GPIO_init(GPIOC, 13, INPUT); 
```



### GPIO_mode\(\)

Configures  GPIO pin modes: In/Out/AF/Analog

```c++
void GPIO_mode(GPIO_TypeDef *Port, int pin, int mode);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH

* **pin**:  pin number (int) 0~15

* **mode**:   INPUT (0), OUTPUT (1),  AF(02), ANALOG (03)

  

**Example code**

```c++
GPIO_mode(GPIOA, 5, OUTPUT);
```



### GPIO_write\(\)

Write the data to GPIO pin: High, Low

```c++
void GPIO_write(GPIO_TypeDef *Port, int pin, int output);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **output**:   LOW(0), HIGH(1)



**Example code**

```c++
GPIO_write(GPIOA, 5, 1);  // 1: High
```



### GPIO_read\(\)

Read the data from GPIO pin

```c++
int  GPIO_read(GPIO_TypeDef *Port, int pin);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15



**Example code**

```c++
GPIO_read(GPIOC, 13);
```



### GPIO_ospeed\(\)

Configures  output speed of GPIO pin : Low, Mid, Fast, High

```c++
void GPIO_ospeed(GPIO_TypeDef* Port, int pin, int speed);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **speed**:   LOW_SPEED(0), MID_SPEED(1), FAST_SPEED(2) , HIGH_SPEED(3)



**Example code**

```c++
GPIO_ospeed(GPIOA, 5, 2);  // 2: FAST_SPEED
```



### GPIO_otype\(\)

Configures  output type of GPIO pin: Push-Pull / Open-Drain

```c++
void GPIO_otype(GPIO_TypeDef* Port, int pin, int type);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **type**:   PUSH_PULL(0), OPEN_DRAIN(1)



**Example code**

```c++
GPIO_otype(GPIOA, 5, 0);  // 0: Push-Pull
```



### GPIO_pupdr\(\)

Configures  Pull-up/Pull-down mode of GPIO pin: No Pull-up, Pull-down/ Pull-up/ Pull-down/ Reserved

```c++
void GPIO_pupd(GPIO_TypeDef* Port, int pin, int pupd);
```

**Parameters**

* **Port:**  Port Number,  GPIOA~GPIOH
* **pin**:  pin number (int) 0~15
* **pupd**:   NO_PUPD(0), PULL_UP(1), PULL_DOWN(2), RESERVED(3)



**Example code**

```c++
GPIO_pupd(GPIOA, 5, 0);  // 0: No Pull-up, Pull-down
```



### sevensegment_display_init()

Take 4 pins to use in the decoder as arguments and set them to output

```c
void sevensegment_display_init(PinName_t pinNameD, PinName_t pinNameC, PinName_t pinNameB, PinName_t pinNameA);
```

##### parameter

* pin: 4 select pin


------

##### Example code

```c
sevensegment_display_init(PA_7, PB_6, PC_7, PA_9);

```

### sevensegment_display()

Code that takes a number as an argument and stores that number bit by bit on four pins of the decoder.

```c
void sevensegment_display(uint8_t num);
```

##### parameter

* num: display number of segment

##### Example code

```c
void sevensegment_display(8) // display number 8 in 7segment
```



### sevensegment_decoder_init()

Code to take 7 pins and set them to OUTPUT to represent the number in the segment without using a decoder (no DP)

```c
void sevensegment_decoder_init(void);
```

##### parameter

* void

##### Example code

```c
sevensegment_decoder_init();
```



### sevensegment_decoder()

Code to take 7 bits and adjust the number of segments

```c
void sevensegment_decoder(uint8_t num)
```

##### parameter

* num: number of segment

##### Example code

```c
sevensegment_decoder(8);
```



```text

```
