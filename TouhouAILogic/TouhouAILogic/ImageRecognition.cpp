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

void TemplateMatch(const std::vector<cv::Mat>& planes, std::pair<std::string, cv::Mat> xy, cv::Mat& result);
void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Point>& maxpt);


void TouhouAILogic::ImageRecognition::test()
{
	WindowPrint wp;
	
	cv::Mat img = wp.HBITMAPToMat();
	
	std::map<std::string, cv::Mat> bullet_image = ImageData::Instance().ImageMap("bullet");
	std::map<std::string, cv::Mat> enemy_image = ImageData::Instance().ImageMap("enemy");
	std::map<std::string, cv::Mat> player_image = ImageData::Instance().ImageMap("player");

	std::vector<cv::Mat> planes;

	cv::split(img, planes);
	
	for (auto xy : bullet_image) {
		cv::Mat result;
		TemplateMatch(planes, xy, result);
		
		SearchMatch(result, 0.65f, bullet_maxpt);

		for (auto x : bullet_maxpt) {
			cv::rectangle(img, x, cv::Point(x.x + xy.second.cols, x.y + xy.second.rows), cv::Scalar(0, 255, 255), 2, 8, 0);
		}
	}

	for (auto xy : enemy_image) {
		cv::Mat result;
		TemplateMatch(planes, xy, result);

		SearchMatch(result, 0.65f, enemy_maxpt);

		for (auto x : enemy_maxpt) {
			cv::rectangle(img, x, cv::Point(x.x + xy.second.cols, x.y + xy.second.rows), cv::Scalar(0, 0, 255), 2, 8, 0);
		}
	}

	for (auto xy : player_image) {
		cv::Mat result;
		TemplateMatch(planes, xy, result);

		SearchMatch(result, 0.65f, player_maxpt);

		for (auto x : player_maxpt) {
			cv::rectangle(img, x, cv::Point(x.x + xy.second.cols, x.y + xy.second.rows), cv::Scalar(255, 0, 0), 2, 8, 0);
		}
	}

	cv::imshow("matching", img);
}


TouhouAILogic::WindowPrint screen_shot;
void TouhouAILogic::ImageRecognition::ScreenShot()
{
	screen_shot.Print();
}

std::vector<cv::Point> TouhouAILogic::ImageRecognition::PlayerPoint()
{
	return player_maxpt;
}

std::vector<cv::Point> TouhouAILogic::ImageRecognition::EnemyPoint()
{
	return enemy_maxpt;
}

std::vector<cv::Point> TouhouAILogic::ImageRecognition::BulletPoint()
{
	return bullet_maxpt;
}



void TemplateMatch(const std::vector<cv::Mat>& planes ,  std::pair<std::string,cv::Mat> xy, cv::Mat& result)
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

void SearchMatch(const cv::Mat& result, float threshold, std::vector<cv::Point>& maxpt)
{
	for (int y = 0; y < result.rows; ++y) {
		for (int x = 0; x < result.cols; ++x) {
			if (result.at<float>(y, x) > threshold) {
				maxpt.emplace_back(x, y);
			}
		}
	}
}