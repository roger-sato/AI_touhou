#include "Stdafx.h"
#include "Vec2D.h"
#include <math.h>

TouhouAILogic::Vec2D::Vec2D(int _x, int _y)
{
	x = _x;
	y = _y;
}

int TouhouAILogic::Vec2D::X()const
{
	return x;
}

int TouhouAILogic::Vec2D::Y()const
{
	return y;
}

int TouhouAILogic::Vec2D::ToLength(Vec2D p)
{
	return (int)sqrt((p.X() - x)*(p.X() - x) + (p.Y() - y)*(p.Y() - y));
}

void TouhouAILogic::Vec2D::Set(Vec2D p)
{
	x = p.X();
	y = p.Y();
}

void TouhouAILogic::Vec2D::Set(int _x, int _y)
{
	x = _x;
	y = _y;
}

void TouhouAILogic::Vec2D::Set(cv::Rect p)
{
	x = p.x;
	y = p.y;
}

void TouhouAILogic::Vec2D::Add(int _x, int _y)
{
	x += x;
	y += y;
}

void TouhouAILogic::Vec2D::Add(Vec2D p)
{
	x += p.X();
	y += p.Y();
}
