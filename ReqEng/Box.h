#pragma once
#include <string>
#include <Windows.h>
class Box
{
public:
	int x, y, h, w;
	std::wstring label[2];
	Box() {}
	Box(int _x, int _y, int _h, int _w, std::wstring _left = L"", std::wstring _right = L"") :x{ _x }, y{ _y }, h{ _h }, w{ _w }
	{
		this->label[0] = _left;
		this->label[1] = _right;
	}
	~Box() {}
};

