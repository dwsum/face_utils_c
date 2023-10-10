//
// Created by Drew Sumsion on 8/15/22.
//

#include "Computer.h"

Computer::Computer() {

    //If 0 doesn't work, try 1
    cv::VideoCapture cap(0);

    //Use this for testing a single video that you can specify
    // std::string videoPath = "/home/tyler/TestEmb.mp4";
    // std::string videoPath = "/home/tyler/Motion2.mp4";
    // cv::VideoCapture cap(videoPath);
    
    if (!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
        return;
    }


    cam = cap;

    cam.set(cv::CAP_PROP_FRAME_WIDTH, COMPUTER_CAMERA_WIDTH);
    cam.set(cv::CAP_PROP_FRAME_HEIGHT, COMPUTER_CAMERA_HEIGHT);
}

bool Computer::IsOnline() {
    return true;
}

bool Computer::FeedAvailable() {
    return true;
}

cv::VideoCapture Computer::GetVideoFeed() {
    return cam;
}

float Computer::GetFaceScale() {
    return 0.3;//Arbitray value
}

cv::Mat Computer::read() {
    cam >> frame;
    return frame;
}

void Computer::release() {
    cam.release();
}

float Computer::get(cv::VideoCaptureProperties getItem) {
    return cam.get(getItem);
}