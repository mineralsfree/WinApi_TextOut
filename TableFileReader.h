#include <Windows.h>
#pragma once
#include <string>

class TableFileReader {
private: 
	HANDLE _file;
	int n, m;
public:
	TableFileReader(LPCWSTR filePath, int n, int m);
	int textOut(HWND hwnd, HDC hdc, std::string str);
	void drawTable(HWND hwnd, HDC hdc);
};