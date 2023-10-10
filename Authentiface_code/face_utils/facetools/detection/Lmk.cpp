//
// Created by Drew Sumsion on 8/22/22.
//

#include "Lmk.h"

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "multi_face_landmarks";
constexpr char kWindowName[] = "MediaPipe";

std::mutex mtxxX; // Mutex to protect concurrent access to the class data (if any).

// mediapipe::CalculatorGraph graph;

Lmk::Lmk() {
    std::cout << "Lmk constructor called." << std::endl;
    std::string calculator_graph_config_contents;
    
    //TODO put this string into the Constants.h file.
    mediapipe::file::GetContents(
        PATH_PB_TXT_FILE,
        &calculator_graph_config_contents);
    
    mediapipe::CalculatorGraphConfig config =
        mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
            calculator_graph_config_contents);

    std::unique_ptr<mediapipe::CalculatorGraph> graph = std::make_unique<mediapipe::CalculatorGraph>();

    graph->Initialize(config);
    mediapipe::StatusOrPoller sop1 = graph->AddOutputStreamPoller(kOutputStream);
    poller = std::make_unique<mediapipe::OutputStreamPoller>(std::move(sop1.value()));
    graph->StartRun({});
    
    bool grab_frames = true;

    graphPointer = std::move(graph); // Move the ownership to the unique_ptr member.  
}

std::vector<std::pair<float, float>> Lmk::GenLmk(cv::Mat roi) {
    // mediapipe::CalculatorGraph& graph = *graphPointer;
    std::lock_guard<std::mutex> lock(mtxxX);
    cv::Mat camera_frame;

    //Convert from BGR to RGB
    cv::cvtColor(roi, camera_frame, cv::COLOR_BGR2RGB);

    //Flips the frame horizontally. This is change the landmark data
    // if (!load_video) {
    //   cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);
    // }

    // Wrap Mat into an ImageFrame.
    auto input_frame = absl::make_unique<mediapipe::ImageFrame>(
        mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows,
        mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
    camera_frame.copyTo(input_frame_mat);

    // Send image packet into the graph.
    size_t frame_timestamp_us =
        (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
    graphPointer->AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us)));
    
    // Get the graph result packet, or stop if that fails.
    std::vector<std::pair<float, float>> allPoints;
    mediapipe::Packet packet;

    if (poller->Next(&packet) && !packet.IsEmpty()){
        //Segmentation fault occurs here because the packet is empty.
        std::vector<mediapipe::NormalizedLandmarkList, std::allocator<mediapipe::NormalizedLandmarkList>> test = packet.Get<std::vector<mediapipe::NormalizedLandmarkList, std::allocator<mediapipe::NormalizedLandmarkList> >>();
        
        for(int i = 0; i < 478; i++) {
            std::pair<float, float> thisPoint(test[0].landmark(i).x(), test[0].landmark(i).y());
            allPoints.push_back(thisPoint);
        }
        std::cout << "(" << test[0].landmark(0).x() << ", " << test[0].landmark(0).y() << ", " << test[0].landmark(0).z() << ")" << std::endl;

    }else{
        std::cout << "Packet is empty" << std::endl;
    }
    
    return allPoints;
}

std::vector<std::vector<std::pair<float, float>>> Lmk::PackLmk(std::vector<std::vector<std::pair<float, float>>> meshSequence){

    std::vector<std::vector<std::pair<float, float>>> processed;

    for (int i = 0; i < meshSequence.size(); i++) {
        std::vector<std::pair<float, float>> thisLmk = meshSequence[i];
        std::vector<std::pair<float, float>> normedLmk = _proc_lmk(thisLmk);
        if (normedLmk.size() > 0) {
            processed.push_back(normedLmk);
        }
    }

    return processed;
}

std::vector<std::pair<float, float>> Lmk::_proc_lmk(std::vector<std::pair<float, float>> lmk){
    std::cout << "Inside _proc_lmk" << std::endl;

    // std::cout << "lmk.size(): " << lmk.size() << std::endl;//lmk.size(): 478

    std::vector<std::pair<float, float>> normed;
    
    std::pair<float, float> noseBridge = lmk[noseBridgeIndex];
    std::pair<float, float> noseTip = lmk[noseTipIndex];

    float vecBaseX = noseTip.first - noseBridge.first;
    float vecBaseY = noseTip.second - noseBridge.second;

    //This is the euclidean distance between the nose tip and the nose bridge.
    float yBase = sqrt(pow(vecBaseX, 2) + pow(vecBaseY, 2));

    //This is the unit vector of the nose tip to the nose bridge.
    float vecBaseXNorm = vecBaseX / yBase;

    //This is the unit vector of the nose tip to the nose bridge.
    float vecBaseYNorm = vecBaseY / yBase;

    //This is the unit vector of the nose tip to the nose bridge.
    std::pair<float, float> vecBase(vecBaseXNorm, vecBaseYNorm);

    //This is the unit vector of the nose tip to the nose bridge.
    std::vector<std::pair<float, float>> vecCurrOrg;
    std::vector<float> yCurr;

    //Find the euclidean distance between the nose tip and the nose bridge.
    //Do this for all points in the landmark except the nose tip and the nose bridge.
    for (int i = 0; i < lmk.size(); i++) {
        if (i != noseBridgeIndex && i != noseTipIndex) {
            std::pair<float, float> thisPoint = lmk[i];
            float thisVecCurrX = thisPoint.first - noseBridge.first;
            float thisVecCurrY = thisPoint.second - noseBridge.second;
            float thisYCurr = sqrt(pow(thisVecCurrX, 2) + pow(thisVecCurrY, 2));
            yCurr.push_back(thisYCurr);
            float thisVecCurrXNorm = thisVecCurrX / thisYCurr;
            float thisVecCurrYNorm = thisVecCurrY / thisYCurr;
            std::pair<float, float> thisVecCurr(thisVecCurrXNorm, thisVecCurrYNorm);
            vecCurrOrg.push_back(thisVecCurr);
        }
    }

    //Print size of vecCurrOrg
    // std::cout << "vecCurrOrg.size(): " << vecCurrOrg.size() << std::endl;//vecCurrOrg.size(): 476

    //Find the dot product between vecCurr and vecBase.
    std::vector<float> dot;
    for (int i = 0; i < vecCurrOrg.size(); i++) {
        std::pair<float, float> thisPoint = vecCurrOrg[i];
        float thisDot = thisPoint.first * vecBase.first + thisPoint.second * vecBase.second;
        dot.push_back(thisDot);
    }
    
    //Clip the dot product between -1 and 1.
    for (int i = 0; i < dot.size(); i++) {
        float thisDot = dot[i];
        if (thisDot < -1) {
            thisDot = -1;
        } else if (thisDot > 1) {
            thisDot = 1;
        }
        dot[i] = thisDot;
    }

    //Find the angle between vecCurr and vecBase.
    std::vector<float> angl;
    for (int i = 0; i < dot.size(); i++) {
        float thisDot = dot[i];
        float thisAngl = acos(thisDot);
        angl.push_back(thisAngl);
    }

    //Find the cross product between vecCurr and vecBase.
    std::vector<float> cross;
    for (int i = 0; i < vecCurrOrg.size(); i++) {
        std::pair<float, float> thisPoint = vecCurrOrg[i];
        float thisCross = thisPoint.first * vecBase.second - thisPoint.second * vecBase.first;
        cross.push_back(thisCross);
    }

    //Clip the cross product between -1 and 1.
    for (int i = 0; i < cross.size(); i++) {
        float thisCross = cross[i];
        if (thisCross < -1) {
            thisCross = -1;
        } else if (thisCross > 1) {
            thisCross = 1;
        }
        cross[i] = thisCross;
    }

    //Find the angle from the sine of the cross product.
    std::vector<float> anglFromSine;
    for (int i = 0; i < cross.size(); i++) {
        float thisCross = cross[i];
        float thisAnglFromSine = asin(thisCross);
        anglFromSine.push_back(thisAnglFromSine);
    }

    //Find the x and y coordinates of the normalized landmark.
    for (int i = 0; i < anglFromSine.size(); i++) {
        float thisAnglFromSine = anglFromSine[i];
        float thisYCurr = yCurr[i];
        float thisX = thisYCurr * sin(thisAnglFromSine);
        float thisY = thisYCurr * cos(angl[i]);
        std::pair<float, float> thisNormed(thisX, thisY);
        normed.push_back(thisNormed);
    }

    return normed;
}

