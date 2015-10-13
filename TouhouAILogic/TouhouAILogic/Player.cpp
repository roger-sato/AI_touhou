#include "Stdafx.h"
#include "Player.h"

TouhouAILogic::Vec2D TouhouAILogic::Player::Point()
{
	return point;
}

void TouhouAILogic::Player::Move(Vec2D v)
{
	point.Add(v);


}
