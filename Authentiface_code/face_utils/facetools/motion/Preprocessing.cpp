//
// Created by Drew Sumsion on 8/16/22.
// Modified by Tyler Perkins on 6/6/23
//

#include "Preprocessing.h"
#include <iostream>

Preprocessing::Preprocessing() {}

/*
FindFace()
Verifies that the user's face appears large enough in the frame to be 
readable.

returns whether the calculated faceHeight is greater than the threshhold
*/
bool Preprocessing::FindFace(cv::Mat roi, 
    FaceDetect& myFaceDetect, Door& door) {

    // std::cout << "In FindFace\n";
    std::array<float, 4> detected = DetectFaceHelper(roi, myFaceDetect);

    //Needs to include the image that's being checked out.
    //mediapipe::Detections detection = DetectFaceHelper(frameToCheck);

    //Verify data
    if (detected.size() != 4){
        std::cout << "ArraySize error!\n";
        return false;
    }
    if (detected[0] <= .1 || detected[1] <= .1 || detected[2] <= .1 || 
        detected[3] <= .1){
        std::cout << "Inaccurate data- face not detected yet.\n";
        return false;
    }

    float scaleFactor = 1;

    //Verify door is ready
    if (door.GetCamera()->IsOnline()){
        scaleFactor = door.GetCamera()->GetFaceScale();
    } else {
        std::cerr << "Error: Failed to verify camera online.\n";
        return false;
    }

    //TODO: Can all of the code below be replaced with the data held in 
    //detection.location_data().relative_bounding_box().height();
    //It appears to do the same thing...

    //Get faceHeight
    float ymin = detected[1];
    float ymax = detected[3];
    float imageHeight = float(roi.rows);
    //This seems to be the same thing as 
    //detection.location_data().relative_bounding_box().height();
    float faceHeight = (ymax - ymin)/imageHeight;

    // std::cout << "Here is the face height " << faceHeight << std::endl;
    // std::cout << "detected in FindFace: " << detected[0] << " " << detected[1] << " " 
    //     << detected[2] << " " << detected[3] << std::endl;

    return (faceHeight > scaleFactor);
}
/*
DetectFaceHelper
NOTE: This function can likely be replaced by
detection.location_data().relative_bounding_box().height();
used in the FindFace

return 
- an array with information of the bounding box
*/
std::array<float, 4> Preprocessing::DetectFaceHelper(cv::Mat roi, 
    FaceDetect& myFaceDetect) {
    
    // std::cout << "In DetectFaceHelper\n";

    // bool faceDetectResult = myFaceDetect.GenFaceDetect(roi);
    std::array<float, 4> detected = myFaceDetect.GenFaceDetect(roi);

    // std::cout << "detected in DetectFaceHelper: " << detected[0] << " " << detected[1] << " "
    //     << detected[2] << " " << detected[3] << std::endl;

    return detected;
}