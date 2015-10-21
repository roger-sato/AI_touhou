#pragma once

#include <vector>
#include <opencv2\opencv.hpp>
#include "Vec2D.h"

namespace TouhouAILogic {
	public class ImageRecognition 
	{
		std::vector<cv::Rect> player_maxpt;
		std::vector<cv::Rect> enemy_maxpt;
		std::vector<cv::Rect> bullet_maxpt;

	public:
		void Proc();
		void PlayerRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p);
		void BulletRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p);
		void EnemyRecognition(cv::Mat& img, std::vector<cv::Mat>& planes , Vec2D p);
		void DrawRectangle(cv::Mat& img, std::vector<cv::Rect>& maxpt, cv::Scalar color);
		void ScreenShot();

		std::vector<cv::Rect> PlayerRect();
		std::vector<cv::Rect> EnemyRect();
		std::vector<cv::Rect> BulletRect();
	};

}