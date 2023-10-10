//
// Created by Drew Sumsion on 8/15/22.
//

#include "GpioLock.h"

GpioLock::GpioLock() {
    std::cout << INIT_MESSAGE << GPIO_LOCK_NAME << std::endl;
}

bool GpioLock::IsOnline() {
    std::cout << GPIO_LOCK_NAME << ONLINE_MESSAGE << true << std::endl;
    return true;
}

void GpioLock::Unlock() {
    std::cout << LOCKING_MESSAGE << GPIO_LOCK_NAME << std::endl;
}

void GpioLock::Lock() {
    std::cout << UNLOCKING_MESSAGE << GPIO_LOCK_NAME << std::endl;
}