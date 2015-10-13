#pragma once

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>

namespace TouhouAILogic {
	public ref class  WindowPrint {
		int num = 0;
	public:
		void Print();
		cv::Mat HBITMAPToMat();
	};

}