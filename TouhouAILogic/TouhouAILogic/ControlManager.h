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
		cv::Mat screen_image;
		std::vector<cv::Mat> screen_planes;
		void GetPrintScreenModule();
		void PlayerModule();
		void EnemyModule();
		void BulletModule();
	};

}