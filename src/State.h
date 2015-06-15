#ifndef State_H
#define State_H

typedef enum {PRESS, RELEASE, LED_ON, LED_OFF, LED_BLINKING_ON, LED_BLINKING_OFF} State;
typedef enum {RUNNING, READY, SPAWNED, TERMINATED, BLOCKING, SLEEPING} TaskState;

#endif // State_H
