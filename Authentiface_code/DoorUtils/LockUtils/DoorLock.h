//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_DOORLOCK_H
#define AUTHENTIFACEDEMO_C_DOORLOCK_H

#include <iostream>
#include "../../Constants.h"

class DoorLock {
public:
    DoorLock();
    virtual bool IsOnline();    //virtual is for polymorphism
    virtual void Unlock();
    virtual void Lock();
};


#endif //AUTHENTIFACEDEMO_C_DOORLOCK_H
