//
// Created by Drew Sumsion on 8/15/22.
//

#include "Camera.h"

Camera::Camera() {
    frame = cv::Mat::zeros(DEFAULT_WIDTH,DEFAULT_HEIGHT,CV_8UC1);
}

bool Camera::IsOnline() {
    return true;
}

bool Camera::FeedAvailable() {
    return true;
}

cv::VideoCapture Camera::GetVideoFeed() {
    return cam;
}

float Camera::GetFaceScale() {
    return 0.3;//TODO change from hardcoding.
}

cv::Mat Camera::read() {
    return frame;
}

void Camera::release() {}

float Camera::get(cv::VideoCaptureProperties getItem) {
    return cam.get(getItem);
}