#include "Stdafx.h"
#include "ControlManager.h"
#include <random>

std::random_device random;
std::mt19937 mt(random());

void TouhouAILogic::ControlManager::Proc()
{

	std::vector<cv::Point> bullet_p = recog.BulletPoint();

	Vec2D minp(0,0);
	int minl = 999999;

	PlayerModule();

	/*
	Vec2D player_p = player.Point();

	for (auto bullet : bullet_p) {
		Vec2D vec(bullet);

		if (vec.ToLength(player_p) < minl) {
			minp = vec;
		}
	}

	if (!bullet_p.empty()) {
		if (mt() % 10 == 0) {
			Vec2D priority(-player_p.Y() + minp.Y(), -player_p.X() + minp.X());
			player.Move(priority);
		}
		else {
			Vec2D priority(player_p.Y() - minp.Y(), player_p.X() - minp.X());
			player.Move(priority);
		}
	}
	else {
		player.Move(minp);
	}
	*/
}

void TouhouAILogic::ControlManager::PlayerModule()
{
	cv::Mat img;
	printer.HBITMAPToMat(img);

	std::vector<cv::Mat> planes;

	cv::split(img, planes);

	recog.PlayerRecognition(img, planes , Vec2D(0, 0));

	cv::imshow("matching", img);

	player.InputPoint(recog.PlayerPoint());
}
