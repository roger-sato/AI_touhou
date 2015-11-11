#include "Stdafx.h"
#include "PlayerAlgorithm.h"
#include "SendMove.h"
#include "Bullet.h"
#include "Player.h"

using namespace TouhouAILogic;

SendMove send_move;


void Algorithm1(cv::Point player_p, std::list<Bullet> bullet_rect, Player& player, cv::Mat& screen_image);
void Algorithm2(cv::Point player_p, std::list<Bullet>& bullet_rect, Player& player, cv::Mat& screen_image);

void TouhouAILogic::PlayerAlgorithm::PlayerUpdate(cv::Point player_p, std::list<Bullet>& bullet_rect,Player& player,cv::Mat& screen_image)
{
	Algorithm2(player_p,bullet_rect,player,screen_image);
}

void Algorithm1(cv::Point player_p, std::list<Bullet> bullet_rect, Player& player, cv::Mat& screen_image) {

	cv::Point to_v(0, 0);

	int min_dd = 9999999;

	for (auto x : bullet_rect) {
		auto w = x.Image().first.rows + 16;

		int kk = 2;

		cv::circle(screen_image, x.MidPoint() + x.MoveVec() * kk, std::sqrt(w*w), cv::Scalar(0, 0, 255), 3);

		auto bp = x.MidPoint() + x.MoveVec()*kk - player_p;

		auto dd = bp.x*bp.x + bp.y*bp.y;

		if (dd > w*w || dd > min_dd) {
			continue;
		}
		min_dd = dd;
		auto s = cv::Point(bp.y, -bp.x);

		to_v += s;
	}

	if (to_v.x == 0 && to_v.y == 0 && bullet_rect.size() == 0) {
		cv::Point defp(357, 754);
		auto ss = defp - player_p;

		cv::circle(screen_image, defp, std::sqrt(20000), cv::Scalar(0, 255, 255), 5);

		if (ss.x*ss.x + ss.y*ss.y > 20000) {
			to_v += ss;
		}

	}
	cv::line(screen_image, player_p, player_p + to_v, cv::Scalar(0, 255, 255), 10);
	player.Move(Vec2D(to_v.x, to_v.y));
	//send_move.MovePlayer(Vec2D(1, 1));
	send_move.Update();
}


static int seach_table[4][4] = { 0 };

void SetTable(cv::Point player_p, std::list<Bullet>& bullet_rect, int s = 70)
{
	memset(seach_table,0,sizeof(seach_table));

	for (auto x : bullet_rect) {
		auto dv = x.MidPoint() - player_p;

		int t = 2 * s;

		if (-t < dv.x && -t < dv.y && dv.x < t && dv.y < t) {
			seach_table[(dv.x + (t - 1)) / s][(dv.y + (t - 1)) / s] += 3;

			int k = 3;

			auto dvt = dv + k * x.MoveVec();


			if (-t < dvt.x && -t < dvt.y && dvt.x < t && dvt.y < t) {
				seach_table[(dvt.x + (t - 1)) / s][(dvt.y + (t - 1)) / s] += 1;
			}
		}
	}
}

cv::Point ToVect()
{
	cv::Point to_v(0, 0);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			to_v.x += (i - 2) < 0 ? seach_table[i][j] : -seach_table[i][j];
			to_v.y += (j - 2) < 0 ? seach_table[i][j] : -seach_table[i][j];
		}
	}

	return to_v;
}

void Algorithm2(cv::Point player_p, std::list<Bullet>& bullet_rect, Player& player, cv::Mat& screen_image) {


	int s = 50;
	
	SetTable(player_p,bullet_rect,s);

	cv::Rect table_rect[4][4];

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			auto rx = player_p.x + (-2 + i)*s;
			auto ry = player_p.y + (-2 + j)*s;

			rx = std::min(std::max(0, rx), screen_image.cols);
			ry = std::min(std::max(0, ry), screen_image.rows);


			table_rect[i][j] = cv::Rect(rx, ry, std::min(s, screen_image.cols -	rx) , std::min(s, screen_image.rows - ry));
		}
	}


	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cv::rectangle(screen_image, table_rect[i][j], cv::Scalar(0, 0, std::min(255, 50 * seach_table[i][j])),4);
		}
	}

	auto to_v = ToVect();


	if (to_v.x == 0 && to_v.y == 0 && bullet_rect.size() == 0) {
		cv::Point defp(357, 724);
		auto ss = defp - player_p;

		cv::circle(screen_image, defp, std::sqrt(20000), cv::Scalar(0, 255, 255), 5);

		if (ss.x*ss.x + ss.y*ss.y > 20000) {
			to_v += ss;
		}

	}

	cv::line(screen_image, player_p, player_p + to_v, cv::Scalar(0, 255, 255), 10);
	player.Move(Vec2D(to_v.x, to_v.y));
	send_move.Update();
}