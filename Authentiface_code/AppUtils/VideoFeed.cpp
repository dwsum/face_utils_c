//
// Created by Drew Sumsion on 8/13/22.
//

#include "VideoFeed.h"

VideoFeed::VideoFeed() {}

VideoFeed::VideoFeed(std::map<std::string, std::any> data) {
//    theCamera = cmraPntr//data[CAMERA];//std::any_cast<*Camera>(data[CAMERA]);
    theCamera = std::any_cast<Camera*>(data[CAMERA]);
}

//Mat is a multi-channel array used to store images
cv::Mat VideoFeed::GetFrame() {
    frame = theCamera->read();
    return frame;
}

void VideoFeed::CloseCamera() {
    theCamera->release();
}