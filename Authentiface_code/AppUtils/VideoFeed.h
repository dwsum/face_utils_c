//
// Created by Drew Sumsion on 8/13/22.
//

#ifndef AUTHENTIFACEDEMO_C_VIDEOFEED_H
#define AUTHENTIFACEDEMO_C_VIDEOFEED_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <map>
#include <any>
#include "../Constants.h"
#include "../DoorUtils/CameraUtils/Camera.h"


class VideoFeed{
public:
    //functions
    VideoFeed();
    VideoFeed(std::map<std::string, std::any> data);
    cv::Mat GetFrame();
    void CloseCamera();

private:
    //variables
    Camera *theCamera;
    cv::Mat frame;
};

#endif //AUTHENTIFACEDEMO_C_VIDEOFEED_H