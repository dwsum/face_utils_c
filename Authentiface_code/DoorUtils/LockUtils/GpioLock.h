//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_GPIOLOCK_H
#define AUTHENTIFACEDEMO_C_GPIOLOCK_H

#include "DoorLock.h"


class GpioLock: public DoorLock {
public:
    GpioLock();
    bool IsOnline();
    void Unlock();
    void Lock();

};


#endif //AUTHENTIFACEDEMO_C_GPIOLOCK_H
