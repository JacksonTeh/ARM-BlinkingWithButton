#include <stdio.h>
#include "ButtonSM.h"
#include "Message.h"
#include "Button.h"

void buttonInitData(ButtonData *data)
{
    data->state = RELEASE;
}

void buttonSM(ButtonData *data)
{
    switch(data->state)
    {
        case RELEASE:
            if(isButtonPressed())       //check button
            {
                msg = CHANGE_MODE;      //pass the msg to LED
                data->state = PRESS;
            }
            break;
        case PRESS:
            if(!isButtonPressed())
                data->state = RELEASE;
            break;
        default :
            printf("Error: Unknown state encounter in buttonSM: %d\n", data->state);
            break;
    }
}