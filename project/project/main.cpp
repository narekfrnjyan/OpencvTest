#include <opencv2\imgcodecs.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <string>
#include <opencv2/objdetect.hpp>
#include "QRDetector.h"
#include "Controller.h"



int main()
{
    Controller c("TestData/TestImg5.jpg", "OriginalImages/");
    auto error = c.startProcess();
    if (error != Controller::ProcessError::eNo)
    {
        std::cout << "proccess ended with error code " << error << std::endl;
        return -1;
    }

    return 0;
   
}
