#ifndef AUTHENTIFACEDEMO_C_CORE_H
#define AUTHENTIFACEDEMO_C_CORE_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp> // Include the OpenCV library
#include <cmath> // Include cmath for the round function
#include <map>
#include <any>
#include <vector>
#include <chrono>
#include <ctime>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class Core {
public:
    cv::Mat GetCroppedFaceImage(cv::Mat roi, std::array<float, 4> detected, float expansion, float targetSize, bool largest);
    cv::Mat ResizeToCeiling(cv::Mat img, float targetSize);
    cv::Mat ResizeFaceRegion(cv::Mat img, float targetSize);
    cv::Mat CropFaceRegion(cv::Mat img, std::array<float, 4> detected, float expansion);
    cv::Mat CropFace(cv::Mat img, std::array<float, 4> detected, float expansion, float targetSize, bool largest);

private:

};

#endif //AUTHENTIFACEDEMO_C_CORE_H