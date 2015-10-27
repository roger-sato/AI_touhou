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


static std::map<std::string, bool> table;

void TouhouAILogic::Bullets::InputRecoBullets(std::vector<Bullet> b)
{

	for (auto x : b) {
		auto hash = bullet_hash.GetHash(x.Rect());

		if (table.find(hash) != table.end()) {
			table[hash] = ok;
			continue;
		}

		bullets.push_back(x);
		table[hash] = ok;
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
