#include "Stdafx.h"
#include "Bullets.h"
#include "Bullet.h"

using namespace TouhouAILogic;

TouhouAILogic::Bullets::Bullets()
{
}

std::list<Bullet> TouhouAILogic::Bullets::OutRecoBullets()
{
	return std::list<Bullet>();
}

void TouhouAILogic::Bullets::InputRecoBullets(std::vector<cv::Rect>)
{
}
