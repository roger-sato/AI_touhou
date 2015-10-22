#include "Stdafx.h"
#include "ControlManager.h"
#include <random>

using namespace System::Threading;
using namespace System;
using namespace TouhouAILogic;

static WindowPrint printer;
static ImageRecognition recog;
static Player player;
static cv::Mat screen_image;
static std::vector<cv::Mat> screen_planes;

void PlayerModule();
void EnemyModule();
void BulletModule();

bool end[3] = { true,true,true };

void TouhouAILogic::ControlManager::Proc()
{
	System::Console::Write("aaaaa");
	
	GetPrintScreenModule();

	Thread^ player_th = gcnew Thread(gcnew ThreadStart(PlayerModule));
	Thread^ enemy_th = gcnew Thread(gcnew ThreadStart(EnemyModule));
	Thread^ bullet_th = gcnew Thread(gcnew ThreadStart(BulletModule));
	
	if(end[0])
		player_th->Start();

	if(end[1])
		enemy_th->Start();

	if(end[2])
		bullet_th->Start();

	/*
	player_th->Join();
	enemy_th->Join();
	bullet_th->Join();
	*/

	if (end[0])
		recog.DrawRectangle(screen_image, recog.PlayerRect(), cv::Scalar(0, 255, 0));

	if (end[1])
		recog.DrawRectangle(screen_image, recog.EnemyRect(), cv::Scalar(0, 0, 255));

	if (end[2])
	recog.DrawRectangle(screen_image, recog.BulletRect(), cv::Scalar(255, 0, 0));
	
	cv::imshow("matching", screen_image);
}

void TouhouAILogic::ControlManager::GetPrintScreenModule()
{
	printer.HBITMAPToMat(screen_image);

	cv::split(screen_image, screen_planes);
}

void PlayerModule()
{
	end[0] = false;
	recog.PlayerRecognition(screen_image, screen_planes , Vec2D(0, 0));
	end[0] = true;
}

void EnemyModule()
{
	end[1] = false;
	recog.EnemyRecognition(screen_image, screen_planes, Vec2D(0, 0));
	end[1] = true;
}

void BulletModule()
{
	end[2] = false;
	recog.BulletRecognition(screen_image, screen_planes, Vec2D(0, 0));
	end[2] = true;
}
