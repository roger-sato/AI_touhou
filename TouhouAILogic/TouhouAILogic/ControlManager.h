#pragma once
#include "Player.h"
#include "ImageRecognition.h"

namespace TouhouAILogic {

	class ControlManager {
		ImageRecognition recog;
		Player player;

	public:
		ControlManager() {}
		void Proc();
	};

}