#include "FaceDetect.h"

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "face_detections";
constexpr char kWindowName[] = "MediaPipe";

std::mutex mtxFaceDetect; // Mutex to protect concurrent access to the class data (if any).

// mediapipe::CalculatorGraph graphFaceDetect;

FaceDetect::FaceDetect() {

    std::cout << "Initializing FaceDetect\n";
    std::string calculator_graph_config_contents;

    mediapipe::file::GetContents(
        PATH_DETECT_FACE_PB_TXT_FILE,
        &calculator_graph_config_contents);

    mediapipe::CalculatorGraphConfig config =
        mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(
            calculator_graph_config_contents);

    std::unique_ptr<mediapipe::CalculatorGraph> graph = std::make_unique<mediapipe::CalculatorGraph>();

    graph->Initialize(config);
    mediapipe::StatusOrPoller sop1 = graph->AddOutputStreamPoller(kOutputStream);
    poller = std::make_unique<mediapipe::OutputStreamPoller>(std::move(sop1.value()));
    graph->StartRun({});

    graphPointerFaceDetect = std::move(graph); // Move the ownership to the unique_ptr member.
    
}

std::array<float, 4> FaceDetect::GenFaceDetect(cv::Mat roi) {
    // std::cout << "In GenFaceDetect\n";

    //This should unlock the mutex when it goes out of scope.
    std::lock_guard<std::mutex> lock(mtxFaceDetect);
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
    // std::cout << "Sending image packet into the graph\n";
    size_t frame_timestamp_us =
        (double)cv::getTickCount() / (double)cv::getTickFrequency() * 1e6;
    graphPointerFaceDetect->AddPacketToInputStream(
        kInputStream, mediapipe::Adopt(input_frame.release())
                          .At(mediapipe::Timestamp(frame_timestamp_us)));
    
    // Get the graph result packet, or stop if that fails.
    mediapipe::Packet packet;
    std::array<float, 4> detected;

    // std::cout << "Getting the graph result packet\n";
    if (poller->Next(&packet) && !packet.IsEmpty()){
        //Segmentation fault occurs here because the packet is empty.
        const std::vector<mediapipe::Detection>& detection_vector = packet.Get<std::vector<mediapipe::Detection, std::allocator<mediapipe::Detection>>>();
        
        // std::cout << "Detection vector: " << detection_vector[0].location_data().relative_bounding_box().height() << std::endl;

        const mediapipe::Detection& detection = detection_vector[0];
        float boundXmin = detection.location_data().relative_bounding_box().xmin();
        float boundYmin = detection.location_data().relative_bounding_box().ymin();
        float boundWidth = detection.location_data().relative_bounding_box().width();
        float boundHeight = detection.location_data().relative_bounding_box().height();

        float width = float(roi.cols);
        float height = float(roi.rows);
        
        float first = boundXmin * width;
        float second = boundYmin * height;
        float third = (boundXmin + boundWidth) * width;
        float fourth = (boundYmin + boundHeight) * height;

        detected = {first, second, third, fourth};

    }else{
        std::cout << "Packet is empty" << std::endl;
        detected = {0,0,0,0};
    }
    
    return detected;
}