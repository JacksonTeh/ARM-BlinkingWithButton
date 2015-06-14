#include <stdio.h>
#include "LedSM.h"
#include "Message.h"
#include "Time.h"
#include "LED.h"

void ledInitData(LedData *data)
{
    data->state = LED_OFF;
}

void ledSM(LedData *data)
{
    static uint32_t previousTime;
    
    switch(data->state)
    {
        case LED_OFF:
            turnOffLED();
            if(msg == CHANGE_MODE)
            {
                data->state = LED_BLINKING_ON;
                msg = DO_NOTHING;
            }
            break;
        case LED_ON:
            turnOnLED();
            if(msg == CHANGE_MODE)
            {
                data->state = LED_OFF;
                msg = DO_NOTHING;
            }
            break;
        case LED_BLINKING_ON:
            turnOnLED();
            if(msg == CHANGE_MODE)
            {
                data->state = LED_ON;
                msg = DO_NOTHING;
            }
            else
            {
                if(isTimerExpire(FIVE_HUND_MILISEC, previousTime))
                    data->state = LED_BLINKING_OFF;
            }
            break;
        case LED_BLINKING_OFF:
            turnOffLED();
            if(msg == CHANGE_MODE)
            {
                data->state = LED_ON;
                msg = DO_NOTHING;
            }
            else
            {
                if(isTimerExpire(FIVE_HUND_MILISEC, previousTime))
                    data->state = LED_BLINKING_ON;
            }
            break;
        default :
            printf("Error: Unknown state encounter in LedSM: %d\n", data->state);
            break;
    }
}