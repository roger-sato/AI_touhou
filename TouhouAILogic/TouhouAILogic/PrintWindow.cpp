#include "Stdafx.h"
#include <Windows.h>
#include "PrintWindow.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <string>
#include "Debug.h"

#include <fstream>

BOOL WriteBitmap(LPTSTR lpszFileName, int nWidth, int nHeight, LPVOID lpBits);
HBITMAP CreateBackbuffer(int nWidth, int nHeight);
HBITMAP CreateBackbuffer2(int nWidth, int nHeight);
BITMAPINFOHEADER MakeBITINFO(int nWidth, int nHeight, LPVOID lpBits);

void WindowPrint::Print(System::IntPtr hw)
{
	HDC hdc;
	HWND hwnd = static_cast< HWND >(hw.ToPointer());
	//HWND hwnd = GetDesktopWindow();
	RECT rc;
	BITMAP bm;
	HBITMAP hbmp;
	HBITMAP hbmpPrev;

	GetClientRect(hwnd,&rc);

	debug_out << rc.right << std::endl << rc.bottom << std::endl;

	hdc = CreateCompatibleDC(NULL);
	hbmp = CreateBackbuffer2(rc.right,rc.bottom);
	hbmpPrev = (HBITMAP)SelectObject(hdc, hbmp);

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, GetWindowDC(hwnd), 0, 0, SRCCOPY);
	
	GetObject(hbmp, sizeof(BITMAP), &bm);
	
	
	WriteBitmap(TEXT("capture.bmp"), rc.right, rc.bottom, bm.bmBits);

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

cv::Mat WindowPrint::HBITMAPToMat(System::IntPtr hw)
{

	HDC hdc;
	HWND hwnd = static_cast< HWND >(hw.ToPointer());
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

	SelectObject(hdc, hbmpPrev);
	DeleteObject(hbmp);
	DeleteDC(hdc);

	return image;
}