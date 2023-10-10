#ifndef AUTHENTIFACEDEMO_C_USERINTERFACE_H
#define AUTHENTIFACEDEMO_C_USERINTERFACE_H

#include <iostream>



#include "ProcessImages.h"

class UserInterface {
public:
    UserInterface();
    void StartEnrollment();

private:
    ProcessImages processImages;
    void AddProcessImages();
    bool ContinueCapture();
    void UpdatePicture();
    void playSound();
    


};

#endif //AUTHENTIFACEDEMO_C_USERINTERFACE_H