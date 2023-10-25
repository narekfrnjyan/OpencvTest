#include "Warper.h"
#include "Controller.h"
#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2/objdetect.hpp>
Warper::Warper(cv::Mat inputImg):
m_inputImg(inputImg)

{
}

Controller::ProcessError  Warper::getOriginalImg(std::string stored_path)
{
    

    if (m_inputImg.empty())
    {
        return Controller::ProcessError::eCantOpenInputImage;
    }
    cv::QRCodeDetector qrDecoder = cv::QRCodeDetector::QRCodeDetector();

    std::string data = qrDecoder.detectAndDecode(m_inputImg, src);
    
    if (src.empty())
    {
        imshow("error", m_inputImg);
        cv::waitKey(0);
        return Controller::ProcessError::eCantFindQr;
    }
    std::cout << cv::Mat(src).t() << std::endl;

    originalImg = imread(stored_path + data + ".png", cv::IMREAD_UNCHANGED);
    

    std::string dataOriginal = qrDecoder.detectAndDecode(originalImg, srcOriginal);
    std::cout << cv::Mat(srcOriginal).t() << std::endl;
    if (dataOriginal != data)
    {
        std::cout << __FUNCSIG__ << " line : " << __LINE__ << std::endl;
        return Controller::ProcessError::еUndefined;
    }
    return Controller::ProcessError::eNo;
}


cv::Mat Warper::warp()
{
    
   // resize(m_inputImg, m_inputImg, cv::Size(m_inputImg.cols + 30, m_inputImg.rows + 30));
    cv::Mat matrix, imgWarp;
    for (int i = 0; i < 4; i++) {
        srcOriginal[i] = srcOriginal[i] + cv::Point2f(15,15);
    }
    matrix = getPerspectiveTransform(src, srcOriginal);

    warpPerspective(m_inputImg, imgWarp, matrix, m_inputImg.size());
    cv::namedWindow("warppedCropped", cv::WINDOW_FREERATIO);
    cv::namedWindow("OriginalImg", cv::WINDOW_FREERATIO);
    cv::imshow("OriginalImg", originalImg);
    cv::imshow("warppedCropped", imgWarp(cv::Rect(0, 0, originalImg.size().width, originalImg.size().height)));
    return imgWarp(cv::Rect(0, 0, originalImg.size().width+30, originalImg.size().height+30));
}
