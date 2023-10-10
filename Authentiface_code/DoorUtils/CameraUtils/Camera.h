//
// Created by Drew Sumsion on 8/15/22.
//

#ifndef AUTHENTIFACEDEMO_C_CAMERA_H
#define AUTHENTIFACEDEMO_C_CAMERA_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

// LibMP Header
#include "libmp.h"

// #include "mediapipe/framework/port/opencv_highgui_inc.h"
// #include "mediapipe/framework/port/opencv_imgproc_inc.h"
// #include "mediapipe/framework/port/opencv_video_inc.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "../../Constants.h"

class Camera {
public:
    Camera();
    virtual bool IsOnline();    //virtual is for polymorphism
    virtual bool FeedAvailable();
    virtual cv::VideoCapture GetVideoFeed();
    virtual float GetFaceScale();
    virtual cv::Mat read();
    virtual void release();
    virtual float get(cv::VideoCaptureProperties getItem);
//    void Test();
//    void GetFaceScale();
//    void GetFps();
//    void IndicateSound();
//    void GetWidthHeight();
//    void StartEnroll();
private:
    cv::VideoCapture cam;
    cv::Mat frame;
};

#endif //AUTHENTIFACEDEMO_C_CAMERA_H
