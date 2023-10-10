//
// Created by Drew Sumsion on 8/13/22.
//

#include "App.h"

App::App() : theAnalysis{} {
    TerminalSetup setupHelper;
    std::map<std::string, std::any> data = setupHelper.SetupHelp();

    theVid = VideoFeed(data);
    theAnalysis = FrameAnalyze(data);
    theProcessImgs = ProcessImages(data);
    door = std::any_cast<Door>(data[DOOR]);
    cameraPntr = std::any_cast<Camera*>(data[CAMERA]);
}

/*
Capture()

*/
void App::Capture() {

    //How performance intensive is it to check every frame for a new face?
    //Is it worth it to check every nth frame?
    while (true) {

        // if (cameraPntr->IsOnline()){
        //   if (cameraPntr->StartEnoll()) {
        //   //UserInterface::StartEnrollment();
        // }

        //Mat is a multi-channel array used to store images
        //roi is region of interest - the frame we're analyzing
        cv::Mat roi = theVid.GetFrame();
        if (!roi.empty()) {
            theAnalysis.IsFace(roi);
            cv::Mat theroi = theAnalysis.CheckCurrRecording(roi);
        };

        //Display the image in a window.
        imshow( "Frame", roi );

        // Press  ESC on keyboard to exit
        // waitKey() waits for a key event infinitely (when delay = 0) 
        char c=(char)cv::waitKey(25);
        if(c==27)
            break;
    }
    cv::destroyAllWindows();

    theVid.CloseCamera();
}