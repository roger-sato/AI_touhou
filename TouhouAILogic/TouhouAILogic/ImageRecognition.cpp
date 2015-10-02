#include "stdafx.h"
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "ImageRecognition.h"
#include "PrintWindow.h"


void TouhouAILogic::ImageRecognition::test(System::IntPtr hw)
{
	WindowPrint wp;
	cv::Mat img = wp.HBITMAPToMat(hw);
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);
	cv::imshow("red", img);
	cv::waitKey(0);
	cv::destroyAllWindows();
}
