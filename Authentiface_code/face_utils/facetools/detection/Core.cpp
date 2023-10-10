#include "Core.h"

cv::Mat Core::ResizeToCeiling(cv::Mat img, float targetSize){
    std::cout << "In ResizeToCeiling\n";
    // std::cout << "roi size: " << img.size() << std::endl;
    float h0, w0;
    
    h0 = img.rows;
    w0 = img.cols;

    // std::cout << "w0: " << w0 << std::endl;
    // std::cout << "h0: " << h0 << std::endl;

    float w_, h_;

    if (w0 >= h0) {
        w_ = targetSize;
        h_ = static_cast<int>(round(h0 * static_cast<double>(targetSize) / w0));
    } else {
        h_ = targetSize;
        w_ = static_cast<int>(round(w0 * static_cast<double>(targetSize) / h0));
    }

    // std::cout << "w_: " << w_ << std::endl;
    // std::cout << "h_: " << h_ << std::endl;

    cv::Size size_(h_, w_);
    // std::cout << "size_: " << size_ << std::endl;
    cv::Mat img_;
    cv::resize(img, img_, size_, 0, 0, cv::INTER_LINEAR);
    // std::cout << "img_ size: " << img_.size() << std::endl;
    // std::cout << "img_ type: " << img_.type() << std::endl;

    //convert img_ to uint8
    img_.convertTo(img_, CV_8U);
    // std::cout << "new img_ type: " << img_.type() << std::endl;
    //Print img_ with its size and type)
    
    return img_;
}

cv::Mat Core::ResizeFaceRegion(cv::Mat img, float targetSize){
    std::cout << "In ResizeFaceRegion\n";
    //Put the shape of img into a list
    std::array<float,3> _shape = {img.rows, img.cols, img.channels()};
    // std::cout << "img size: " << img.size() << std::endl;

    cv::Mat roi_ = ResizeToCeiling(img, targetSize);

    float h_ = roi_.rows;
    float w_ = roi_.cols;
    
    // std::cout << "ResizeFaceRegion - w_: " << w_ << std::endl;
    // std::cout << "ResizeFaceRegion - h_: " << h_ << std::endl;

    _shape[0] = targetSize;
    _shape[1] = targetSize;

    cv::Mat canvas(targetSize, targetSize, CV_8UC3, cv::Scalar(0, 0, 0));
    // std::cout << "x size: " << x.size() << std::endl;

    if (h_ == w_) {
        // std::cout << "Height and width are equal\n";
        //roi_.copyTo(x(cv::Rect(0, 0, w_, h_)));
        roi_.copyTo(canvas(cv::Rect(0, 0, w_, h_)));
        
    } else if (h_ < w_) {
        // std::cout << "Height is less than width\n";
        int top_ = static_cast<int>((targetSize - h_) / 2);
        int bottom_ = top_ + h_;
        roi_.copyTo(canvas(cv::Rect(0, top_, w_, bottom_)));
    } else {
        // std::cout << "Height is greater than width\n";
        int left_ = static_cast<int>((targetSize - w_) / 2);
        int right_ = left_ + w_;
        roi_.copyTo(canvas(cv::Rect(left_, 0, right_, h_)));
    }

    // std::cout << "canvas size: " << canvas.size() << std::endl;
    return canvas;
}

cv::Mat Core::CropFaceRegion(cv::Mat arr, std::array<float, 4> detected, float expansion){
    std::cout << "In CropFaceRegion\n";

    // cv::Rect bbox(detected[0], detected[1], detected[2], detected[3]);
    //Height is rows, width is cols
    int h0 = arr.rows;
    int w0 = arr.cols;
    // std::cout << "CropFaceRegion - h0: " << h0 << std::endl;
    // std::cout << "CropFaceRegion - w0: " << w0 << std::endl;
    int xmin = detected[0];
    int ymin = detected[1];
    int xmax = detected[2];
    int ymax = detected[3];
    int _w = xmax - xmin + 1;
    int _h = ymax - ymin + 1;
    int _top = ymin;
    int _left = xmin;

    //Print all the above values
    // std::cout << "xmin: " << xmin << std::endl;
    // std::cout << "ymin: " << ymin << std::endl;
    // std::cout << "xmax: " << xmax << std::endl;
    // std::cout << "ymax: " << ymax << std::endl;
    // std::cout << "_w: " << _w << std::endl;
    // std::cout << "_h: " << _h << std::endl;
    // std::cout << "_top: " << _top << std::endl;
    // std::cout << "_left: " << _left << std::endl;

    double _half_size = std::max(_w, _h) * expansion / 2;
    // std::cout << "_half_size: " << _half_size << std::endl;
    int _rc = _top + (_h / 2);
    int _cc = _left + (_w / 2);

    int top_ = static_cast<int>(round(_rc - _half_size));
    int left_ = static_cast<int>(round(_cc - _half_size));
    int bottom_ = static_cast<int>(round(_rc + _half_size));
    int right_ = static_cast<int>(round(_cc + _half_size));

    int top_new = std::max(0, top_);
    int left_new = std::max(0, left_);
    int bottom_new = std::min(h0, bottom_);
    int right_new = std::min(w0, right_);

    //print out all the next values
    // std::cout << "new values: " << std::endl;
    // std::cout << "top_new: " << top_new << std::endl;
    // std::cout << "left_new: " << left_new << std::endl;
    // std::cout << "bottom_new: " << bottom_new << std::endl;
    // std::cout << "right_new: " << right_new << std::endl;

    cv::Mat img = arr(cv::Range(top_new, bottom_new), cv::Range(left_new, right_new)).clone();
    // std::cout << "img size: " << img.size() << std::endl;

    return img;
}

cv::Mat Core::CropFace(cv::Mat img, std::array<float, 4> detected, float expansion, float targetSize, bool largest){
    // std::cout << "In CropFace\n";
    cv::Mat roi = CropFaceRegion(img, detected, expansion);
    cv::Mat roi_= ResizeFaceRegion(roi, targetSize);

    //print size of roi
    // std::cout << "roi_ size before return: " << roi_.size() << std::endl;
    return roi_;
}

/*
GetCroppedFaceImage

Crop, resize, and center the face image(s) using detected bounding box(es).

:param img: A whole frame image.
:param face_bbox: Bounding box or a list of bounding boxes.
:param expansion: The rate to expand the detected box.
:param target_size: The size of the returned square face image.
:param largest: If True, only return the the face with largest area.
:return:
*/
cv::Mat Core::GetCroppedFaceImage(cv::Mat roi, std::array<float, 4> detected, float expansion, float targetSize, bool largest){
    //TOOD: Add support for multiple faces as in python build.
    //Currently the code only supports there being a single face in the frame.
    
    std::cout << "In GetCroppedFaceImage\n";

    // CropFace(roi, detected, expansion, targetSize, largest);

    cv::Mat _roi = CropFace(roi, detected, expansion, targetSize, largest);

    // std::cout << "_roi size: " << _roi.size() << std::endl;

    //Write the image to a file for data analysis
    // cv::imwrite("cropped_image.jpg", _roi);

    //print the rgb value of the first pixel in the frame the same way
    //as it would in python with the array notation [0,0,255]
    // std::cout << "CORE-_roi[0][0]: " << _roi.at<cv::Vec3b>(0,0) << std::endl;

    //print rgb value of first column of pixels
    // std::cout << "CORE-_roi[0]: " << _roi.at<cv::Vec3b>(0) << std::endl;

    return _roi;
}