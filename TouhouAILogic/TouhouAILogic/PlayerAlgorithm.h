#pragma once

#include "opencv2\opencv.hpp"
#include "Bullet.h"

namespace TouhouAILogic {
	class PlayerAlgorithm {
	public:
		void PlayerUpdate(cv::Point player_p , std::vector<Bullet> bullet_rect);
	};
}