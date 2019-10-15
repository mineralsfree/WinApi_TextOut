#include <windows.h>
#include <tchar.h>
#include <cmath>
#include <cstdlib>
#include "Sprite.h"
#include<gdiplus.h>
#include "TableFileReader.h"
#include <iostream>
#include <locale>
#include <fstream>
#include <thread>
#include <algorithm>
#include <vector>
#include <string>
#define DVD_SPRITE L"logo.png"
#define TIMER_TIME 50
#define STEP 5
#define WINDOW_TITLE L"Osisp lab1"
TableFileReader* text;
Sprite *DVD_Sprite;
LRESULT CALLBACK  WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
TCHAR WinName[] = _T("MainFrame");
RECT rc;

std::string tmp_s;
#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;
class Window {
public:
	HWND hwnd;              // Window's descriptor
	MSG msg;
	WNDCLASS wc;

	bool reg_window(HINSTANCE This, LPCWSTR lpzClassName, WNDPROC lpfnWndProc) {
		wc.hInstance = This;
		wc.lpszClassName = WinName;
		wc.lpfnWndProc = WndProc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.lpszMenuName = NULL;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;            // White color
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			HBRUSH hb = ::CreateSolidBrush(RGB(255, 255,255));
                		wc.hbrBackground = hb;
		if (!RegisterClass(&wc)) return 0;

	}

	void create_window(HINSTANCE This) {
		hwnd = CreateWindow(WinName, //
			WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW,
			0, // x
			0, // y   
			1000, // width
			600, // Height
			HWND_DESKTOP,
			NULL,         // Without menu
			This,         // Application descriptor
			NULL);
			GetWindowRect(hwnd, &rc);
	}

	void show_window() {
		ShowWindow(hwnd, SW_SHOW);
	}

};



int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE,
	LPTSTR,
	int mode)
{

GdiplusStartupInput gdiplusStartupInput; // Связано с загрузкой картинки
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL); // Включаем GDI+
	std::string filename;
	filename = "text.txt";
	std::ifstream reader(filename.c_str());
	getline(reader, tmp_s, '\n');
	std::string::iterator end_pos = std::remove(tmp_s.begin(),tmp_s.end(), ' ');
	tmp_s.erase(end_pos, tmp_s.end());
	getline(reader, tmp_s, '\n');
	text = new TableFileReader(L"C:\\Users\\User\\Desktop\\OSISP2\\ext.txt", 4, 4);

	HWND hWnd;
	MSG msg;
	Window myWin;

	myWin.reg_window(This, L"MyWindowClass", WndProc);
	myWin.create_window(This);
	myWin.show_window();
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		GdiplusShutdown(gdiplusToken); // Завершение работы GDI+

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		RECT rc;
		GetWindowRect(hWnd, &rc);
		HDC hDC = BeginPaint(hWnd, &ps);
		text->textOut(hWnd, hDC, tmp_s);
		text->drawTable(hWnd, hDC);
		EndPaint(hWnd, &ps);
	}
	break;


	case WM_GETMINMAXINFO: {
		auto lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 500;
		lpMMI->ptMinTrackSize.y = 500;
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}