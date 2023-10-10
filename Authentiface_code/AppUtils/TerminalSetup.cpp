//
// Created by Drew Sumsion on 8/15/22.
//

#include "TerminalSetup.h"
#include <iostream>
std::map<std::string, std::any> TerminalSetup::SetupHelp() {

    Door myDoor = Door(COMPUTER_CAMERA, GPIO_LOCK);
    Camera* myCamera = myDoor.GetCamera();
    DoorLock* myLock = myDoor.GetLock();

    //get thresholds
    float idThres = GetLmkTh(SETTINGS_PATH_ID);
    float lmkThres = GetLmkTh(SETTINGS_PATH_LMK);
    std::map<std::string, float> passwordStrength = GetPasswordStrength();
    if (idThres == -1 || lmkThres == -1) {
        throw std::invalid_argument(THRESH_ERROR);
    }

    // get the videoSize, etc.
    int videoSize, width, height, fps, videoX, videoY;
    videoSize = VARIABLE_VIDEO_SIZE;
    width = myCamera->get(cv::CAP_PROP_FRAME_WIDTH);
    height = myCamera->get(cv::CAP_PROP_FRAME_HEIGHT);
    fps = myCamera->get(cv::CAP_PROP_FPS);
    // fps = 15;
    //TODO WHY IS THIS IF STATEMENT HERE? the fps>30....I carried it over from the other demo. It was just hard coded to a value....I don't think that is good.
//    if (fps > 30)  {
//        fps = door.GetFps();
//     }
    if (videoSize > height) {
        videoSize = height;
    }

    if (DEBUG) {
        std::cout << "Frame dimension: " << width << "x" << height 
            << "\nROI size: " << videoSize 
            << "\nFPS: " << fps << std::endl;
    }

    videoX = std::round((width - videoSize) / 2);
    videoY = std::round((height - videoSize) / 2);

    //TODO implement a FaceID and FaceMesh.

    //Do I need to implement them here? Can't they just be acessed by class include?
//    detectFace =
//    faceMesh =
//    faceID =

    std::map<std::string, std::any> data;
    data[ID_THRESH] = idThres;
    data[LMK_THRESH] = lmkThres;
    data[PASSWORD_STRENGTH] = passwordStrength;
    data[DOOR] = myDoor;
    data[VIDEO_SIZE] = videoSize;
    data[CAMERA] = myCamera;
    data[WIDTH] = width;
//    data.insert(std::pair<std::string, int>(WIDTH, width));
    data[HEIGHT] = height;
    data[FPS] = fps;
    data[VIDEO_X] = videoX;
    data[VIDEO_Y] = videoY;
    data[LOCK] = myLock;
//    data[DETECT_FACE] = detectFace;
//    data[FACE_MESH] = faceMesh;
//    data[FACE_ID] = faceID;
    data[ENROLL] = true;//TODO Implement logic for enroll.

    return data;
}

float TerminalSetup::GetLmkTh(std::string path) {

    std::fstream newfile;
    newfile.open(path,std::ios::in);
    std::string tp;

    if (newfile.is_open()){
        getline(newfile, tp);
        newfile.close();
    }
    else {
        return -1;
    }

    return std::stof(tp);
}

float FindPercentile(std::string text, int num) {
    std::string findMe = std::to_string(num) + PERCENTILE_LABEL;
    float result;
    int startIndex = text.find(findMe);
    if (startIndex != std::string::npos) {
        std::string substring = text.substr(startIndex);
        int endIndex = substring.find("\n");
        std::string result_str = text.substr(startIndex + findMe.size(), startIndex + endIndex);
        float result = std::stof(result_str);
    }
    else {
        throw std::invalid_argument(POWER_LOAD_ERROR);
    }
    return result;

}

std::map<std::string, float> TerminalSetup::GetPasswordStrength() {


    //read the file contents first.
    std::fstream newfile;
    newfile.open(SETTINGS_PATH_STRENGTH,std::ios::in);
    std::string tp;
    std::string fullFileContents = "";

    if(newfile.is_open()) {
        while(getline(newfile,tp)) {
            fullFileContents += tp + "\n";
        }
        newfile.close();
    }
    else {
        throw std::invalid_argument(POWER_LOAD_ERROR);
    }

    std::map<std::string, float> dataPercentiles;
    dataPercentiles[PERCENTILE_SCORE_0] = FindPercentile(fullFileContents, PERCENTILE_SCORE_0_NUM);
    dataPercentiles[PERCENTILE_SCORE_1] = FindPercentile(fullFileContents, PERCENTILE_SCORE_1_NUM);
    dataPercentiles[PERCENTILE_SCORE_2] = FindPercentile(fullFileContents, PERCENTILE_SCORE_2_NUM);
    dataPercentiles[PERCENTILE_SCORE_3] = FindPercentile(fullFileContents, PERCENTILE_SCORE_3_NUM);
    dataPercentiles[PERCENTILE_SCORE_4] = FindPercentile(fullFileContents, PERCENTILE_SCORE_4_NUM);
    dataPercentiles[PERCENTILE_SCORE_5] = FindPercentile(fullFileContents, PERCENTILE_SCORE_5_NUM);
    dataPercentiles[PERCENTILE_SCORE_6] = FindPercentile(fullFileContents, PERCENTILE_SCORE_6_NUM);
    dataPercentiles[PERCENTILE_SCORE_7] = FindPercentile(fullFileContents, PERCENTILE_SCORE_7_NUM);
    dataPercentiles[PERCENTILE_SCORE_8] = FindPercentile(fullFileContents, PERCENTILE_SCORE_8_NUM);
    dataPercentiles[PERCENTILE_SCORE_9] = FindPercentile(fullFileContents, PERCENTILE_SCORE_9_NUM);
    dataPercentiles[PERCENTILE_SCORE_10] = FindPercentile(fullFileContents, PERCENTILE_SCORE_10_NUM);
    dataPercentiles[STRENGTH_LABEL] = VARIABLE_PASSWORD_STRENGTH_SETTING;

    return dataPercentiles;
}