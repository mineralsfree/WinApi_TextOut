#include "Sprite.h"
#include <gdiplus.h>
#include <math.h>
using namespace Gdiplus;


using namespace Gdiplus;
Sprite::Sprite(int _x, int _y, int _length, int _height, WCHAR* _image) {
	x = _x;
	y = _y;
	length = _length;
	height = _height;
	image = _image;
	dirx = 1;
	diry = 1;
	step = 3;
}
void Sprite::draw(HWND hwnd) {
	PAINTSTRUCT ps;
	RECT rc;
	GetWindowRect(hwnd, &rc);
	HDC hDC = BeginPaint(hwnd, &ps);
	
	Graphics graphics(hDC);
	Bitmap BackBuf(rc.right, rc.bottom, &graphics);
	Graphics temp(&BackBuf);

	int win_width = rc.right - rc.left;
	int win_height = rc.bottom - rc.top;
	x = min(win_width - length, x);
	y = min(win_height - height-30, y);
	Image img  = image;
	temp.DrawImage(&img,x,y,length,height);
	graphics.DrawImage(&BackBuf, 0, 0, 0, 0, rc.right, rc.bottom, UnitPixel);
		EndPaint(hwnd, &ps);

}
void Sprite::move(HWND& hwnd, int dx, int dy){
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int win_width = rect.right - rect.left;
	int win_height = rect.bottom - rect.top;
	x = x + dx; 
	y = y + dy;
	if (y < 0) {
		y = 10;
	}
	if (x < 0) {
		x = 10;
	}
	if (x+length > win_width) {
		x = win_width - length - 20;
	}
	if (y+height +20 > win_height) {
		y = win_height - height -40;
	}
	InvalidateRect(hwnd, NULL, true);
}
void Sprite::autoMove(HWND& hwnd) {
	RECT rect;
	GetWindowRect(hwnd, &rect);
	int win_width = rect.right - rect.left;
	int win_height = rect.bottom - rect.top;
	x = x + (dirx * step);
	y = y + (diry * step);
	if (y + step * 2 + height + 30 > win_height || y - step < 0) {
		diry = diry * (-1);
	}
	if (x + step * 2 + length > win_width || x - step < 0) {
		dirx = dirx * (-1);
	}
	InvalidateRect(hwnd, NULL, true);


}