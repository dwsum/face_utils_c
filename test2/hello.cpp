#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

extern "C" {
    void run(unsigned char* data, int width, int height, int channels) {
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

        cv::imshow("Frame in cpp",roi);
        cv::waitKey(0);


        std::cout << "Hello from C++!" << std::endl;
    }
}
