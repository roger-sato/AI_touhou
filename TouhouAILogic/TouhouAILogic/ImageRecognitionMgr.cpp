#include "Stdafx.h"
#include "ImageRecognition.h"
#include "ImageRecognitionMgr.h"
#include "ImageData.h"
#include "Player.h"
#include "Debug.h"

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
static cv::Mat screen_image;
static ImageRecognition recog;
static std::vector<cv::Mat> screen_planes;
static Player player;

static void PlayerRecognition();
//static void EnemyRecognition();
static void BulletRecognition(System::Object^ s);

ref struct State
{
	Player& player; //最初の整数
	Mutex^ mtx; //ロック用のハンドル
	int n;

	State(int _n ,Player& _player, Mutex^ _mtx)
		: player(_player), mtx(_mtx), n(_n){}
};

TouhouAILogic::ImageRecognitionMgr::ImageRecognitionMgr()
{
}

void TouhouAILogic::ImageRecognitionMgr::Init()
{
	ImageData::Instance().ImageMap("player", player_image);
	ImageData::Instance().ImageMap("move_player", player_image_move);
	ImageData::Instance().ImageMap("bullet", bullet_image);

	recog.Init();
}

void TouhouAILogic::ImageRecognitionMgr::Recognition(cv::Mat& screen ,Player& _player)
{
	player = _player;

	player_th = gcnew Thread(gcnew ThreadStart(PlayerRecognition));
	
	screen_image = screen;

	BulletThreadSet();

	screen_planes.clear();
	cv::split(screen_image, screen_planes);
	
	if (!player_th->IsAlive) {
		player_th->Start();
	}

	BulletThreadStart(screen,player);

	BulletThreadJoin();
	player_th->Join();

	recog.DrawRectangle(screen,bullet_rect, cv::Scalar(0, 255, 0));
	
}

static void BulletRecognition(System::Object^ s)
{
	
	State^ state = dynamic_cast<State^>(s); //キャストが必要

	std::vector<Bullet> b;

	state->mtx->WaitOne();
	auto img = bullet_image[state->n - 1];
	state->mtx->ReleaseMutex();

	recog.BulletRecognitionInd(screen_image, img , bullet_planes, b, Vec2D(bullet_search_rect.x, bullet_search_rect.y));
	
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

void TouhouAILogic::ImageRecognitionMgr::BulletThreadSet()
{
	bullet_th1 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	
	bullet_th2 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	bullet_th3 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	bullet_th4 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	bullet_th5 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	bullet_th6 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	bullet_th7 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	bullet_th8 = gcnew Thread(gcnew ParameterizedThreadStart(BulletRecognition));
	
}

static int player_count = 20;

void PlayerRecognition()
{
	auto p_p = player.Point();

	const int h = 200;
	const int w = 200;

	p_p.Set(std::max(p_p.X() - (w / 2 - 20), 0), std::max(p_p.Y() - h / 2, 0));
	p_p.Set(std::min(p_p.X(), screen_image.cols - w), std::min(p_p.Y(), screen_image.rows - h));

	cv::Rect roi_rect(p_p.X(), p_p.Y(), w, h);

	//プレイヤー探索範囲
	cv::rectangle(screen_image, roi_rect, cv::Scalar(0, 0, 0), 2, 8, 0);

	std::vector<cv::Mat> player_planes;

	for (auto x : screen_planes) {
		player_planes.push_back(x(roi_rect));
	}


	recog.PlayerRecognition(screen_image, player_planes, player_rect, Vec2D(p_p.X(), p_p.Y()));

	if (!player_rect.empty()) {
		cv::rectangle(screen_image, player_rect[0], cv::Scalar(255, 0, 0), 2, 8, 0);
	}

	if (player_rect.empty()) {
		if (--player_count < 0) {
			player_rect.push_back(cv::Rect(357, 754, 14, 44));
		}
	}
	else {
		player_count = 20;
	}

}

void TouhouAILogic::ImageRecognitionMgr::BulletThreadStart(cv::Mat& screen_image,Player& player)
{
	Mutex^ mtx = gcnew Mutex;

	const int hai = 300;
	const int wid = 300;

	auto p_p = player.Point();
	p_p.Set(std::max(p_p.X() - (wid / 2 - 20), 0), std::max(p_p.Y() - (hai * 3 / 4), 0));

	bullet_search_rect = cv::Rect(p_p.X(), p_p.Y(), std::min(screen_image.cols - p_p.X(), wid), std::min(screen_image.rows - p_p.Y(), hai));

	cv::rectangle(screen_image, bullet_search_rect, cv::Scalar(0, 0, 255), 2, 8, 0);


	bullet_planes.clear();
	bullets.clear();
	bullet_rect.clear();


	for (auto x : screen_planes) {
		bullet_planes.push_back(x(bullet_search_rect));
	}


	bullet_th1->Start(gcnew State(1,player, mtx));
	
	bullet_th2->Start(gcnew State(2,player, mtx));
	bullet_th3->Start(gcnew State(3,player, mtx));
	bullet_th4->Start(gcnew State(4,player, mtx));
	bullet_th5->Start(gcnew State(5,player, mtx));
	bullet_th6->Start(gcnew State(6,player, mtx));
	bullet_th7->Start(gcnew State(7,player, mtx));
	bullet_th8->Start(gcnew State(8,player, mtx));
	
}

void TouhouAILogic::ImageRecognitionMgr::BulletThreadJoin()
{
	bullet_th1->Join();
	
	bullet_th2->Join();
	bullet_th3->Join();
	bullet_th4->Join();
	bullet_th5->Join();
	bullet_th6->Join();
	bullet_th7->Join();
	bullet_th8->Join();
	
}
