#pragma once
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include "controller.h"
class Warper
{
public:
	Warper(cv::Mat inputImg);
	Controller::ProcessError getOriginalImg(std::string stored_path);
	cv::Mat warp();
private:
	cv::Mat m_inputImg;
	cv::Mat originalImg;
	std::vector<cv::Point2f> src;
	std::vector<cv::Point2f> srcOriginal;
};

