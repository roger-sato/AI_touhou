#pragma once

#include "Vec2D.h"
#include <vector>
#include <opencv2\opencv.hpp>
#include "SendMove.h"

namespace TouhouAILogic {
	class Player {
		Vec2D point;
		SendMove move;
	public:
		Vec2D Point();
		void Move(Vec2D);
		void InputPoint(std::vector<cv::Point>);
	};
}
