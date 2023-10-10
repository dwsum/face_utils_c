//
// Created by Drew Sumsion on 8/22/22.
//

#ifndef AUTHENTIFACEDEMO_C_LMK_H
#define AUTHENTIFACEDEMO_C_LMK_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>

#include <thread>
#include <mutex>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
// #include "mediapipe/framework/calculator_framework.h"
// #include "mediapipe/framework/formats/image_frame.h"
// #include "mediapipe/framework/formats/image_frame_opencv.h"
// #include "mediapipe/framework/port/file_helpers.h"
// #include "mediapipe/framework/port/opencv_highgui_inc.h"
// #include "mediapipe/framework/port/opencv_imgproc_inc.h"
// #include "mediapipe/framework/port/opencv_video_inc.h"
// #include "mediapipe/framework/port/parse_text_proto.h"
// #include "mediapipe/framework/port/status.h"
// #include "mediapipe/modules/face_geometry/libs/geometry_pipeline.h"
#include "mediapipe/framework/formats/landmark.pb.h"

#include "../../../Constants.h"

class Lmk {

public:
    // functions:
    Lmk();
    std::vector<std::pair<float, float>> GenLmk(cv::Mat roi);
    std::vector<std::vector<std::pair<float, float>>> PackLmk(std::vector<std::vector<std::pair<float, float>>> meshSequence);
    // bool GenLmk(cv::Mat roi);

private:

    std::vector<std::pair<float, float>> _proc_lmk(std::vector<std::pair<float, float>> lmk);

    // class variables:
    // mediapipe::CalculatorGraph graph;
    std::unique_ptr<mediapipe::OutputStreamPoller> poller;
    
    //The graph can't be a global variable because it needs to be initialized
    //with the correct input and output streams, which are different for each
    //instance of the class. Thus we have it as a unique pointer, which is
    //initialized locally in the constructor (Lmk()).
    std::unique_ptr<mediapipe::CalculatorGraph> graphPointer;

    //class functions:
    absl::Status RunMPPGraph();
    int noseBridgeIndex = 6;
    int noseTipIndex = 4;
};

#endif //AUTHENTIFACEDEMO_C_LMK_H