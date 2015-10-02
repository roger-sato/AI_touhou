#pragma once

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

class WindowPrint {
public:
	void Print(System::IntPtr);
	cv::Mat HBITMAPToMat(System::IntPtr hw);
};