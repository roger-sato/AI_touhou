#pragma once

#include <vector>

namespace TouhouAILogic {

	using namespace System::Threading;

	class Player;

	ref class ImageRecognitionMgr {
		Thread^ player_th;

	public:
		ImageRecognitionMgr();

		void Init();

		void Recognition(cv::Mat& screen_image , Player& player);
		void PlayerRect(std::vector<cv::Rect>&);
		void EnemyRect(std::vector<cv::Rect>&);
		void BulletRect(std::vector<cv::Rect>&);
		void Bullets(std::vector<Bullet>&);

	};

}
