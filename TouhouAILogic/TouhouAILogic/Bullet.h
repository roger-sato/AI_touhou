#pragma once

#include "Vec2D.h"
#include <vector>
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class Bullet {
		std::vector<cv::Rect> points;
		bool is_recognited = false;

	public:
		Bullet();
		std::vector<cv::Rect> Points();
		void InputPoint(std::vector<cv::Rect>);

		bool IsRegognited() { return is_recognited; }
	};
}
