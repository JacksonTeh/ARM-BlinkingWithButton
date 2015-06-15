#ifndef Button_H
#define Button_H

#include "stm32f4xx_hal_gpio.h"

#if !defined(TEST)
  #define	readUserButton()	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)
#else
  uint32_t readUserButton();
#endif

void initUserButton();

#endif // Button_H
