//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_TYPES_H
#define AUTHENTIFACEDEMO_C_TYPES_H

//include all the cameras here.
#include "CameraUtils/Computer.h"
#include "CameraUtils/Camera.h"

//include all the locks here.
#include "LockUtils/DoorLock.h"
#include "LockUtils/GpioLock.h"

#include "../Constants.h"

#include <map>
#include <iostream>
#include <iterator>


//enum CameraTypes {COMPUTER_CAMERA0};
class Types {
public:
    Types();
    Camera* GetCamera(std::string choice);
    DoorLock* GetLock(std::string choice);

private:
    std::map<std::string, Camera*> CameraTypes;
    std::map<std::string, DoorLock*> LockTypes;
};


#endif //AUTHENTIFACEDEMO_C_TYPES_H
