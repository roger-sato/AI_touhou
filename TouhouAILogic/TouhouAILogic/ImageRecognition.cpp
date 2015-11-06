#include "stdafx.h"
#include <Windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\nonfree\nonfree.hpp>
#include "ImageRecognition.h"
#include "PrintWindow.h"
#include <vector>
#include "ImageData.h"
#include "Bullet.h"

#include "SendMove.h"
#include "Vec2D.h"

using namespace TouhouAILogic;

void TemplateMatch(std::vector<cv::Mat>& planes, std::pair<cv::Mat, std::string> xy, cv::Mat& result);
void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt, std::pair<cv::Mat, std::string> xy, TouhouAILogic::Vec2D p);
void SearchMatch_p(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt, std::pair<cv::Mat, std::string> xy, TouhouAILogic::Vec2D p);

void TouhouAILogic::ImageRecognition::Init()
{
	ImageData::Instance().ImageMap("player", player_image);
	ImageData::Instance().ImageMap("move_player", player_image_move);

	ImageData::Instance().ImageMap("bullet", bullet_image);
}


void TouhouAILogic::ImageRecognition::PlayerRecognition(cv::Mat& img, std::vector<cv::Mat>& planes, Vec2D p)
{
	player_maxpt.clear();

	if (player_image.empty())
		return;


	for (int i = 0; i < 4; ++i) {
		auto xy = player_image_move[player_move_i];
		player_move_i = ++player_move_i % player_image_move.size();

		cv::Mat result;

		TemplateMatch(planes, xy, result);
		SearchMatch_p(result, 0.75f, player_maxpt, xy, p);
		
		if (!player_maxpt.empty())
			return;
	}


	for (int i = 0; i < 3; ++i) {
		auto xy = player_image[player_i];
		player_i = ++player_i % player_image.size();

		cv::Mat result;

		TemplateMatch(planes, xy, result);
		SearchMatch_p(result, 0.75f, player_maxpt, xy, p);

		if (!player_maxpt.empty())
			return;
	}

}

void TouhouAILogic::ImageRecognition::BulletRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p)
{
	bullet_maxpt.clear();
	bullet.clear();


	if (bullet_image.empty())
		return;

	
	for (int i = 0; i < 3; ++i) {
		auto xy = bullet_image[bullet_i];
		bullet_i = ++bullet_i % bullet_image.size();

		cv::Mat result;
		TemplateMatch(planes, xy, result);

		SearchMatch(result, 0.75f, bullet_maxpt, xy, p);

		for (auto y : bullet_maxpt) {
			Bullet b(xy);
			b.InputRect(y);

			bullet.push_back(b);
		}
	}
	
}

void TouhouAILogic::ImageRecognition::BulletRecognitionInd(cv::Mat & img, std::pair<cv::Mat, std::string>& temp, std::vector<cv::Mat>& planes, std::vector<Bullet>& bu,Vec2D p)
{
	std::vector<cv::Rect> temp_maxpt;

	cv::Mat result;
	TemplateMatch(planes, temp, result);

	SearchMatch(result, 0.75f, temp_maxpt, temp, p);

	for (auto y : temp_maxpt) {
		Bullet b(temp);
		b.InputRect(y);

		bu.push_back(b);
		bullet_maxpt.push_back(y);
	}
}


void TouhouAILogic::ImageRecognition::EnemyRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p)
{
	std::vector<std::pair<cv::Mat,std::string>> enemy_image;
	ImageData::Instance().ImageMap("enemy",enemy_image);

	enemy_maxpt.clear();


	if (enemy_image.empty())
		return;

	auto xy = enemy_image[enemy_i];
	enemy_i = ++enemy_i% enemy_image.size();


	for (auto xy : enemy_image) {
		cv::Mat result;
		TemplateMatch(planes, xy, result);

		SearchMatch(result, 0.65f, enemy_maxpt,xy , p);
	}
}


TouhouAILogic::WindowPrint screen_shot;

void TouhouAILogic::ImageRecognition::ScreenShot()
{
	screen_shot.Print();
}

void TouhouAILogic::ImageRecognition::DrawRectangle(cv::Mat& img, std::vector<cv::Rect>& maxpt , cv::Scalar color)
{
	for (auto x : maxpt) {
		cv::rectangle(img, cv::Point(x.x,x.y), cv::Point(x.x + x.width, x.y + x.height), color, 2, 8, 0);
	}
}

void TemplateMatch(std::vector<cv::Mat>& planes , std::pair<cv::Mat, std::string> xy, cv::Mat& result)
{
	if (xy.second[xy.second.size() - 1] == 'R') {
		cv::matchTemplate(planes[2], xy.first, result, cv::TM_CCOEFF_NORMED);
	}
	else if (xy.second[xy.second.size() - 1] == 'G') {
		cv::matchTemplate(planes[1], xy.first, result, cv::TM_CCOEFF_NORMED);
	}

	else if (xy.second[xy.second.size() - 1] == 'B') {
		cv::matchTemplate(planes[0], xy.first, result, cv::TM_CCOEFF_NORMED);
	}
}

void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt , std::pair<cv::Mat, std::string> xy ,  TouhouAILogic::Vec2D p)
{
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.push_back(cv::Rect(x + p.X(), y + p.Y(), xy.first.cols, xy.first.rows));
			}
		}
	}
}

//プレイヤーに最適化
void SearchMatch_p(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt, std::pair<cv::Mat, std::string> xy, TouhouAILogic::Vec2D p)
{
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.emplace_back(x + p.X(), y + p.Y(), xy.first.cols, xy.first.rows);
				return;
			}
		}
	}
}