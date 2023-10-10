#ifndef AUTHENTIFACEDEMO_C_FACEDETECT_H
#define AUTHENTIFACEDEMO_C_FACEDETECT_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <stdexcept>

#include <thread>
#include <mutex>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "libmp.h"
#include "mediapipe/framework/formats/landmark.pb.h" //do not need. Just putting to test imports.

// #include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_format.pb.h" //trying for previous import replacement.
// #include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/calculator.pb.h" //trying for previous import replacement.
#include "mediapipe/framework/calculator_options.pb.h" //trying for previous import replacement.
#include "mediapipe/framework/calculator_profile.pb.h" //trying for previous import replacement.

// #include "mediapipe/framework/formats/image_frame_opencv.h"
// #include "mediapipe/framework/port/file_helpers.h"
// #include "mediapipe/framework/port/opencv_highgui_inc.h"
// #include "mediapipe/framework/port/opencv_imgproc_inc.h"
// #include "mediapipe/framework/port/opencv_video_inc.h"
// #include "mediapipe/framework/port/parse_text_proto.h"
// #include "mediapipe/framework/port/status.h"
// #include "mediapipe/modules/face_geometry/libs/geometry_pipeline.h"

// #include "mediapipe/framework/packet.h"
// #include "mediapipe/framework/port/ret_check.h"
// #include "mediapipe/framework/formats/detection.pb.h"

#include "../../../Constants.h"

class FaceDetect {
public:
    // functions:
    FaceDetect();

    std::array<float, 4> GenFaceDetect(cv::Mat roi);
    float oldBoundingBoxHeight = 0.1;
    float newBoundingBoxHeight = 0.1;

    bool debounce;

private:
    // // class variables:
    // // mediapipe::CalculatorGraph graph;
    // std::unique_ptr<mediapipe::OutputStreamPoller> poller;
    // // std::unique_ptr<mediapipe::CalculatorGraph> graph;

    //The graph can't be a global variable because it needs to be initialized
    //with the correct input and output streams, which are different for each
    //instance of the class. Thus we have it as a unique pointer, which is
    //initialized locally in the constructor (Lmk()).
    std::unique_ptr<mediapipe::CalculatorGraph> graphPointerFaceDetect;

};

#endif //AUTHENTIFACEDEMO_C_FACEDETECT_H