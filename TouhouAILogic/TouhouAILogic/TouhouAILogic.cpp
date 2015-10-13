// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "TouhouAILogic.h"
#include "KeyManage.h"
#include "ImageRecognition.h"
#include "SystemData.h"
#include "ImageData.h"

static long long time = 0;
static TouhouAILogic::ImageRecognition ir;

System::String^ TouhouAILogic::MainProc::Test()
{
	
	ImageRecognition ir;
	ir.test();
	
	return "te22277777st";
}

void TouhouAILogic::MainProc::Init(System::IntPtr hw)
{
	SystemData::Instance().SetWindowHandle(hw);
	ImageData::Instance().Init();
}


void TouhouAILogic::MainProc::Mach()
{
	ImageRecognition aa;
	aa.test();
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
