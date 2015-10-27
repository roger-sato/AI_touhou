#include "Stdafx.h"
#include "BulletHash.h"

TouhouAILogic::BulletHash::BulletHash()
{
	for (int i = 0; i < 78; ++i) {
		x_table[i] = std::to_string(i);
	}

	for (int i = 0; i < 91; ++i) {
		y_table[i] = std::to_string(i);
	}
}

std::string TouhouAILogic::BulletHash::GetHash(cv::Rect r)
{
	return x_table[r.x / 10] + y_table[r.y / 10] + std::to_string(r.width) + std::to_string(r.height);
}
