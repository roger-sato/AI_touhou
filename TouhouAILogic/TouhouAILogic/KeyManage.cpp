#include "stdafx.h"

#include <windows.h>
#include "KeyManage.h"
#

/*
const int INPUT_MOUSE = 0;                  // マウスイベント
const int INPUT_KEYBOARD = 1;               // キーボードイベント
const int INPUT_HARDWARE = 2;               // ハードウェアイベント

const int MOUSEEVENTF_MOVE = 0x1;           // マウスを移動する
const int MOUSEEVENTF_ABSOLUTE = 0x8000;    // 絶対座標指定
const int MOUSEEVENTF_LEFTDOWN = 0x2;       // 左　ボタンを押す
const int MOUSEEVENTF_LEFTUP = 0x4;         // 左　ボタンを離す
const int MOUSEEVENTF_RIGHTDOWN = 0x8;      // 右　ボタンを押す
const int MOUSEEVENTF_RIGHTUP = 0x10;       // 右　ボタンを離す
const int MOUSEEVENTF_MIDDLEDOWN = 0x20;    // 中央ボタンを押す
const int MOUSEEVENTF_MIDDLEUP = 0x40;      // 中央ボタンを離す
const int MOUSEEVENTF_WHEEL = 0x800;        // ホイールを回転する
const int WHEEL_DELTA = 120;                // ホイール回転値

const int KEYEVENTF_KEYDOWN = 0x0;          // キーを押す
const int KEYEVENTF_KEYUP = 0x2;            // キーを離す
const int KEYEVENTF_EXTENDEDKEY = 0x1;      // 拡張コード
const int KEYEVENTF_SCANCODE = 0x0008;
const int VK_SHIFT = 0x10;                  // SHIFTキー
const int VK_RETURN = 0x0D;                 // ENTER
const int VK_UP = 0x26;                     // UP
const int VK_RIGHT = 0x27;                  // RIGHT
const int VK_LEFT = 0x25;                   // LEFT
const int VK_DOWN = 0x28;                   // DOWN
*/


void SendKey(short keycode)
{
	Sleep(20);
	
	int num = 2;
	INPUT inp[2];

	inp[0].type = INPUT_KEYBOARD;
	inp[0].ki.wVk = keycode;
	inp[0].ki.wScan = (short)MapVirtualKey(inp[0].ki.wVk, 0);
	inp[0].ki.dwFlags = KEYEVENTF_SCANCODE;
	inp[0].ki.dwExtraInfo = GetMessageExtraInfo();
	inp[0].ki.time = 0;

	SendInput(1, &inp[0], sizeof(INPUT));

	Sleep(20);


	inp[1].type = INPUT_KEYBOARD;
	inp[1].ki.wVk = keycode;
	inp[1].ki.wScan = (short)MapVirtualKey(inp[1].ki.wVk, 0);
	inp[1].ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
	inp[1].ki.dwExtraInfo = GetMessageExtraInfo();
	inp[1].ki.time = 0;

	SendInput(1, &inp[1], sizeof(INPUT));
}

void TouhouAILogic::KeyManage::SendUp()
{
	SendKey(VK_UP);
}

void TouhouAILogic::KeyManage::SendDown()
{
	SendKey(VK_DOWN);
}

void TouhouAILogic::KeyManage::SendRight()
{
	SendKey(VK_RIGHT);
}

void TouhouAILogic::KeyManage::SendLeft()
{
	SendKey(VK_LEFT);
}

void TouhouAILogic::KeyManage::SendEnter()
{
	SendKey(VK_RETURN);
}
