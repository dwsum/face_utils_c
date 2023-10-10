//
// Created by Drew Sumsion on 8/15/22.
//

#include "Door.h"
#include <iostream>

Door::Door() {}

Door::Door(std::string cameraType, std::string lockType) {
    Types theTypes;
    std::cout << "Connecting to Lock.\n";
    myCamera = theTypes.GetCamera(cameraType);
    myLock = theTypes.GetLock(lockType);
}

Camera* Door::GetCamera() {
    return myCamera;
}

DoorLock* Door::GetLock() {
    return myLock;
}