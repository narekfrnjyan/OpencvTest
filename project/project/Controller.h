#pragma once
#include <iostream>
class Controller
{
public:
	enum ProcessError
	{
		eNo,
		eCantOpenInputImage,
		eCantFindQr,
		еUndefined
	};
public:
	Controller(const std::string& inputImgPath = "", const std::string& storedDataPath = "");
	void setInputImagePath(const std::string& inputImgPath);

	ProcessError startProcess();

private:
	std::string m_inputImagePath;
	std::string m_storedDataPath;
};

