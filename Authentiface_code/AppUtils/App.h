//
// Created by Drew Sumsion on 8/13/22.
//

#ifndef AUTHENTIFACEDEMO_C_APP_H
#define AUTHENTIFACEDEMO_C_APP_H

#include <iostream>
#include "VideoFeed.h"
#include "FrameAnalyze.h"
#include "TerminalSetup.h"
#include "ProcessImages.h"

#include "../DoorUtils/Door.h"


class App {
public:
    // functions:
    App();
    void Capture();

private:
    // class variables:
    VideoFeed theVid;
    FrameAnalyze theAnalysis;
    ProcessImages theProcessImgs;

    Door door;
    Camera* cameraPntr;
};

#endif //AUTHENTIFACEDEMO_C_APP_H
