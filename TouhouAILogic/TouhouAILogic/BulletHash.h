#pragma once

#include <string>
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class BulletHash {
		std::string x_table[78], y_table[91];
	public:
		BulletHash();
		std::string GetHash(cv::Rect);
	};
}