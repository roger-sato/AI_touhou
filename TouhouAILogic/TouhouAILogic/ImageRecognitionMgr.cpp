#include "Stdafx.h"
#include "ImageRecognition.h"
#include "ImageRecognitionMgr.h"
#include "ImageData.h"
#include "Player.h"

using namespace System::Threading;
using namespace TouhouAILogic;

static std::vector<cv::Rect> player_rect;
static std::vector<cv::Rect> enemy_rect;
static std::vector<cv::Rect> bullet_rect;
static std::vector<Bullet> bullets;

static std::vector<std::pair<cv::Mat, std::string>> player_image;
static std::vector<std::pair<cv::Mat, std::string>> player_image_move;
static std::vector<std::pair<cv::Mat, std::string>> bullet_image;

static ImageRecognition recog;
static cv::Mat screen_image;
static std::vector<cv::Mat> screen_planes;

static std::vector<Thread^> enemy_th;
static std::vector<Thread^> bullet_th;

static void PlayerRecognition();
static void EnemyRecognition();
static void BulletRecognition(System::Object^ s);

TouhouAILogic::ImageRecognitionMgr::ImageRecognitionMgr()
{
	throw gcnew System::NotImplementedException();
}

void TouhouAILogic::ImageRecognitionMgr::Init()
{
	ImageData::Instance().ImageMap("player", player_image);
	ImageData::Instance().ImageMap("move_player", player_image_move);
	ImageData::Instance().ImageMap("bullet", bullet_image);
}

void TouhouAILogic::ImageRecognitionMgr::Recognition(cv::Mat& screen_image ,Player& player)
{

	player_th = gcnew Thread(gcnew ThreadStart(PlayerRecognition));

	for (auto x : bullet_image) {
		bullet_th.push_back(gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition)));
	}

	if (!player_th->IsAlive) {
		player_th->Start();
	}

	for (int i = 0; i < bullet_th.size();++i) {
		if (!bullet_th[i]->IsAlive) {
			bullet_th[i]->Start();
		}
	}

	player_th->Join();
	for (auto x : bullet_th) {
		x->Join();
	}
}


static void BulletRecognition(System::Object^ s) {

}

void TouhouAILogic::ImageRecognitionMgr::PlayerRect(std::vector<cv::Rect>& p)
{
	p = player_rect;
}

void TouhouAILogic::ImageRecognitionMgr::EnemyRect(std::vector<cv::Rect>& e)
{
	e = enemy_rect;
}

void TouhouAILogic::ImageRecognitionMgr::BulletRect(std::vector<cv::Rect>& b)
{
	b = bullet_rect;
}

void TouhouAILogic::ImageRecognitionMgr::Bullets(std::vector<Bullet>& b)
{
	b = bullets;
}
