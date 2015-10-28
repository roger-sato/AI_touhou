#pragma once

#include "Vec2D.h"
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class Bullet {
		std::pair<cv::Mat, std::string> img;
		cv::Rect rect;
		cv::Point mid_point;
		Vec2D move_vec;
		std::string identify;

		const int defo_life_time = 2;

		int life_time = defo_life_time;


	public:
		Bullet(std::pair<cv::Mat, std::string>);
		cv::Rect Rect()const;
		void InputRect(cv::Rect);
		void Update(bool can_reco);
		cv::Point MidPoint()const;
		int LifeTime()const;
		void SetPoint(cv::Point);
		std::pair<cv::Mat,std::string> Image() const;
		void SetIdentify(std::string);

		void SetMoveVec(Vec2D);

		bool IsDead() { return life_time < 0; }


	};
}
