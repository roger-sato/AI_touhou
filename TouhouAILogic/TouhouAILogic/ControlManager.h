#pragma once
#include "Player.h"
#include "ImageRecognition.h"
#include "PrintWindow.h"
#include "ImageRecognitionMgr.h"

using namespace System::Threading;

void BulletModule();

namespace TouhouAILogic {

	ref class ControlManager {
		ImageRecognitionMgr recogmg;

		Thread^ debug_th;

	public:
		void Init();
		ControlManager();
		void DebugSave();
		void Proc();

	private:
		void GetPrintScreenModule();
	};

}