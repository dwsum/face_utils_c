//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_TERMINALSETUP_H
#define AUTHENTIFACEDEMO_C_TERMINALSETUP_H

#include <map>
#include <any>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>

#include "../DoorUtils/CameraUtils/Computer.h"
#include "../DoorUtils/CameraUtils/Camera.h"
#include "../DoorUtils/Door.h"

#include "../Constants.h"

class TerminalSetup {
public:
    std::map<std::string, std::any> SetupHelp();

private:
    float GetLmkTh(std::string path);
    std::map<std::string, float> GetPasswordStrength();
};


#endif //AUTHENTIFACEDEMO_C_TERMINALSETUP_H
