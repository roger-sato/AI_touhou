#pragma once

#include <vector>
#include <opencv2\opencv.hpp>
#include "Vec2D.h"

namespace TouhouAILogic {
	public class ImageRecognition 
	{
		std::vector<cv::Point> player_maxpt;
		std::vector<cv::Point> enemy_maxpt;
		std::vector<cv::Point> bullet_maxpt;

	public:
		void Proc();
		void PlayerRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p);
		void BulletRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p);
		void EnemyRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p);

		void ScreenShot();

		std::vector<cv::Point> PlayerPoint();
		std::vector<cv::Point> EnemyPoint();
		std::vector<cv::Point> BulletPoint();
	};

}