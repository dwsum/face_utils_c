//
// Created by Drew Sumsion on 8/15/22.
//

#include "DoorLock.h"

DoorLock::DoorLock() {
    std::cout << MESSAGE_DOOR_LOCK;
}

bool DoorLock::IsOnline() {
    std::cout << MESSAGE_DOOR_LOCK;
    return false;
}

void DoorLock::Unlock() {
    std::cout << MESSAGE_DOOR_LOCK;
}

void DoorLock::Lock() {
    std::cout << MESSAGE_DOOR_LOCK;
}
