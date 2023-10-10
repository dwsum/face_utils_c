//
// Created by Drew Sumsion on 8/13/22.
//

#ifndef AUTHENTIFACEDEMO_C_FRAMEANALYZE_H
#define AUTHENTIFACEDEMO_C_FRAMEANALYZE_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <map>
#include <any>
#include <vector>
#include <chrono>
#include <ctime>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <torch/script.h>
#include <torch/torch.h>

#include "../DoorUtils/Door.h"

#include "../face_utils/facetools/motion/Preprocessing.h"
#include "../face_utils/facetools/detection/Lmk.h"
#include "../face_utils/facetools/detection/Core.h"
#include "../face_utils/facetools/detection/FaceDetect.h"
#include "../AppUtils/ProcessImages.h"
#include "../face_utils/facetools/representation/CNNEmbedding.h"


class FrameAnalyze {
public:
    FrameAnalyze();
    FrameAnalyze(std::map<std::string, std::any> data);
    void IsFace(cv::Mat roi);
    cv::Mat CheckCurrRecording(cv::Mat roi);
    torch::Tensor IsEnrolled(cv::Mat roi);
    void readDataFromQueue();

private:
    std::thread readerThread;
    std::thread runFaceIDThread;

    //variables

    //for image processing

    //meshSequence is a vector of vectors of pairs of floats that 
    //make up the x and y coordinates of the landmarks.
    std::vector<std::vector<std::pair<float, float>>> meshSequence;

    //Vector of tensors called faceIDSequence
    std::vector<torch::Tensor> faceIDSequence;
    
    
    int numImages;
    int maxFaceIDFrames;
    std::chrono::system_clock::time_point faceStartTime;
    bool faceFound;
    bool isProcessing;
    bool isRecording;
    float findFaceSeconds;
    float waitAfterRecording;
//    thread threadProcess;
    int width;
    int height;
//    detectFace
    Door door;
    int videoSize;
    Camera* cameraPntr;
    int videoY;
    int videoX;
    int fps;
    ProcessImages processImagesPntr;
//    uiPntr
//    faceDetector
//    faceMesh
    float idTH;
    int totalNumFrames;
    std::vector<cv::Mat> img_seq;
    std::thread faceMesh_thread;
    std::chrono::system_clock::time_point recordingStartTime;
    std::chrono::system_clock::time_point oldCurrRecordingCheckpointTime;
    std::chrono::system_clock::time_point newCurrRecordingCheckpointTime;
    std::chrono::system_clock::time_point finalizeRecordingTime;
    Preprocessing myPreprocessing;
    bool passFaceID;
    int cntFaceID = 0;
    bool doEveryOther;
    
    std::vector<std::pair<float, float>> idemb;
    
    FaceDetect myFaceDetect;

    std::queue<cv::Mat> frameAnalyze_queueFaceMesh;

    //functions
    void StartRecording();
    void ResetFaceID();
    cv::Mat CurrRecording(cv::Mat roi);
    void FinalizeRecording();
    void Process();
    void StartProcessing();
    void RunFaceID();
};


#endif //AUTHENTIFACEDEMO_C_FRAMEANALYZE_H