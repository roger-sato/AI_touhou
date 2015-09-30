#include "Stdafx.h"
#include <Windows.h>
#include "PrintWindow.h"

void WindowPrint::Print()
{
	HDC dc = GetWindowDC(GetActiveWindow());
	DeleteDC(dc);
}
