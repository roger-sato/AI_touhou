#pragma once

#include "Vec2D.h"
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class Bullet {
		std::pair<cv::Mat, std::string> img;
		cv::Rect rect;
		cv::Point mid_point;
		cv::Point move_vec;
		std::string identify;
		std::string hash;

		const int defo_life_time  = 1;

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
		
		std::string GetHash() { return hash; }
		void SetHash(std::string h) { hash = h; }

		void SetMoveVec(cv::Point);
		cv::Point MoveVec();

		bool IsDead() { return life_time < 0; }


	};
}
