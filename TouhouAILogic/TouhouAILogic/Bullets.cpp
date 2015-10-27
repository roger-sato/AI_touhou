#include "Stdafx.h"
#include "Bullets.h"
#include "Bullet.h"
#include "Debug.h"

using namespace TouhouAILogic;

TouhouAILogic::Bullets::Bullets()
{
}

std::vector<Bullet> TouhouAILogic::Bullets::OutRecoBullets()
{
	return bullets;
}

void TouhouAILogic::Bullets::InputRecoBullets(std::vector<Bullet> b)
{
	for (auto x : b) {
		bullets.push_back(x);
	}

	for (auto x : b) {
		out << x.Rect().x << ":" << x.Rect().y << std::endl;
	}

	if (bullets.empty())return;


	std::sort(bullets.begin(), bullets.end());
	bullets.erase((std::unique(bullets.begin(),bullets.end()),bullets.end()));
}

void TouhouAILogic::Bullets::ClearBullets()
{
	bullets.clear();
}
