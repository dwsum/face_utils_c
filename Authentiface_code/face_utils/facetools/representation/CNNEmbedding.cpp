//
// Created by Drew Sumsion on 8/18/22.
//

#include "CNNEmbedding.h"

CNNEmbedding::CNNEmbedding() {
    std::cout << "Initialize FaceID model.\n";

    model = torch::jit::load("tracedFaceIDModel_Authentiface.pt");
    
    model.to(torch::kCPU);

    model.eval();
}

torch::Tensor CNNEmbedding::Predict(cv::Mat roi) {
    // cv::Mat roi(height, width, CV_8UC3, data);
    // memcpy(roi.data, data, width * height * channels);
    // Make sure 'mat' is continuous (no padding between rows)
    std::cout << "before" << std::endl;
    // Check if the data type matches CV_8U, and if not, convert it
    // if (roi.type() != CV_8U) {
    //     std::cout << "converting\n";
    //     roi.convertTo(roi, CV_MAKETYPE(CV_8U, channels));
    // }
    // if (roi.isContinuous()) {
    //     std::cout << "in first if" << std::endl;
    //     memcpy(roi.data, data, width * height * channels);
    // } else {
    //     std::cout << "in second if" << std::endl;
    //     // If 'mat' is not continuous, copy row by row
    //     for (int i = 0; i < height; ++i) {
    //         memcpy(roi.ptr(i), data + i * width * channels, width * channels);
    //     }
    // }
    std::cout << "before imshow" << std::endl;
    // cv::imshow("Frame in cpp",roi);
    // std::cout << "after imshow" << std::endl;
    // cv::waitKey(0);

    std::cout << "In Predict\n";

    torch::NoGradGuard no_grad;

    //print dtype of the roi
    // std::cout << "roi type: " << roi.type() << std::endl;

    //print the rgb value of the first pixel in the frame the same way
    //as it would in python with the array notation [0,0,255]
    // std::cout << "CNNEMB - roi[0][0]: " << roi.at<cv::Vec3b>(0,0) << std::endl;
    std::cout << roi.type() << std::endl;
    std::cout << CV_8U << std::endl;
    std::cout << "CV_8UC3:" << CV_8UC3 << std::endl;

    // assert(roi.type() == CV_8U);

    std::cout << "after assert" << std::endl;
    std::cout << "roi:" << roi.size << std::endl;
    //Convert roi to a tensor
    // torch::Tensor x = torch::from_blob(roi.data, {1, roi.channels(), roi.rows, roi.cols}, torch::kFloat32);
    torch::Tensor x = torch::from_blob(roi.data, {1, roi.channels(), roi.rows, roi.cols}, torch::kUInt8);
    std::cout << "test here" << std::endl;
    // std::cout << x << std::endl;
    //Print out the rgb value of the first pixel in
    //the tensor x with array notation [0,0,255]
    // std::cout << "CNNEMB - x[0][0]: " << x[0][0] << std::endl;//Same data as roi[0][0]

    //print out the size of the tensor
    // std::cout << "x:" << x << std::endl;
    // std::cout << "x size: " << x.sizes() << std::endl;
    // x = x.to(torch::kFloat32);
    std::cout << "test here again" << std::endl;
    x = x.to(torch::kFloat32) * 2 - 1;
    // x = x * 2 - 1;
    std::cout << "test2 here" << std::endl;
    x = x.to(torch::kCPU);
    std::cout << "test3 here" << std::endl;
 
    torch::Tensor emb = model.forward({x}).toTensor()[0];
    std::cout << "test4 here" << std::endl;

    std::cout << "emb: " << emb << std::endl;

    torch::Tensor out = emb.detach().to(torch::kCPU);

    std::cout << "out: " << out << std::endl;

    return out;

    //Save the out to a .pt file for analysis
    // torch::save(out, "cpp_idemb.pt");
}



CNNEmbedding* CreateCNNEmbedding() {
    return new CNNEmbedding();
}

void ReleaseCNNEmbedding(CNNEmbedding* instance) {
    delete instance;
}

// torch::Tensor Predict(CNNEmbedding* instance, unsigned char* data, int width, int height, int channels) {
//     return instance->Predict(data, width, height, channels);
// }

void Predict2(CNNEmbedding* instance, unsigned char* data, int width, int height, int channels) {
    std::cout << "here\n";
    // void run() {
        // cv::Mat roi(height, width, CV_8U, data);
        cv::Mat roi(height, width, CV_8UC3, data);
        // memcpy(roi.data, data, width * height * channels);
        // Make sure 'mat' is continuous (no padding between rows)
        std::cout << "before" << std::endl;
        // Check if the data type matches CV_8U, and if not, convert it
        if (roi.type() != CV_8U) {
            std::cout << "converting\n";
            roi.convertTo(roi, CV_MAKETYPE(CV_8U, channels));
        }

        std::cout << "in outside predict" << std::endl;
        cv::imshow("Frame in cpp",roi);
        std::cout << "in outside predict2" << std::endl;
        cv::waitKey(0);
        std::cout << "in outside predict3" << std::endl;

        std::cout << "PyTorch version: "
                    << TORCH_VERSION_MAJOR << "."
                    << TORCH_VERSION_MINOR << "."
                    << TORCH_VERSION_PATCH << std::endl;
        std::cout << "CV_Version: " <<CV_VERSION << std::endl; 
        std::cout << "Major version : " << CV_MAJOR_VERSION << std::endl;
        std::cout << "Minor version : " << CV_MINOR_VERSION << std::endl;
        std::cout << "Subminor version : " << CV_SUBMINOR_VERSION << std::endl;
        
        std::cout << roi.type() << std::endl;
    std::cout << CV_8U << std::endl;
    std::cout << "CV_8UC3:" << CV_8UC3 << std::endl;
        // assert(roi.type() == CV_8U);

        std::cout << "Hello from C++!" << std::endl;
        torch::Tensor out;
        out = instance->Predict(roi);
}