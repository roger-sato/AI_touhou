#pragma once
#include "Player.h"
#include "ImageRecognition.h"
#include "PrintWindow.h"

namespace TouhouAILogic {

	ref class ControlManager {

	public:
		ControlManager() {}
		void Proc();

	private:
		void GetPrintScreenModule();
	};

}