//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_DOOR_H
#define AUTHENTIFACEDEMO_C_DOOR_H

#include <iostream>
#include "Types.h"
//#include "CameraUtils/Camera.h"

class Door {
public:
    //variables
    DoorLock* myLock;

    //functions
    Door();
    Door(std::string cameraType, std::string lockType);
    Camera* GetCamera();
    DoorLock* GetLock();

private:
    Camera* myCamera;
};

#endif //AUTHENTIFACEDEMO_C_DOOR_H
