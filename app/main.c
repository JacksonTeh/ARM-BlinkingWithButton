//#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "Time.h"
#include "LED.h"
#include "Button.h"
#include "LedSM.h"
#include "ButtonSM.h"

int main(void)
{
	LedData ledData;
	ButtonData buttonData;

	initUserButton();
	CLK_EN();
	configureLED(LED3, PORTG);
	configureLED(LED4, PORTG);
	configureLED(LED5, PORTB);
	configureLED(LED6, PORTC);
	buttonInitData(&buttonData);
	ledInitData(&ledData);

    while(1)
    {
    	updateTime();
    	buttonSM(&buttonData);
    	ledSM(&ledData);
    }
}
