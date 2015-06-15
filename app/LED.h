#ifndef LED_H
#define LED_H

#include "stm32f4xx_hal_gpio.h"
#include "State.h"

#if !defined(TEST)

#define LED3	GPIO_PIN_13
#define LED4	GPIO_PIN_14
#define LED5	GPIO_PIN_13
#define LED6	GPIO_PIN_5

#define PORTA	GPIOA
#define PORTB	GPIOB
#define PORTC	GPIOC
#define PORTG	GPIOG

#define turnOnLED(port, pin)	HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET)
#define turnOffLED(port, pin)	HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET)
#define toggleLED(port, pin)	HAL_GPIO_TogglePin(port, pin)
#define	readPinLED(port, pin)	HAL_GPIO_ReadPin(port, pin)

#define CLK_EN()	do{										    \
							__HAL_RCC_GPIOA_CLK_ENABLE();	\
							__HAL_RCC_GPIOB_CLK_ENABLE();	\
							__HAL_RCC_GPIOC_CLK_ENABLE();	\
							__HAL_RCC_GPIOG_CLK_ENABLE();	\
					}while(0)

#define configureLED(pin, port)	do{											\
									GPIO_InitTypeDef GpioInfo;				    \
                                                        \
									GpioInfo.Mode = GPIO_MODE_OUTPUT_PP;	\
									GpioInfo.Pin = pin;						        \
									GpioInfo.Pull = GPIO_NOPULL;			    \
									GpioInfo.Speed = GPIO_SPEED_HIGH;		  \
                                                        \
									HAL_GPIO_Init(port, &GpioInfo);	      \
								}while(0)

#else

#define LED3	3
#define PORTG	13

void turnOnLED(int port, int pin);
void turnOffLED(int port, int pin);

#endif

#endif // LED_H
