//
// Created by Drew Sumsion on 8/16/22.
//

#ifndef AUTHENTIFACEDEMO_C_PREPROCESSING_H
#define AUTHENTIFACEDEMO_C_PREPROCESSING_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <map>
#include <any>
#include <vector>
#include <chrono>
#include <ctime>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>


#include "../detection/FaceDetect.h"
#include "../../../DoorUtils/Door.h"

class Preprocessing {
public:
    Preprocessing();
    bool FindFace(cv::Mat roi, FaceDetect& myFaceDetect, Door& door);
    std::array<float, 4> DetectFaceHelper(cv::Mat roi, FaceDetect& myFaceDetect); //Does this need to be a public class?

private:
    
    FaceDetect myFaceDetect;
};


#endif //AUTHENTIFACEDEMO_C_PREPROCESSING_H
