#include "Stdafx.h"
#include <Windows.h>
#include "PrintWindow.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <string>



BOOL WriteBitmap(LPTSTR lpszFileName, int nWidth, int nHeight, LPVOID lpBits);
HBITMAP CreateBackbuffer(int nWidth, int nHeight);


void WindowPrint::Print(System::IntPtr hw)
{
	
	HDC hdc;
	HWND hwnd = reinterpret_cast< HWND >(hw.ToPointer());
	//HWND hwnd = FindWindow()
	RECT rc;
	BITMAP bm;
	HBITMAP hbmp;
	HBITMAP hbmpPrev;

	GetWindowRect(hwnd,&rc);

	hdc = CreateCompatibleDC(NULL);
	hbmp = CreateBackbuffer(rc.right,rc.bottom);
	hbmpPrev = (HBITMAP)SelectObject(hdc, hbmp);

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, GetWindowDC(hwnd), 0, 0, SRCCOPY);
	
	GetObject(hbmp, sizeof(BITMAP), &bm);

	WriteBitmap(TEXT("capture.bmp"), rc.right, rc.bottom, bm.bmBits);
	
	/*
	if (WriteBitmap(TEXT("capture.bmp"), rc.right, rc.bottom, bm.bmBits))
		MessageBox(NULL, TEXT("ファイルを作成しました。"), TEXT("OK"), MB_OK);
	else
		MessageBox(NULL, TEXT("ファイルの作成に失敗しました。"), NULL, MB_ICONWARNING);
		*/
		


	//IplImage image() ;
		/*
	cv::Mat redImg();
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);
	cv::imshow("red", redImg);
	cv::waitKey(0);
	cv::destroyAllWindows();
	*/
	SelectObject(hdc, hbmpPrev);
	DeleteObject(hbmp);
	DeleteDC(hdc);
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
	bmiHeader.biHeight = nHeight;
	bmiHeader.biPlanes = 1;
	bmiHeader.biBitCount = 24;

	bmi.bmiHeader = bmiHeader;

	return CreateDIBSection(NULL, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS, &lp, NULL, 0);

}
