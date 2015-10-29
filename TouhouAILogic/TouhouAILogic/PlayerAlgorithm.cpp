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

	for (auto x : bullet_rect) {
		auto p = x.MidPoint();

		cv::Point dp = cv::Point(p.x,p.y) - player_p;
		double di = std::sqrt((dp.x*dp.x + dp.y*dp.y));
		if (di == 0)
			di = 1;

		double ndpx = dp.x / di;
		double ndpy = dp.y / di;

		cv::Point dp2 = x.MoveVec();
		double di2 = std::sqrt((dp2.x*dp2.x + dp2.y*dp2.y));
		if (di2 == 0)
			di2 = 1;

		double ndpx2 = dp2.x / di2;
		double ndpy2 = dp2.y / di2;


		auto ndx = (ndpx + ndpx2);
		auto ndy = (ndpy + ndpy2);

		ndx *= (di);
		ndy *= (di);

		cv::circle(aa, player_p + cv::Point(-ndx,-ndy), std::sqrt(1000), cv::Scalar(0, 0, 255),10);

		if (ndx*ndx + ndy*ndy > 1000) {
			continue;
		}

		auto s = cv::Point(dp.y,-dp.x);

		to_v += s;
	}

	if (to_v.x == 0 && to_v.y == 0) {
		cv::Point defp(357, 754);
		auto ss = defp - player_p;

		cv::circle(aa, defp, std::sqrt(10000), cv::Scalar(0, 255, 255),5);

		if (ss.x*ss.x + ss.y*ss.y > 10000) {
			to_v += ss;
		}

	}
	cv::line(aa, player_p, player_p + to_v, cv::Scalar(0, 255, 255), 10);
	player.Move(Vec2D(to_v.x, to_v.y));
	//send_move.MovePlayer(Vec2D(1, 1));
	send_move.Update();
}
