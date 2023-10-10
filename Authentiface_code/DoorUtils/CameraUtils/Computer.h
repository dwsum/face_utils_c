//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_COMPUTER_H
#define AUTHENTIFACEDEMO_C_COMPUTER_H

#include "Camera.h"
#include <string>

class Computer:public Camera {
public:
    Computer();
    bool IsOnline();
    bool FeedAvailable();
    cv::VideoCapture GetVideoFeed();
    float GetFaceScale();
    cv::Mat read();
    void release();
    float get(cv::VideoCaptureProperties getItem);

private:
    cv::VideoCapture cam;
    
    cv::Mat frame;
};

#endif //AUTHENTIFACEDEMO_C_COMPUTER_H
