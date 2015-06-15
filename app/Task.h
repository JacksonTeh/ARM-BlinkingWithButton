#ifndef Task_H
#define Task_H

#include <stdint.h>
#include "State.h"

typedef struct
{
    TaskState state;
    uint32_t stack;
} Tcb;

#endif // Task_H
