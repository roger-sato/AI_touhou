// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "TouhouAILogic.h"
#include "Stdafx.h"
#include "KeyManage.h"
#include "ImageRecognition.h"
#include "SystemData.h"
#include "ImageData.h"

TouhouAILogic::ImageRecognition screen_shot;

System::String^ TouhouAILogic::MainProc::Test()
{
	cm.Proc();
	
	return "te22277777st";
}

void TouhouAILogic::MainProc::Init(System::IntPtr hw)
{
	SystemData::Instance().SetWindowHandle(hw);
	ImageData::Instance().Init();
	cm.Init();

	cv::Mat img = cv::imread("./template/start.bmp");
	cv::imshow("matching", img);
}


void TouhouAILogic::MainProc::ScreenShot()
{
	screen_shot.ScreenShot();
}

void TouhouAILogic::MainProc::DebugSave()
{
	cm.DebugSave();
}

void TouhouAILogic::MainProc::Up()
{
	KeyManage::Instance().SendUp();
}

