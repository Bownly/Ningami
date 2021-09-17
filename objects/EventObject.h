#ifndef EVENTOBJECT_H
#define EVENTOBJECT_H
 
#include <gb/gb.h>
#include "../enums.h"

typedef struct EventObject {
    UINT8 x;
    UINT8 y;
    EVENTTYPE type;
    UINT8 value;
    
} EventObject;

#endif