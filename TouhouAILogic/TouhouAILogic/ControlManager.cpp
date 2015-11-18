#include "Stdafx.h"
#include "ControlManager.h"
#include "Bullets.h"
#include "PlayerAlgorithm.h"
#include "ImageRecognitionMgr.h"

using namespace TouhouAILogic;

static WindowPrint printer;
static ImageRecognition recog;
static Player player;
static cv::Mat screen_image;
static std::vector<cv::Mat> screen_planes;
static Bullets bullets;
static PlayerAlgorithm player_alg;

static int num = 0;

bool debug = false;

void SaveScreenImage();

void TouhouAILogic::ControlManager::Init()
{
	recogmg.Init();
}

TouhouAILogic::ControlManager::ControlManager()
{
}

void TouhouAILogic::ControlManager::Proc()
{
	GetPrintScreenModule();

	recogmg.Recognition(screen_image, player);

	std::vector<cv::Rect> prect;
	recogmg.PlayerRect(prect);
	player.InputPoint(prect);

	std::vector<Bullet> bb;
	recogmg.Bullets(bb);
	bullets.InputRecoBullets(bb);

	recog.DrawRectangle(screen_image, bullets.BulletsRect(), cv::Scalar(0, 255, 0));

	auto p = player.MidPoint();

	debug_th = gcnew Thread(gcnew ThreadStart(SaveScreenImage));
	debug_th->Start();

	player_alg.PlayerUpdate(cv::Point(p.X(), p.Y()), bullets.OutRecoBullets(), player, screen_image);

	cv::imshow("matching", screen_image);

	debug_th->Join();
}

void SaveScreenImage()
{
	if (debug) {
		cv::imwrite("./Debug/debug" + std::to_string(num) + ".png", screen_image);
		num++;
	}
}

void TouhouAILogic::ControlManager::DebugSave()
{
	debug = true;
}

void TouhouAILogic::ControlManager::GetPrintScreenModule()
{
	printer.HBITMAPToMat(screen_image);

	cv::split(screen_image, screen_planes);
}


void EnemyModule()
{
	recog.EnemyRecognition(screen_image, screen_planes, Vec2D(0, 0));
}
