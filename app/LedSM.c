#include <stdio.h>
#include "LedSM.h"
#include "Message.h"
#include "Time.h"
#include "LED.h"

void ledInitData(LedData *data)
{
    data->state = LED_OFF;
    data->time = 0;
}

void ledSM(LedData *data)
{
    switch(data->state)
    {
        case LED_OFF:
            turnOffLED(PORTG, LED3);
            if(msg == CHANGE_MODE)
            {
                data->state = LED_BLINKING_ON;
                msg = DO_NOTHING;
            }
            break;
        case LED_ON:
            turnOnLED(PORTG, LED3);
            if(msg == CHANGE_MODE)
            {
                data->state = LED_OFF;
                msg = DO_NOTHING;
            }
            break;
        case LED_BLINKING_ON:
            turnOnLED(PORTG, LED3);
            if(msg == CHANGE_MODE)
            {
                data->state = LED_ON;
                msg = DO_NOTHING;
            }
            else
            {
                if(isTimerExpire(FIVE_HUND_MILISEC, &data->time))
                    data->state = LED_BLINKING_OFF;
            }
            break;
        case LED_BLINKING_OFF:
            turnOffLED(PORTG, LED3);
            if(msg == CHANGE_MODE)
            {
                data->state = LED_ON;
                msg = DO_NOTHING;
            }
            else
            {
                if(isTimerExpire(FIVE_HUND_MILISEC, &data->time))
                    data->state = LED_BLINKING_ON;
            }
            break;
        default :
			#ifdef TEST
            printf("Error: Unknown state encounter in LedSM: %d\n", data->state);
			#endif
            break;
    }
}
