#include "Stdafx.h"
#include "Bullet.h"
#include <algorithm>

TouhouAILogic::Bullet::Bullet(std::pair<cv::Mat,std::string>& image) :img(image)
{
}

cv::Rect TouhouAILogic::Bullet::Rect()
{
	return rect;
}

void TouhouAILogic::Bullet::InputRect(cv::Rect p)
{
	rect = p;
}

void TouhouAILogic::Bullet::Update(bool can_reco)
{
	if (can_reco) {
		life_time = defo_life_time;
	}
	else {
		--life_time;
	}
}

cv::Point TouhouAILogic::Bullet::MidPoint()
{
	return cv::Point(rect.x + rect.width / 2 , rect.y + rect.height / 2);
}

void TouhouAILogic::Bullet::SetPoint(cv::Point p)
{
	rect.x = p.x;
	rect.y = p.y;
}

std::pair<cv::Mat,std::string> TouhouAILogic::Bullet::Image()
{
	return img;
}

void TouhouAILogic::Bullet::SetMoveVec(Vec2D v)
{
	move_vec = v;
}

