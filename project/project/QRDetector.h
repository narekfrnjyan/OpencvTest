#pragma once
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/objdetect.hpp>


class QRDetector
{
public:
	void display(cv::Mat& im, cv::Mat& bbox);
	cv::Mat  warp(cv::Mat inputImage, cv::Mat originalImage, int h, int w);
	std::vector<cv::Point2f> detect(cv::Mat inputImage);
	std::vector<std::vector<cv::Point>> detectRectangle(cv::Mat inputImage);

	
};

