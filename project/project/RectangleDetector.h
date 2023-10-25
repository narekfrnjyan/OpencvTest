#pragma once
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2/objdetect.hpp>
class RectangleDetector{
public:
	
public:
	RectangleDetector(cv::Mat warpedImg);
	std::vector<std::vector<cv::Point>> detectRectangel();

private:
	cv::Mat warpedImg;
};

