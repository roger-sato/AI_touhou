#pragma once

#include <opencv2\opencv.hpp>


namespace TouhouAILogic {
	class Vec2D {
		int x, y;

	public:
		int X();
		int Y();
		int ToLength(Vec2D);
		void Set(Vec2D);
		void Set(int x, int y);
		void Set(cv::Rect);
		void Add(int x, int y);
		void Add(Vec2D);
	};
}