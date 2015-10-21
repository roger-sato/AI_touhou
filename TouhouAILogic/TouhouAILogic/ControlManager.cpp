#include "Stdafx.h"
#include "ControlManager.h"
#include <random>

using namespace System::Threading;

void TouhouAILogic::ControlManager::Proc()
{
	System::Console::Write("aaaaa");
	Thread^ threadA = gcnew Thread(gcnew ThreadStart(PlayerModule));
}

void TouhouAILogic::ControlManager::GetPrintScreenModule()
{
	printer.HBITMAPToMat(screen_image);

	cv::split(screen_image, screen_planes);
}

void TouhouAILogic::ControlManager::PlayerModule()
{
	recog.PlayerRecognition(screen_image, screen_planes , Vec2D(0, 0));
}

void TouhouAILogic::ControlManager::EnemyModule()
{
	recog.EnemyRecognition(screen_image, screen_planes, Vec2D(0, 0));
}

void TouhouAILogic::ControlManager::BulletModule()
{
	recog.BulletRecognition(screen_image, screen_planes, Vec2D(0, 0));
}

