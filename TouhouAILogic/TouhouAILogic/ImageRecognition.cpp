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

#include "SendMove.h"
#include "Vec2D.h"

void TemplateMatch(std::vector<cv::Mat>& planes, std::pair<std::string, cv::Mat> xy, cv::Mat& result);
void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt, std::pair<std::string, cv::Mat> xy, TouhouAILogic::Vec2D p);

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

void TouhouAILogic::ImageRecognition::PlayerRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p)
{
	std::map<std::string, cv::Mat> player_image;
	ImageData::Instance().ImageMap("player",player_image);

	player_maxpt.clear();

	for (auto xy : player_image) {
		cv::Mat result;
		
		TemplateMatch(planes, xy, result);
		SearchMatch(result, 0.65f, player_maxpt ,xy , p);
	}
}

void TouhouAILogic::ImageRecognition::BulletRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p)
{
	std::map<std::string, cv::Mat> bullet_image;
	ImageData::Instance().ImageMap("bullet",bullet_image);

	bullet_maxpt.clear();

	for (auto xy : bullet_image) {
		cv::Mat result;
		TemplateMatch(planes, xy, result);

		SearchMatch(result, 0.65f, bullet_maxpt ,xy , p);
	}


}

void TouhouAILogic::ImageRecognition::EnemyRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p)
{
	std::map<std::string, cv::Mat> enemy_image;
	ImageData::Instance().ImageMap("enemy",enemy_image);

	enemy_maxpt.clear();

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
	return bullet_maxpt;
}

void TouhouAILogic::ImageRecognition::DrawRectangle(cv::Mat& img, std::vector<cv::Rect>& maxpt , cv::Scalar color)
{
	for (auto x : maxpt) {
		cv::rectangle(img, cv::Point(x.x,x.y), cv::Point(x.x + x.width, x.y + x.height), color, 2, 8, 0);
	}
}

void TemplateMatch(std::vector<cv::Mat>& planes ,  std::pair<std::string,cv::Mat> xy, cv::Mat& result)
{
	if (xy.first[xy.first.size() - 1] == 'R') {
		cv::matchTemplate(planes[2], xy.second, result, cv::TM_CCOEFF_NORMED);
	}
	else if (xy.first[xy.first.size() - 1] == 'G') {
		cv::matchTemplate(planes[1], xy.second, result, cv::TM_CCOEFF_NORMED);
	}

	else if (xy.first[xy.first.size() - 1] == 'B') {
		cv::matchTemplate(planes[0], xy.second, result, cv::TM_CCOEFF_NORMED);
	}
}

void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Rect>& maxpt , std::pair<std::string, cv::Mat> xy ,  TouhouAILogic::Vec2D p)
{
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.emplace_back(x + p.X(), y + p.Y(), xy.second.rows, xy.second.cols);
			}
		}
	}
}