#pragma once

#include "Vec2D.h"
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	class Bullet {
		std::pair<cv::Mat, std::string> img;
		cv::Rect rect;
		cv::Point mid_point;
		Vec2D move_vec;

		const int defo_life_time = 5;

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

		void SetMoveVec(Vec2D);

		bool IsDead() { return life_time <= 0; }

		Bullet& operator=(const Bullet& b)
		{
			//img = b.Image();
			//rect = b.Rect();
			//mid_point = b.MidPoint();
			//life_time = b.LifeTime();
			return *this;
		}
		
		bool operator==(Bullet b) 
		{
			
			if (b.Rect().width == Rect().width && b.Rect().height == Rect().height) {
				auto dx = (b.Rect().x - Rect().x); 
				auto dy = (b.Rect().y - Rect().y);
				if (dx*dx > 5 && dy * dy > 5) {
					return true;
				}
			}

			return false;
			
		}

		bool operator<(Bullet b)
		{
			return Rect().x < b.Rect().x;
		}

	};
}
