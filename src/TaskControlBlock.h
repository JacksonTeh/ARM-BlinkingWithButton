#ifndef TaskControlBlock_H
#define TaskControlBlock_H

#include "State.h"

typedef struct
{
    TaskState state;
    uint32_t stack;
} Tcb;

#endif // TaskControlBlock_H
