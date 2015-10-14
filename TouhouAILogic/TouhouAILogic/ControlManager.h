#pragma once
#include "Player.h"
#include "ImageRecognition.h"
#include "PrintWindow.h"

namespace TouhouAILogic {

	class ControlManager {
		WindowPrint printer;
		ImageRecognition recog;
		Player player;

	public:
		ControlManager() {}
		void Proc();

	private:
		void PlayerModule();
	};

}