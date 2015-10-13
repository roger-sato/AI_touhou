#pragma once

#include <vector>
#include <opencv2\opencv.hpp>

namespace TouhouAILogic {
	public class ImageRecognition 
	{
		std::vector<cv::Point> player_maxpt;
		std::vector<cv::Point> enemy_maxpt;
		std::vector<cv::Point> bullet_maxpt;
	public:
		void test();
		std::vector<cv::Point> Mach();

		std::vector<cv::Point> PlayerPoint();
		std::vector<cv::Point> EnemyPoint();
		std::vector<cv::Point> BulletPoint();
	};

}