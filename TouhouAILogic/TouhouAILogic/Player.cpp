#include "Stdafx.h"
#include "Player.h"
#include <algorithm>

TouhouAILogic::Vec2D TouhouAILogic::Player::Point()
{
	return point;
}

void TouhouAILogic::Player::Move(Vec2D v)
{
	point.Add(v);
	move.MovePlayer(v);
}

void TouhouAILogic::Player::InputPoint(std::vector<cv::Point> input)
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
	point.Set((max_x+min_x)/2, (max_y + min_y) / 2);
}
