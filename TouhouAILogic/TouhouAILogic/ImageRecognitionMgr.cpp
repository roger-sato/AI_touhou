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

static cv::Rect bullet_search_rect;

static std::vector<cv::Mat> bullet_planes;

static ImageRecognition recog;
static cv::Mat screen_image;
static std::vector<cv::Mat> screen_planes;

//static std::vector<Thread^> bullet_th;

static void PlayerRecognition();
static void EnemyRecognition();
static void BulletRecognition(System::Object^ s);

ref struct State
{
	Player& player; //最初の整数
	Mutex^ mtx; //ロック用のハンドル
	std::pair<cv::Mat,std::string>& img;

	State(Player& player, Mutex^ mtx,std::pair<cv::Mat,std::string>& img)
		: player(player), mtx(mtx),img(img) {}
};

TouhouAILogic::ImageRecognitionMgr::ImageRecognitionMgr()
{
}

void TouhouAILogic::ImageRecognitionMgr::Init()
{
	ImageData::Instance().ImageMap("player", player_image);
	ImageData::Instance().ImageMap("move_player", player_image_move);
	ImageData::Instance().ImageMap("bullet", bullet_image);

	bullet_th.reserve(bullet_image.size());
}

void TouhouAILogic::ImageRecognitionMgr::Recognition(cv::Mat& screen_image ,Player& player)
{
	
	player_th = gcnew Thread(gcnew ThreadStart(PlayerRecognition));
	
	for (int i = 0; i < bullet_th.size(); ++i) {
		bullet_th[i] = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	}

	if (!player_th->IsAlive) {
		player_th->Start();
	}

	Mutex^ mtx = gcnew Mutex;

	const int hai = 300;
	const int wid = 300;

	auto p_p = player.Point();
	p_p.Set(std::max(p_p.X() - (wid / 2 - 20), 0), std::max(p_p.Y() - (hai * 3 / 4), 0));

	bullet_search_rect = cv::Rect(p_p.X(), p_p.Y(), std::min(screen_image.cols - p_p.X(), wid), std::min(screen_image.rows - p_p.Y(), hai));

	cv::rectangle(screen_image, bullet_search_rect, cv::Scalar(0, 0, 255), 2, 8, 0);

	bullet_planes.clear();
	bullets.clear();
	bullet_planes.clear();

	for (auto x : screen_planes) {
		bullet_planes.push_back(x(bullet_search_rect));
	}
	
	/*
	for (int i = 0; i < bullet_th.size();++i) {
		if (!bullet_th[i]->IsAlive) {
			bullet_th[i]->Start(gcnew State(player,mtx,bullet_image[i]));
		}
	}
	*/
	/*
	player_th->Join();
	for (auto x : bullet_th) {
		x->Join();
	}
	recog.DrawRectangle(screen_image,bullet_rect, cv::Scalar(0, 255, 0));
	*/
}


static void BulletRecognition(System::Object^ s)
{
	State^ state = dynamic_cast<State^>(s); //キャストが必要

	std::vector<Bullet> b;

	recog.BulletRecognitionInd(screen_image, state->img, bullet_planes, b, Vec2D(bullet_search_rect.x, bullet_search_rect.y));

	state->mtx->WaitOne();
	
	for (auto x : b) {
		bullets.push_back(x);
		bullet_rect.push_back(x.Rect());
	}

	state->mtx->ReleaseMutex();

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
