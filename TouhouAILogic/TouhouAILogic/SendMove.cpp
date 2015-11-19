#include "Stdafx.h"
#include "SendMove.h"
#include "KeyManage.h"

enum MoSt {
	UP = 0, RIGHT, LEFT, DOWN, NOWN
};

TouhouAILogic::SendMove::SendMove()
{
	MoveState[0] = MoveState[1] = MoveState[2] = MoveState[3] = false;
}

void TouhouAILogic::SendMove::MovePlayer(Vec2D dif)
{	
	if (dif.Y() < 0) {
		if (!MoveState[MoSt::UP]) {
			KeyManage::Instance().OnUp();
			MoveState[MoSt::UP] = true;
		}

		if (MoveState[MoSt::DOWN]) {
			KeyManage::Instance().OffDown();
			MoveState[MoSt::DOWN] = false;
		}
	}

	else if (dif.Y() > 0) {
		if (!MoveState[MoSt::DOWN]) {
			KeyManage::Instance().OnDown();
			MoveState[MoSt::DOWN] = true;
		}
		if (MoveState[MoSt::UP]) {
			KeyManage::Instance().OffUp();
			MoveState[MoSt::UP] = false;
		}
	}
	
	else {
		if (MoveState[MoSt::UP]) {
			KeyManage::Instance().OffUp();
			MoveState[MoSt::UP] = false;
		}

		if (MoveState[MoSt::DOWN]) {
			KeyManage::Instance().OffDown();
			MoveState[MoSt::DOWN] = false;
		}
	}
	
	
	
	if (dif.X() < 0) {
		if (!MoveState[MoSt::LEFT]) {
			KeyManage::Instance().OnLeft();
			MoveState[MoSt::LEFT] = true;
		}
		if (MoveState[MoSt::RIGHT]) {
			KeyManage::Instance().OffRight();
			MoveState[MoSt::RIGHT] = false;
		}
	}

	else if (dif.X() > 0) {
		if (!MoveState[MoSt::RIGHT]) {
			KeyManage::Instance().OnRight();
			MoveState[MoSt::RIGHT] = true;
		}
		if (MoveState[MoSt::LEFT]) {
			KeyManage::Instance().OffLeft();
			MoveState[MoSt::LEFT] = false;
		}
	}
	
	else {
		if (MoveState[MoSt::LEFT]) {
			KeyManage::Instance().OffLeft();
			MoveState[MoSt::LEFT] = false;
		}

		if (MoveState[MoSt::RIGHT]) {
			KeyManage::Instance().OffRight();
			MoveState[MoSt::RIGHT] = false;
		}
	}
	
	
}

static int time = 0;

void TouhouAILogic::SendMove::Update()
{
	if (time == 0) {
		KeyManage::Instance().OffZ();
		KeyManage::Instance().OnZ();
	}

	time = ++time % 10;
}
