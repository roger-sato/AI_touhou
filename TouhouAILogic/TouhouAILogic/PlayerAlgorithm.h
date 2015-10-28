#pragma once

#include "opencv2\opencv.hpp"
#include "Bullet.h"
#include "Player.h"

namespace TouhouAILogic {
	class PlayerAlgorithm {
	public:
		void PlayerUpdate(cv::Point player_p , std::list<Bullet> bullet_rect,Player& pla);
	};
}