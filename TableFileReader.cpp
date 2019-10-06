#pragma once
#include "TableFileReader.h"
#include <iostream>
#include<TCHAR.H>
#include <math.h> 
#include <random>
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 255);
wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
	TableFileReader::TableFileReader(LPCWSTR filePath, int _n, int _m) {
		HANDLE buffer;
		_file = CreateFile(filePath,
			READ_CONTROL,
			FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		n = _n;
		m = _m;

	}
	int TableFileReader::textOut(HWND hwnd, HDC hdc) {

		RECT winRect;
		GetClientRect(hwnd, &winRect);
		int width = (winRect.right - winRect.left) / n;
		int height = (winRect.bottom - winRect.top) / m;

		TCHAR buffer_read[50];
		DWORD bytes_read = 0;
		bool flag = ReadFile(_file, &buffer_read, 50, &bytes_read, NULL);
		int scale = ceil(width/240);
		HFONT   hFont = CreateFont(20 + scale*2, 10 + scale, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Helvetica"));

		SelectObject(hdc, hFont);

		RECT textRect;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				SetTextColor(hdc, RGB((byte)distribution(generator), (byte)distribution(generator), (byte)distribution(generator)));
				textRect.left = i* width + 3;
				textRect.right = i*width + width;
				textRect.bottom = j*height + height;
				textRect.top = j*height;
				DrawText(hdc, L"F2as dfa sdf asd fas df asd fas dfasdfasdfasdfasdf asdfasdfasdfaAGATHAF", 70, &textRect, DT_WORDBREAK);
			}
		}

		DeleteObject(hFont);
		return 1;
	}
	void TableFileReader::drawTable(HWND hwnd, HDC hdc) {
		RECT winRect;
		GetClientRect(hwnd, &winRect);
		int width = (winRect.right - winRect.left) / n;
		int height = (winRect.bottom- winRect.top) / m;
		for (int i = 1; i < n; i++)
		{
			MoveToEx(hdc, width*i, 0, NULL);
			LineTo(hdc, width*i, winRect.bottom);
		}
		for (int i = 1; i < m; i++)
		{
			MoveToEx(hdc, 0, height * i, NULL);
			LineTo(hdc, winRect.right, height * i);
		}
		
	}

	 