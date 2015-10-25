#include "Stdafx.h"
#include "Bullet.h"
#include <algorithm>

TouhouAILogic::Bullet::Bullet()
{
}

std::vector<cv::Rect> TouhouAILogic::Bullet::Points()
{
	return points;
}


void TouhouAILogic::Bullet::InputPoint(std::vector<cv::Rect> input)
{
	if (input.empty())
		return;

	int max_x = -99999;
	int max_y = -99999;

	int min_x = 99999;
	int min_y = 99999;

	for (auto in : input) {
		max_x = std::max(in.x, max_x);
		max_y = std::max(in.y, max_y);
		min_x = std::min(in.x, min_x);
		min_y = std::min(in.y, min_y);
	}
	is_recognited = true;
	//point.Set((max_x + min_x) / 2, (max_y + min_y) / 2);
}
