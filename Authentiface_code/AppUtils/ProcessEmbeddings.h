#ifndef AUTHENTIFACEDEMO_C_PROCESSEMBEDDINGS_H
#define AUTHENTIFACEDEMO_C_PROCESSEMBEDDINGS_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <map>
#include <any>
#include <vector>
#include <tuple>
#include <string>

#include <torch/script.h>
#include <torch/torch.h>

#include "../DoorUtils/Door.h"
#include "../face_utils/facetools/motion/LmkModel.h"

class ProcessEmbeddings {
public:
    ProcessEmbeddings();
    ProcessEmbeddings(std::map<std::string, std::any> theData);
    void ProcessEmb(std::vector<std::vector<std::pair<float, float>>> original_LMK_seq, std::vector<cv::Mat> img_seq);
    void AddEnrollment(std::vector<std::vector<std::pair<float, float>>> original_LMK_seq, std::vector<cv::Mat> img_seq);
    void StartEnrollment();

private:
    //variables
    bool enroll;
    float idTH;
    float lmkTH;

    float lmkEMB;
    float idEMB;

    std::vector<std::pair<float, float>> lmkEMBs;
    std::vector<std::pair<float, float>> idEMBs;

    std::vector<std::vector<cv::Mat>> enrollImages;

    //original_LMK_seq stores the lmk sequences for each of the frames
    //in the video.
    std::vector<std::vector<std::pair<float, float>>> original_LMK_seq;

    //for image processing
    int width;
    int height;
    Door door;
    int videoSize;
    //Camera* cameraPntr;
    int videoY;
    int videoX;
    int fps;
    std::vector<cv::Mat> img_seq;

    //FaceDetect myFaceDetect;
    LmkModel myLmkModel;

    std::string enrollName;
};

#endif //AUTHENTIFACEDEMO_C_PROCESSEMBEDDINGS_H