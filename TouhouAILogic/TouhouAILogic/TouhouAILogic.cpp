// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "TouhouAILogic.h"
#include "KeyManage.h"
#include "ImageRecognition.h"

System::String^ TouhouAILogic::MainProc::Test(System::IntPtr hw)
{
	aaa.Print(hw);
	return "te22277777st";
}

void TouhouAILogic::MainProc::Mach()
{
	ImageRecognition aa;
	aa.TemplateMatch();
}

void TouhouAILogic::MainProc::Up()
{
	KeyManage::Instance().SendUp();
}

void TouhouAILogic::MainProc::Down()
{
	KeyManage::Instance().SendDown();
}

void TouhouAILogic::MainProc::Right()
{
	KeyManage::Instance().SendRight();
}

void TouhouAILogic::MainProc::Left()
{
	KeyManage::Instance().SendLeft();
}

void TouhouAILogic::MainProc::Enter()
{
	KeyManage::Instance().SendEnter();
}
