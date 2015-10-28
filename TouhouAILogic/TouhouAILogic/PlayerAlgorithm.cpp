#include "Stdafx.h"
#include "PlayerAlgorithm.h"
#include "SendMove.h"
#include "Bullet.h"
#include "Debug.h"
#include "Player.h"

using namespace TouhouAILogic;

SendMove send_move;

void TouhouAILogic::PlayerAlgorithm::PlayerUpdate(cv::Point player_p, std::list<Bullet> bullet_rect,Player& player)
{
	cv::Point to_v(0,0);

	for (auto x : bullet_rect) {
		auto p = x.Rect();

		cv::Point dp = cv::Point(p.x,p.y) - player_p;
		double di = (dp.x*dp.x + dp.y*dp.y);
		if (di == 0)
			di = 1;

		double ndpx=0;
		double ndpy=0;

		if (dp.x > 0) {
			ndpx = dp.x*dp.x / di;
		}
		else {
			ndpx = -(dp.x*dp.x / di);
		}
		if (dp.y > 0) {
			ndpy = dp.y*dp.y / di;
		}
		else {
			ndpy = -(dp.y*dp.y / di);
		}

		cv::Point dp2 = x.MoveVec();
		double di2 = (dp2.x*dp2.x + dp2.y*dp2.y);
		if (di2 == 0)
			di2 = 1;

		double ndpx2=0;
		double ndpy2=0;

		if (dp2.x > 0) {
			ndpx2 = dp2.x*dp2.x / di2;
		}
		else {
			ndpx2 = -(dp2.x*dp2.x / di2);
		}
		if (dp2.y > 0) {
			ndpy2 = dp2.y*dp2.y / di;
		}
		else {
			ndpy2 = -(dp2.y*dp2.y / di);
		}

		auto ndx = (ndpx + ndpx2);
		auto ndy = (ndpy + ndpy2);

		ndx *= (di/1000);
		ndy *= (di/1000);

		out << ndx<< "::" << ndy << "::::::::::::::::" << std::endl;
		out << ndx*ndx + ndy*ndy << "::" << ndpy << "::" << di << std::endl << std::endl;


		if (ndx*ndx + ndy*ndy > 10000) {
			continue;
		}

		auto s = cv::Point(1,0);


		//s.x /= di;
		//s.y /= di;
		to_v += s;
	}
	player.Move(Vec2D(to_v.x, to_v.y));
	//send_move.MovePlayer(Vec2D(1, 1));
	send_move.Update();
}
