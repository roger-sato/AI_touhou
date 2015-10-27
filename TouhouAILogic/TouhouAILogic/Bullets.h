#pragma once

#include <list>
#include <opencv2\opencv.hpp>
#include "Bullet.h"


namespace TouhouAILogic {

	class Bullets {
		std::vector<Bullet> bullets;
	public:
		Bullets();

		std::vector<Bullet> OutRecoBullets();
		void InputRecoBullets(std::vector<Bullet>&);
		void ClearBullets();
	};
}
