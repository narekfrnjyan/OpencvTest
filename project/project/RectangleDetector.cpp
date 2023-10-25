#include "RectangleDetector.h"
#include <iostream>

RectangleDetector::RectangleDetector(cv::Mat warpedImg):
warpedImg(warpedImg)
{
}

std::vector<std::vector<cv::Point>> RectangleDetector::detectRectangel()
{
    cv::Mat warppedGray, thresholded;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> rectengularContours;
    std::vector<std::vector<cv::Point>> rectangle;

    //resize(warpedImg, warpedImg, cv::Size(warpedImg.cols + 20, warpedImg.rows + 20));
    cv::cvtColor(warpedImg, warppedGray, cv::COLOR_BGR2GRAY);
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
    auto maxArea = std::max_element(areas.begin(), areas.end());
    float second = 0.0f;
    for (int i = 0; i < rectengularContours.size(); i++) {
        if (areas[i] < *maxArea && areas[i]>second) {
            second = areas[i];
            k = i;
        }
    }
    rectangle.push_back(rectengularContours[k]);
    cv::drawContours(warpedImg, rectangle, -1, cv::Scalar(0, 255, 0), 1);
    cv::waitKey(0);
    return rectangle;
}
