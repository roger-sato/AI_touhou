#pragma once

#include <vector>
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	public class ImageRecognition 
	{
	public:
		void test();
		void TemplateMatch();
		std::vector<cv::Point> Mach();
	};

}