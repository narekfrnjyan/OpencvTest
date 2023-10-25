#include "QRDetector.h"
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/objdetect.hpp>
#include <algorithm>

void QRDetector::display(cv::Mat& im, cv::Mat& bbox)
{
    int n = bbox.rows;
    for (int i = 0; i < n; i++)
    {
        line(im, cv::Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)),
                cv::Point2i(bbox.at<float>(i, 2), bbox.at<float>(i, 3)),
                cv::Scalar(255, 0, 0), 3);
    }
    /*cv::imshow("Result", im);*/
    std::cout << n << std::endl;
}

std::vector<std::vector<cv::Point>> QRDetector::detectRectangle(cv::Mat inputImage)
{
    cv::Mat warppedGray, thresholded;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> rectengularContours;
    std::vector<std::vector<cv::Point>> rectangle;

    
    cv::cvtColor(inputImage, warppedGray, cv::COLOR_BGR2GRAY);
    cv::threshold(warppedGray, thresholded, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
    cv::findContours(thresholded, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    
    
    int k = 0;
    std::vector<float> areas;
    for (int i = 0; i < contours.size(); i++) {
        float epsilion = 0.01 * cv::arcLength(contours[i], true);
        cv::approxPolyDP(contours[i], contours[i], epsilion, true);

        std::cout << contours[i].size() << std::endl;
        if (contours[i].size() == 4) {
            rectengularContours.push_back(contours[i]);
            areas.push_back(contourArea(contours[i]));
        }
    }
    auto maxArea = std::max_element(areas.begin(),areas.end());
    float second = 0.0f;
    for (int i = 0; i < rectengularContours.size(); i++) {
        if (areas[i] < *maxArea && areas[i]>second) {
            second = areas[i];
            k = i;
        }
    }
    rectangle.push_back(rectengularContours[k]);



    cv::drawContours(inputImage, rectangle, -1, cv::Scalar(0, 255, 0), 1);
   /* imshow("Rectified Thresholded QRCode", thresholded);*/
    
    imshow("detected", inputImage);
    
    cv::waitKey(0);

}


cv::Mat QRDetector::warp(cv::Mat inputImg, cv::Mat originalImg, int h, int w) {
    //originalImg.size()
    resize(inputImg, inputImg, cv::Size(originalImg.cols+20, originalImg.rows+20));
    cv::Point2f padding = cv:: Point2f(10.0f, 10.0f);
    if (inputImg.cols > inputImg.rows) {
        rotate(inputImg, inputImg, cv::ROTATE_90_CLOCKWISE);
    }

    cv::Mat bbox, rectifiedImage, matrix, imgWarp;
    imshow("img", inputImg);
    std::vector<cv::Point2f> src = detect(inputImg);
    cv::Point2f qrTopLeft = detect(originalImg)[0];
   
    if (!src.empty())
    {
        std::vector<cv::Point2f> dst = { qrTopLeft + padding + cv::Point2f(0.0f,0.0f),
                                         qrTopLeft + padding + cv::Point2f(w,0.0f),
                                         qrTopLeft + padding + cv::Point2f(w,h),
                                         qrTopLeft + padding + cv::Point2f(0.0f,h) };

        matrix = getPerspectiveTransform(src, dst);
        warpPerspective(inputImg, imgWarp, matrix, inputImg.size());

        for (int i = 0; i < 4; i++) 
        {
            circle(inputImg, src[i], 15, cv::Scalar(255, 0, 0), 2);
        }
        
    }
    else
        std::cout << "QR Code not detected" << std::endl;
   /* imshow("Warped", imgWarp);*/
    return imgWarp;
}


std::vector < cv::Point2f > QRDetector::detect(cv::Mat inputImage)
{
    
    cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

    cv::Mat bbox, rectifiedImage, matrix, imgWarp;
    std::vector<cv::Point2f> src;
    
    std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if (data.length() > 0)
    {
        std::cout << "Decoded Data : " << data << std::endl;
        
        src.resize(4);
        for (int i = 0; i < 8; i += 2) {
            src[i / 2] = { cv::Point2f(bbox.at<float>(0, i), bbox.at<float>(0, i + 1)) };
        }
        
        cv::waitKey(0);
    }

    return src;
}

