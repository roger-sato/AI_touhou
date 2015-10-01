#include "stdafx.h"
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "ImageRecognition.h"


void TouhouAILogic::ImageRecognition::test()
{
	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);
	cv::imshow("red", redImg);
	cv::waitKey(0);
	cv::destroyAllWindows();
}
