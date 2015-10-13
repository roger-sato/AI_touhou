#pragma once

#include "Vec2D.h"

namespace TouhouAILogic {
	class Player {
		Vec2D point;

	public:
		Vec2D Point();
		void Move(Vec2D);
	};
}
