#pragma once

#include "Vec2D.h"
#include <vector>
#include <opencv2\opencv.hpp>
#include "SendMove.h"

namespace TouhouAILogic {
	class Player {
		Vec2D point;
		SendMove move;
		bool is_recognited = false;

	public:
		Player();
		Vec2D Point();
		Vec2D MidPoint();
		void Move(Vec2D);
		void InputPoint(std::vector<cv::Rect>);
		

		bool IsRegognited() { return is_recognited; }
	};
}
