// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "TouhouAILogic.h"
#include "KeyManage.h"
#include "ImageRecognition.h"
#include "SystemData.h"
#include "ImageData.h"
#include "ControlManager.h"

static TouhouAILogic::ControlManager cm;
TouhouAILogic::ImageRecognition screen_shot;

System::String^ TouhouAILogic::MainProc::Test()
{
	TouhouAILogic::ControlManager cm;
	cm.Proc();
	
	return "te22277777st";
}

void TouhouAILogic::MainProc::Init(System::IntPtr hw)
{
	SystemData::Instance().SetWindowHandle(hw);
	ImageData::Instance().Init();
	/*
	cv::Mat img = cv::imread("capture.bmp");
	cv::imshow("matching", img);
	*/
}


void TouhouAILogic::MainProc::ScreenShot()
{
	screen_shot.ScreenShot();
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
