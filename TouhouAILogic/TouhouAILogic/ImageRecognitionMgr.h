#pragma once

#include <vector>

namespace TouhouAILogic {

	using namespace System::Threading;

	class Player;

	ref class ImageRecognitionMgr {
		Thread^ bullet_th1;
		Thread^ bullet_th2;
		Thread^ bullet_th3;
		Thread^ bullet_th4;
		Thread^ bullet_th5;
		Thread^ bullet_th6;
		Thread^ bullet_th7;
		Thread^ bullet_th8;
		Thread^ bullet_th9;
		Thread^ bullet_th10;
		Thread^ bullet_th11;
		Thread^ bullet_th12;
		Thread^ bullet_th13;

		Thread^ enemy_th1;
		Thread^ enemy_th2;
		Thread^ enemy_th3;

		Thread^ player_th;

	public:
		ImageRecognitionMgr();

		void Init();

		void Recognition(cv::Mat& screen_image , Player& player);
		void PlayerRect(std::vector<cv::Rect>&);
		void EnemyRect(std::vector<cv::Rect>&);
		void BulletRect(std::vector<cv::Rect>&);
		void Bullets(std::vector<Bullet>&);

	private:
		void BulletThreadSet();
		void BulletThreadStart(cv::Mat& ,Player&);
		void BulletThreadJoin();
			

		void EnemyThreadSet();
		void EnemyThreadStart(cv::Mat&, Player&);
		void EnemyThreadJoin();

	};

}
