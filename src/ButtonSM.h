#ifndef ButtonSM_H
#define ButtonSM_H

#include "State.h"

typedef struct
{
    State state;
} ButtonData;

void buttonInitData(ButtonData *data);
void buttonSM(ButtonData *data);

#endif // ButtonSM_H
