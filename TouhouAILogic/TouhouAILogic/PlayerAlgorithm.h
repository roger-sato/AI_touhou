#pragma once

#include "opencv2\opencv.hpp"

namespace TouhouAILogic {
	class PlayerAlgorithm {
	public:
		void PlayerUpdate(cv::Point player_p , std::vector<cv::Rect> bullet_rect);
	};
}