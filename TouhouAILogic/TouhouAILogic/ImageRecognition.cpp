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

void TouhouAILogic::ImageRecognition::Proc()
{
	WindowPrint wp;
	
	cv::Mat img;
	wp.HBITMAPToMat(img);

	std::vector<cv::Mat> planes;

	cv::split(img, planes);
	
	EnemyRecognition(img,planes , Vec2D(0,0));
	BulletRecognition(img, planes, Vec2D(0, 0));
	PlayerRecognition(img, planes, Vec2D(0, 0));


	cv::imshow("matching", img);
}

void TouhouAILogic::ImageRecognition::PlayerRecognition(cv::Mat& img, std::vector<cv::Mat>& planes, Vec2D p)
{
	std::vector<std::pair<cv::Mat, std::string>> player_image;
	std::vector<std::pair<cv::Mat, std::string>> player_image_move;
	ImageData::Instance().ImageMap("player", player_image);
	ImageData::Instance().ImageMap("move_player", player_image_move);

	player_maxpt.clear();

	if (player_image.empty())
		return;


	for (int i = 0; i < 3; ++i) {
		auto xy = player_image_move[player_move_i];
		player_move_i = ++player_move_i % player_image_move.size();

		cv::Mat result;

		TemplateMatch(planes, xy, result);
		SearchMatch_p(result, 0.65f, player_maxpt, xy, p);
		
		if (!player_maxpt.empty())
			return;
	}


	for (int i = 0; i < 2; ++i) {
		auto xy = player_image[player_i];
		player_i = ++player_i % player_image.size();

		cv::Mat result;

		TemplateMatch(planes, xy, result);
		SearchMatch_p(result, 0.65f, player_maxpt, xy, p);

		if (!player_maxpt.empty())
			return;
	}

}

void TouhouAILogic::ImageRecognition::BulletRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p)
{
	std::vector<std::pair<cv::Mat, std::string>> bullet_image;
	ImageData::Instance().ImageMap("bullet",bullet_image);

	bullet_maxpt.clear();


	if (bullet_image.empty())
		return;

	auto xy = bullet_image[bullet_i];
	bullet_i = ++bullet_i % bullet_image.size();


	std::vector<cv::Rect> tbullet_maxpt;

	for (auto xy : bullet_image) {
		cv::Mat result;
		TemplateMatch(planes, xy, result);

		SearchMatch(result, 0.65f, tbullet_maxpt ,xy , p);

		for (auto y : tbullet_maxpt) {
			Bullet b(xy.first);
			b.InputRect(y);

			bullet_maxpt.push_back(b);
		}
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

std::vector<cv::Rect> TouhouAILogic::ImageRecognition::PlayerRect()
{
	return player_maxpt;
}

std::vector<cv::Rect> TouhouAILogic::ImageRecognition::EnemyRect()
{
	return enemy_maxpt;
}

std::vector<cv::Rect> TouhouAILogic::ImageRecognition::BulletRect()
{
	std::vector<cv::Rect> temp_maxpt;

	for (auto x : bullet_maxpt) {

	}
}

std::vector<Bullet> TouhouAILogic::ImageRecognition::Bullets()
{
	return bullet_maxpt;
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
				maxpt.emplace_back(x + p.X(), y + p.Y(), xy.first.cols, xy.first.rows);
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