#pragma once

#include "Vec2D.h"
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class Bullet {
		cv::Mat& img;
		cv::Rect rect;
		cv::Point mid_point;
		Vec2D move_vec;

		const int defo_life_time = 5;

		int life_time = defo_life_time;
		
	public:
		Bullet(cv::Mat&);
		cv::Rect Rect();
		void InputRect(cv::Rect);
		void Update(bool can_reco);
		cv::Point MidPoint();

		void SetMoveVec(Vec2D);

		bool IsDead() { return life_time <= 0; }
	};
}
