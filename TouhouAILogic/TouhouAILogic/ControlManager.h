#pragma once
#include "Player.h"
#include "ImageRecognition.h"
#include "PrintWindow.h"
#include "ImageRecognitionMgr.h"

using namespace System::Threading;

void PlayerModule();
void EnemyModule();
void BulletModule();

namespace TouhouAILogic {

	ref class ControlManager {
		ImageRecognitionMgr recogmg;

		Thread^ player_th;
		Thread^ enemy_th;
		Thread^ bullet_th;

	public:
		void Init();
		ControlManager();
		void Proc();

	private:
		void GetPrintScreenModule();
	};

}