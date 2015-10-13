#include "Stdafx.h"
#include <Windows.h>
#include "PrintWindow.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include "SystemData.h"

BOOL WriteBitmap(LPTSTR lpszFileName, int nWidth, int nHeight, LPVOID lpBits);
HBITMAP CreateBackbuffer(int nWidth, int nHeight);
HBITMAP CreateBackbuffer2(int nWidth, int nHeight);
BITMAPINFOHEADER MakeBITINFO(int nWidth, int nHeight, LPVOID lpBits);

using namespace TouhouAILogic;

void WindowPrint::Print()
{
	HDC hdc;
	HWND hwnd = static_cast< HWND >(SystemData::Instance().GetWindowHandle().ToPointer());
	//HWND hwnd = GetDesktopWindow();
	RECT rc;
	BITMAP bm;
	HBITMAP hbmp;
	HBITMAP hbmpPrev;

	GetClientRect(hwnd,&rc);

	hdc = CreateCompatibleDC(NULL);
	hbmp = CreateBackbuffer2(rc.right,rc.bottom);
	hbmpPrev = (HBITMAP)SelectObject(hdc, hbmp);

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, GetWindowDC(hwnd), 0, 0, SRCCOPY);
	
	GetObject(hbmp, sizeof(BITMAP), &bm);
	
	std::stringstream ss;

	ss << num;
	num++;

	std::string filename = "capture" + ss.str() + ".bmp";

	WriteBitmap((LPTSTR)filename.c_str(), rc.right, rc.bottom, bm.bmBits);

	SelectObject(hdc, hbmpPrev);
	DeleteObject(hbmp);
	DeleteDC(hdc);
}

BITMAPINFOHEADER MakeBITINFO(int nWidth, int nHeight, LPVOID lpBits)
{
	DWORD            dwSizeImage;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;

	dwSizeImage = nHeight * ((3 * nWidth + 3) / 4) * 4;

	ZeroMemory(&bmfHeader, sizeof(BITMAPFILEHEADER));
	bmfHeader.bfType = *(LPWORD)"BM";
	bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSizeImage;
	bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = nWidth;
	bmiHeader.biHeight = -nHeight;
	bmiHeader.biPlanes = 1;
	//bmiHeader.biBitCount = 24;
	bmiHeader.biBitCount = 32;
	bmiHeader.biSizeImage -= dwSizeImage;
	bmiHeader.biCompression = BI_RGB;
	bmiHeader.biClrUsed = 0;
	bmiHeader.biClrImportant = 0;
	bmiHeader.biXPelsPerMeter = 0;
	bmiHeader.biYPelsPerMeter = 0;

	return bmiHeader;
}

BOOL WriteBitmap(LPTSTR lpszFileName, int nWidth, int nHeight, LPVOID lpBits)
{
	HANDLE           hFile;
	DWORD            dwResult;
	DWORD            dwSizeImage;
	BITMAPFILEHEADER bmfHeader;
	BITMAPINFOHEADER bmiHeader;

	hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	dwSizeImage = nHeight * ((3 * nWidth + 3) / 4) * 4;

	ZeroMemory(&bmfHeader, sizeof(BITMAPFILEHEADER));
	bmfHeader.bfType = *(LPWORD)"BM";
	bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwSizeImage;
	bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	WriteFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER), &dwResult, NULL);

	ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = nWidth;
	bmiHeader.biHeight = nHeight;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24;
	bmiHeader.biSizeImage = dwSizeImage;

	bmiHeader.biCompression = BI_RGB;

	WriteFile(hFile, &bmiHeader, sizeof(BITMAPINFOHEADER), &dwResult, NULL);

	WriteFile(hFile, lpBits, dwSizeImage, &dwResult, NULL);

	CloseHandle(hFile);

	return TRUE;
}

HBITMAP CreateBackbuffer(int nWidth, int nHeight)
{
	LPVOID           lp;
	BITMAPINFO       bmi;
	BITMAPINFOHEADER bmiHeader;

	ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = nWidth;
	bmiHeader.biHeight = -nHeight;
	bmiHeader.biPlanes = 1;
	//bmiHeader.biBitCount = 24;
	bmiHeader.biBitCount = 32;

	bmi.bmiHeader = bmiHeader;

	return CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &lp, NULL, 0);

}

//ファイル出力用
HBITMAP CreateBackbuffer2(int nWidth, int nHeight)
{
	LPVOID           lp;
	BITMAPINFO       bmi;
	BITMAPINFOHEADER bmiHeader;

	ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
	bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiHeader.biWidth = nWidth;
	bmiHeader.biHeight = nHeight;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24;

	bmi.bmiHeader = bmiHeader;

	return CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &lp, NULL, 0);

}

cv::Mat WindowPrint::HBITMAPToMat()
{

	HDC hdc;
	HWND hwnd = static_cast< HWND >(SystemData::Instance().GetWindowHandle().ToPointer());
	//HWND hwnd = GetDesktopWindow();
	RECT rc;
	BITMAP bm;
	HBITMAP hbmp;
	HBITMAP hbmpPrev;

	GetClientRect(hwnd, &rc);

	hdc = CreateCompatibleDC(NULL);
	hbmp = CreateBackbuffer(rc.right, rc.bottom);
	hbmpPrev = (HBITMAP)SelectObject(hdc, hbmp);

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, GetWindowDC(hwnd), 0, 0, SRCCOPY);

	GetObject(hbmp, sizeof(BITMAP), &bm);

	cv::Mat image;
	image.create(rc.bottom, rc.right, CV_8UC4);

	BITMAPINFOHEADER bi = MakeBITINFO(rc.right, rc.bottom, bm.bmBits);

	GetDIBits(hdc, hbmp, 0, bm.bmHeight, image.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	cv::Rect roi_rect(65,55,772,900);
	cv::Mat image_roi = image(roi_rect);

	SelectObject(hdc, hbmpPrev);
	DeleteObject(hbmp);
	DeleteDC(hdc);

	return image_roi;
}