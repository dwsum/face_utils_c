//
// Created by Drew Sumsion on 8/15/22.
//

#include "Types.h"

Types::Types() {
    //Add all the Cameras here.
//    CameraTypes.insert(std::pair<std::string, Computer>(COMPUTER_CAMERA, Computer()));
    CameraTypes[COMPUTER_CAMERA] = new Computer();

    //Add all locks here.
//    LockTypes.insert(std::pair<std::string, DoorLock>(GPIO_LOCK, GpioLock()));
    LockTypes[GPIO_LOCK] = new GpioLock();
}

Camera* Types::GetCamera(std::string choice) {
    return CameraTypes[choice];
//    Camera* tmp = new Computer();
//    return tmp;
}

DoorLock* Types::GetLock(std::string choice) {
    return LockTypes[choice];
}
