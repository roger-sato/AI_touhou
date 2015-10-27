#pragma once

#include <list>
#include <opencv2\opencv.hpp>
#include "Bullet.h"
#include "BulletHash.h"
#include <map>

namespace TouhouAILogic {

	class Bullets {
		std::list<Bullet> bullets;
		BulletHash bullet_hash;
	public:
		Bullets();

		std::list<Bullet> OutRecoBullets();
		void InputRecoBullets(std::vector<Bullet>);
		void ClearBullets();
	};
}
