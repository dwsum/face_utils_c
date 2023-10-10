#ifndef AUTHENTIFACEDEMO_C_FACEMESHDETECT_H
#define AUTHENTIFACEDEMO_C_FACEMESHDETECT_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/file_helpers.h"
#include "mediapipe/framework/port/opencv_highgui_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/opencv_video_inc.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/modules/face_geometry/libs/geometry_pipeline.h"
#include "mediapipe/framework/formats/landmark.pb.h"

#include "../../../Constants.h"

class FaceMeshDetect {
public:
    // functions:
    FaceMeshDetect();
    std::vector<std::pair<float, float>> GenFaceMeshDetect(cv::Mat roi);

private:
    // class variables:
    // mediapipe::CalculatorGraph graph;
    std::unique_ptr<mediapipe::OutputStreamPoller> poller;
    // std::unique_ptr<mediapipe::CalculatorGraph> graph;

    //class functions:
    absl::Status RunMPPGraph();
};

#endif //AUTHENTIFACEDEMO_C_FACEMESHDETECT_H