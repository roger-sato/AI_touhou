#include "Stdafx.h"
#include "Bullets.h"
#include "Bullet.h"

using namespace TouhouAILogic;

TouhouAILogic::Bullets::Bullets()
{
}

std::vector<Bullet> TouhouAILogic::Bullets::OutRecoBullets()
{
	return bullets;
}

void TouhouAILogic::Bullets::InputRecoBullets(std::vector<Bullet>& b)
{
	for (auto x : b) {
		bullets.push_back(x);
	}
}

void TouhouAILogic::Bullets::ClearBullets()
{
	bullets.clear();
}
