//
// Created by Drew Sumsion on 8/18/22.
//

#ifndef AUTHENTIFACEDEMO_C_CNNEMBEDDING_H
#define AUTHENTIFACEDEMO_C_CNNEMBEDDING_H

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <torch/script.h>
#include <torch/torch.h>


class CNNEmbedding {
public:
    //variables
    CNNEmbedding();
    torch::Tensor Predict(cv::Mat roi);

private:
    torch::jit::script::Module model;
};

// Define a C wrapper function
extern "C" {
    CNNEmbedding* CreateCNNEmbedding(); // Create an instance of CNNEmbedding
    void ReleaseCNNEmbedding(CNNEmbedding* instance); // Release the instance
    void Predict2(CNNEmbedding* instance, unsigned char* data, int width, int height, int channels); // Call Predict on the instance
}


#endif //AUTHENTIFACEDEMO_C_CNNEMBEDDING_H
