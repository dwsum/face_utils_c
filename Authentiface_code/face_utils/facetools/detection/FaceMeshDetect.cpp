#include "FaceMeshDetect.h"

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "multi_face_landmarks";
constexpr char kWindowName[] = "MediaPipe";

mediapipe::CalculatorGraph graph;

FaceMeshDetect::FaceMeshDetect() {
    std::string calculator_graph_config_contents;
    
    //Get the correct calculator loaded in for getting the FaceLandmarks
    mediapipe::file::GetContents(
        PATH_DETECT_FACE_PB_TXT_FILE,
        &calculator_graph_config_contents);
    
    mediapipe::CalculatorGraphConfig config =
        mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
            calculator_graph_config_contents);

    
    graph.Initialize(config);
    mediapipe::StatusOrPoller sop1 = graph.AddOutputStreamPoller(kOutputStream);
    poller = std::make_unique<mediapipe::OutputStreamPoller>(std::move(sop1.value()));
    graph.StartRun({});
    
    bool grab_frames = true;    
}

std::vector<std::pair<float, float>> FaceMeshDetect::GenFaceMeshDetect(cv::Mat roi) {
    cv::Mat camera_frame;
    cv::cvtColor(roi, camera_frame, cv::COLOR_BGR2RGB);

    //TODO discuss if we want to have this or not.
    // if (!load_video) {
      cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);
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
    graph.AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us)));
    
    
    // Get the graph result packet, or stop if that fails.
    std::vector<std::pair<float, float>> allPoints;
    mediapipe::Packet packet;

    int timesRun = 0;
    if (poller->Next(&packet)){
        
    } else {
        std::cout << "\nRetreiving packet information failed.\n The packet is a: " << typeid(&packet).name();
    }
    

    return allPoints;
}