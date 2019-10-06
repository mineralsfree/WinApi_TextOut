#pragma once
#include <Windows.h>
#include <gdiplus.h>

using namespace Gdiplus;
class Sprite {
private:
	int x, y,length, height;
	int dirx;
	int step,diry;
	const WCHAR* image;
public:
	Sprite(int _x, int _y, int _length, int _height, WCHAR* _image);
	void draw(HWND hwnd);
	void move(HWND& hwnd, int dx, int dy);
	void autoMove(HWND& hwnd);
};