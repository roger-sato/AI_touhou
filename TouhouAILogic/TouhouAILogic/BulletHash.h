#pragma once

#include <string>
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class BulletHash {
		std::string x_table[78], y_table[91];

		std::string x_table2[39], y_table2[46];

		long long identify = 0;
	public:
		BulletHash();
		std::string GetHash(cv::Rect);
		std::string GetHash2(cv::Rect);
		std::string GetIdentify();
	};
}