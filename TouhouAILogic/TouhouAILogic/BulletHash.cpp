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


	for (int i = 0; i < 39; ++i) {
		x_table2[i] = std::to_string(i);
	}

	for (int i = 0; i < 46; ++i) {
		y_table2[i] = std::to_string(i);
	}
}

std::string TouhouAILogic::BulletHash::GetHash(cv::Rect r)
{
	return x_table[r.x / 10] + y_table[r.y / 10] + std::to_string(r.width) + std::to_string(r.height);
}

std::string TouhouAILogic::BulletHash::GetHash2(cv::Rect r)
{
	return x_table2[r.x / 20] + y_table2[r.y / 20] + std::to_string(r.width) + std::to_string(r.height);
}

std::string TouhouAILogic::BulletHash::GetIdentify()
{
	identify++;
	return std::to_string(identify);
}
