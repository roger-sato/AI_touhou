#pragma once

#include <list>
#include <opencv2\opencv.hpp>
#include "Bullet.h"


namespace TouhouAILogic {

	class Bullets {

	public:
		Bullets();

		std::list<Bullet> OutRecoBullets();
		void InputRecoBullets(std::list<Bullet>);

	};
}
