#include "Stdafx.h"
#include "Bullets.h"
#include "Bullet.h"

using namespace TouhouAILogic;

static bool ok(true), notok(false);

TouhouAILogic::Bullets::Bullets()
{

}

std::list<Bullet> TouhouAILogic::Bullets::OutRecoBullets()
{
	return bullets;
}

std::vector<cv::Rect> TouhouAILogic::Bullets::BulletsRect()
{
	std::vector<cv::Rect> rect;

	for (auto x : bullets) {
		rect.push_back(x.Rect());
	}
	return rect;
}


static std::map<std::string, bool> table;
static std::map<std::string, cv::Rect> table2;


void TouhouAILogic::Bullets::InputRecoBullets(std::vector<Bullet> b)
{

	for (auto x : b) {
		auto hash = bullet_hash.GetHash(x.Rect());
		auto hash2 = bullet_hash.GetHash2(x.Rect());

		if (table.find(hash) != table.end()) {
			table[hash] = ok;
			continue;
		}

		if (table2.find(hash2) != table2.end()) {
			auto y = x.Rect();
			auto y2 = table2[hash2];

			cv::Point po(y.x - y2.x, y.y - y2.y);
			po = po + x.MoveVec();
			po.x /= 2;
			po.y /= 2;

			x.SetMoveVec(po);

			table2.erase(hash2);
		}

		bullets.push_back(x);
		table[hash] = ok;
		table2[hash2] = x.Rect();
	}


	for (auto x = bullets.begin(); x != bullets.end(); ++x){
		auto hash = bullet_hash.GetHash(x->Rect());

		if (table.find(hash) != table.end()) {
			if (table[hash] == ok) {
				x->Update(true);
				table[hash] = notok;
			}
			else {
				x->Update(false);
				if (x->IsDead()) {
					table.erase(hash);
					x = bullets.erase(x);
					x = std::prev(x);
				}
			}

		}
	}
	


}

void TouhouAILogic::Bullets::ClearBullets()
{
	bullets.clear();
}
