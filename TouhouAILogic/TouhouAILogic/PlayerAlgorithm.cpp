#include "Stdafx.h"
#include "PlayerAlgorithm.h"
#include "SendMove.h"
#include "Bullet.h"
#include "Debug.h"
#include "Player.h"

using namespace TouhouAILogic;

SendMove send_move;

void TouhouAILogic::PlayerAlgorithm::PlayerUpdate(cv::Point player_p, std::list<Bullet> bullet_rect,Player& player,cv::Mat& aa)
{
	cv::Point to_v(0,0);

	int min_dd = 9999999;

	for (auto x : bullet_rect) {
		auto w = x.Image().first.rows+16;

		int kk = 2;

		cv::circle(aa, x.MidPoint() + x.MoveVec() * kk, std::sqrt(w*w), cv::Scalar(0, 0, 255), 3);

		auto bp = x.MidPoint() + x.MoveVec()*kk - player_p;

		auto dd = bp.x*bp.x + bp.y*bp.y;

		if (dd > w*w || dd > min_dd) {
			continue;
		}
		min_dd = dd;
		auto s = cv::Point(bp.y,-bp.x);

		to_v += s;
	}

	if (to_v.x == 0 && to_v.y == 0) {
		cv::Point defp(357, 754);
		auto ss = defp - player_p;

		cv::circle(aa, defp, std::sqrt(20000), cv::Scalar(0, 255, 255),5);

		if (ss.x*ss.x + ss.y*ss.y > 20000) {
			to_v += ss;
		}

	}
	cv::line(aa, player_p, player_p + to_v, cv::Scalar(0, 255, 255), 10);
	player.Move(Vec2D(to_v.x, to_v.y));
	//send_move.MovePlayer(Vec2D(1, 1));
	send_move.Update();
}
