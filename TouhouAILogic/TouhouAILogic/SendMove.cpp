#include "Stdafx.h"
#include "SendMove.h"
#include "KeyManage.h"

enum MoSt {
	UP = 0, RIGHT, LEFT, DOWN, NOWN
};
/////////////////////////
void TouhouAILogic::SendMove::MovePlayer(Vec2D dif)
{
	if (dif.X() < 0) {
		if (!MoveState[MoSt::UP]) {
			KeyManage::Instance().OnUp();
		}
		if (MoveState[MoSt::DOWN]) {

		}
	}
	else if(dif.X() > 0){
		if (MoveState[MoSt::DOWN]) {
			KeyManage::Instance().OnDown();
		}
	}
}
