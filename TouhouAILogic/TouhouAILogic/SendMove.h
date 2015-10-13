#pragma once

#include "Vec2D.h"

namespace TouhouAILogic {
	class SendMove {
		bool MoveState[4];
	public:
		void MovePlayer(Vec2D dif);
	};
}