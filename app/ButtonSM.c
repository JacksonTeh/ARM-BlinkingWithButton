#include <stdio.h>
#include "ButtonSM.h"
#include "Message.h"
#include "Button.h"

/*
 *  Initialize data
 */
void buttonInitData(ButtonData *data)
{
    data->state = RELEASE;
}

void buttonSM(ButtonData *data)
{
    switch(data->state)
    {
        case RELEASE:
            if(readUserButton())       //check button
            {
                msg = CHANGE_MODE;      //pass the msg to LED
                data->state = PRESS;
            }
            break;
        case PRESS:
            if(!readUserButton())
                data->state = RELEASE;
            break;
        default :
			#ifdef TEST
            printf("Error: Unknown state encounter in buttonSM: %d\n", data->state);
			#endif
            break;
    }
}
