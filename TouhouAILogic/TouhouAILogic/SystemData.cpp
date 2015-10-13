#include "Stdafx.h"
#include "SystemData.h"

void TouhouAILogic::SystemData::SetWindowHandle(System::IntPtr hw)
{
	WindowHandle = hw;
}

System::IntPtr TouhouAILogic::SystemData::GetWindowHandle()
{
	return WindowHandle;
}
