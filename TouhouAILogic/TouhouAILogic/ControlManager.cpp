#include "Stdafx.h"
#include "ControlManager.h"
#include "Debug.h"
#include <random>

using namespace TouhouAILogic;

static WindowPrint printer;
static ImageRecognition recog;
static Player player;
static cv::Mat screen_image;
static std::vector<cv::Mat> screen_planes;

void PlayerModule();
void EnemyModule();
void BulletModule();

TouhouAILogic::ControlManager::ControlManager()
{
}

void TouhouAILogic::ControlManager::Proc()
{
	GetPrintScreenModule();

	player_th = gcnew Thread(gcnew ThreadStart(PlayerModule));
	//enemy_th = gcnew Thread(gcnew ThreadStart(EnemyModule));
	bullet_th = gcnew Thread(gcnew ThreadStart(BulletModule));
	
	if(!player_th->IsAlive)
		player_th->Start();

	if(!bullet_th->IsAlive)
		bullet_th->Start();
		

	player_th->Join();
	bullet_th->Join();
	

	recog.DrawRectangle(screen_image, recog.PlayerRect(), cv::Scalar(0, 255, 0));
	recog.DrawRectangle(screen_image, recog.BulletRect(), cv::Scalar(255, 0, 255));
	
	cv::imshow("matching", screen_image);
}

void TouhouAILogic::ControlManager::GetPrintScreenModule()
{
	printer.HBITMAPToMat(screen_image);

	cv::split(screen_image, screen_planes);
}

void PlayerModule()
{
	auto p_p = player.Point();

	p_p.Set(std::max(p_p.X() - 28, 0), std::max(p_p.Y() - 36,0));

	cv::Rect roi_rect(p_p.X(),p_p.Y(), 100, 150);

	//ÉvÉåÉCÉÑÅ[íTçıîÕàÕ
	cv::rectangle(screen_image, roi_rect, cv::Scalar(0,0,0), 2, 8, 0);

	std::vector<cv::Mat> player_planes;

	for (auto x : screen_planes) {
		player_planes.push_back(x(roi_rect));
	}

	recog.PlayerRecognition(screen_image, player_planes , Vec2D(p_p.X(), p_p.Y()));
}

void EnemyModule()
{
	recog.EnemyRecognition(screen_image, screen_planes, Vec2D(0, 0));
}

void BulletModule()
{
	recog.BulletRecognition(screen_image, screen_planes, Vec2D(0, 0));
}
