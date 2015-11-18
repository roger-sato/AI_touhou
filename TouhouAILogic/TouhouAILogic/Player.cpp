#include "Stdafx.h"
#include "Player.h"
#include <algorithm>

TouhouAILogic::Player::Player()
{
	point.Set(357,754);
}

TouhouAILogic::Vec2D TouhouAILogic::Player::Point()
{
	return point;
}

TouhouAILogic::Vec2D TouhouAILogic::Player::MidPoint()
{
	return Vec2D(point.X() + 10,point.Y() + 20);
}

void TouhouAILogic::Player::Move(Vec2D v)
{
	int k = 5;
	if (v.X() > 0) {
		if (v.Y() > 0) {
			v = Vec2D(1 * k, 1 * k);
		}
		else if (v.Y() < 0) {
			v = Vec2D(1 * k, -1 * k);
		}
	}
	else if(v.X() < 0) {
		if (v.Y() > 0) {
			v = Vec2D(-1 * k, 1 * k);
		}
		else if (v.Y() < 0) {
			v = Vec2D(-1 * k, -1 * k);
		}
	}

	point.Add(v);
	move.MovePlayer(v);
}

void TouhouAILogic::Player::InputPoint(std::vector<cv::Rect> input)
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
	point.Set((max_x+min_x)/2, (max_y + min_y) / 2);
}
