#include "Controller.h"
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include "QRDetector.h"
#include "Warper.h"
#include "RectangleDetector.h"
#include <iostream>
#include <string>
#include <opencv2/objdetect.hpp>

Controller::Controller(const std::string& inputImgPath, const std::string& storedDataPath)
    : m_inputImagePath(inputImgPath)
    , m_storedDataPath(storedDataPath)
{
    //QRDetector detector;


    //cv::Mat inputImg = imread(inputImgPath, cv::IMREAD_UNCHANGED);
    //cv::Mat originalImg = imread(originalImgPath, cv::IMREAD_UNCHANGED);

    //std::vector<cv::Point2f> src = detector.detect(originalImg);
    //float h = src[3].y - src[0].y;
    //float w = src[1].x - src[0].x;


    //cv::Mat lilImage = detector.warp(inputImg, originalImg, h, w);
    //
    //imshow("Overlay Image", originalImg);
    ////std::vector<std::vector<cv::Point>> rect = detector.detectRectangle(lilImage);
    //cv::waitKey(0);
    
}

void Controller::setInputImagePath(const std::string& inputImgPath)

{
    m_inputImagePath = inputImgPath;
}


Controller::ProcessError Controller::startProcess()
{
    cv::Mat inputImg = cv::imread(m_inputImagePath, cv::IMREAD_UNCHANGED);
    resize(inputImg, inputImg, cv::Size(1000, 1200));
    /*
    if (inputImg.empty())
    {
        return ProcessError::eCantOpenInputImage;
    }
    cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();


    std::vector<cv::Point2f> src;

    std::string data = qrDecoder.detectAndDecode(inputImg, src);
    if (src.empty())
    {
        return ProcessError::eCantFindQr;
    }
    std::cout << cv::Mat(src).t() << std::endl;

    cv::Mat originalImg = imread(m_storedDataPath + data + ".png", cv::IMREAD_UNCHANGED);*/
    /*cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

    
    std::vector<cv::Point2f> src;

    std::string data = qrDecoder.detectAndDecode(inputImg, src);
    if (src.empty())
    {
        return ProcessError::eCantFindQr;
    }
    std::cout << cv::Mat(src).t() << std::endl;

    cv::Mat originalImg = imread(m_storedDataPath + data + ".png", cv::IMREAD_UNCHANGED);
    if (originalImg.empty())
    {
        return ProcessError::eCantFindQr;
    }

    
    std::vector<cv::Point2f> srcOriginal;

    std::string dataOriginal = qrDecoder.detectAndDecode(originalImg, srcOriginal);

    if (dataOriginal != data)
    {
        std::cout << __FUNCSIG__ << " line : " << __LINE__ << std::endl;
        return ProcessError::еUndefined;
    }

    cv::Mat matrix, imgWarp;
    if (srcOriginal.empty())
    {
        std::cout << "can't find qr points in original image\n";
        return ProcessError::еUndefined;
    }
    

    matrix = getPerspectiveTransform(src, srcOriginal);

    warpPerspective(inputImg, imgWarp, matrix, inputImg.size());*/
    //for (int i = 0; i < 4; i++)
    //{
    //    circle(inputImg, src[i], 15, cv::Scalar(255, 0, 0), 2);
    //}
    Warper warper(inputImg);
    Controller::ProcessError error = warper.getOriginalImg(m_storedDataPath);
    if (error != Controller::ProcessError::eNo)
    {
       
        return error;
    }
    cv::Mat imgWarp = warper.warp();
    cv::namedWindow("warpped", cv::WINDOW_FREERATIO);
    cv::namedWindow("inputImg", cv::WINDOW_FREERATIO);
    RectangleDetector detector(imgWarp);
    std::vector <std::vector<cv::Point>> rect = detector.detectRectangel();
    cv::namedWindow("detected", cv::WINDOW_FREERATIO);
    cv::imshow("detected", imgWarp);
    cv::imshow("inputImg", inputImg);
    cv::waitKey();

    return error;

}