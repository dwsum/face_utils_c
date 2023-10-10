#ifndef AUTHENTIFACEDEMO_C_PROCESSIMAGES_H
#define AUTHENTIFACEDEMO_C_PROCESSIMAGES_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <map>
#include <any>
#include <vector>
#include <tuple>
#include <fstream>

#include "../DoorUtils/Door.h"
//#include "../face_utils/facetools/detection/FaceDetect.h"
#include "../AppUtils/ProcessEmbeddings.h"
#include "../face_utils/facetools/detection/Lmk.h"

class ProcessImages {
public:
    ProcessImages();
    ProcessImages(std::map<std::string, std::any> transferData);
    void ProcessBatch(std::vector<std::vector<std::pair<float, float>>> receivedMeshSequence, std::vector<std::pair<float, float>> idemb);
    void SetData(std::map<std::string, std::any> transferData);
    void ProcessImg();
    void StartEnrollment();

private:
    Lmk myLmkHelper;

    //variables
    bool enroll;
    float idTH;
    float lmkTH;

    float lmkEMB;
    float idEMB;

    ProcessEmbeddings processEmbeddings;

    std::vector<std::vector<std::pair<float, float>>> original_LMK_seq;

    //for image processing
    std::vector<std::vector<std::pair<float, float>>> meshSequence;
    int width;
    int height;
    Door door;
    int videoSize;
    //Camera* cameraPntr;
    int videoY;
    int videoX;
    int fps;
    std::vector<cv::Mat> img_seq;
    //Lmk myLmkHelper;

    //FaceDetect myFaceDetect;

    //flags
    bool processingBatch;
    bool isProcessing;

};

#endif //AUTHENTIFACEDEMO_C_PROCESSIMAGES_H