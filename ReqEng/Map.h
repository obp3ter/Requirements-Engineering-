#pragma once
#include <iostream>
#include <Windows.h>
#include "Box.h"
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>


class Map
{
private:
	wchar_t **map;
	int h, w;
	std::wstring debug;
public:
	Map();
	Map(int _h, int _w):h{_h},w{_w}
	{
		this->map =new wchar_t*[h];
		for (int i = 0; i < h; ++i)
			this->map[i] = new wchar_t[w];
	}
	~Map()
	{
		for (int i = 0; i < this->h; ++i)
			delete[] this->map[i];
		delete[] this->map;
	}
	void init(int a)
	{
		switch (a) {
		case(1):
		{
			for (int i = 0; i < this->h; ++i)
				for (int j = 0; j < w; ++j)
					this->map[i][j] = 'a' + ((this->h) * i + j) % 26;
			return;
		}
		case(2):
		{
			for (int i = 0; i < this->h; ++i)
				for (int j = 0; j < w; ++j)
					this->map[i][j] = ' ';
			return;
		}
		case(3):
		{
			init(2);
			Box outside(20, 20, 100, 110);
			Box inside(20, 20, 90, 100);
			placebox(outside);
			placebox(inside);
			Box b1(100, 55, 10, 35, L"BIO");
			placebox(b1);
			Box b2(100, 20, 10, 35, L"Pre-Made Meal");
			placebox(b2);
			Box b3(80, 20, 20, 10, L"Coffee");
			placebox(b3);
			Box b4(80, 75, 15, 15, L"Fruit", L"Vegetables");
			placebox(b4);
			Box b5(80, 55, 15, 15, L"Baked goods", L"Fruit");
			placebox(b5);
			Box b6(80, 35, 15, 15, L"Canned food", L"Baked goods");
			placebox(b6);
			Box b7(60, 20, 20, 10, L"Dairy");
			placebox(b7);
			Box b8(60, 35, 15, 15, L"Frozen meat", L"Frozen veg.");
			placebox(b8);
			Box b9(60, 55, 15, 15, L"Frozen Snacks");
			placebox(b9);
			Box b10(60, 75, 15, 15, L"Magazines");
			placebox(b10);
			Box b11(40, 20, 20, 10, L"Office");
			placebox(b11);
			Box b12(40, 35, 15, 15, L"Dry supplies");
			placebox(b12);
			Box b13(40, 55, 15, 15, L"Water", L"Juices");
			placebox(b13);
			Box b14(40, 75, 15, 15, L"Soft drinks");
			placebox(b14);
			Box b15(20, 20, 20, 10, L"Beer");
			placebox(b15);
			Box b16(20, 35, 15, 15, L"Wine/Spirits", L"Cosmetics");
			placebox(b16);
			Box b17(20, 55, 15, 15, L"Cosmetics", L"Pet food");
			placebox(b17);
			Box b18(20, 75, 15, 15, L"Pet food", L"Cleaning");
			placebox(b18);
			Box b19(20, 95, 15, 15, L"Cleaning", L"Medicine");
			placebox(b19);

			placechar(20, 30, L'┳');
			placechar(20, 35, L'┳');
			placechar(20, 50, L'┳');
			placechar(20, 55, L'┳');
			placechar(20, 70, L'┳');
			placechar(20, 75, L'┳');
			placechar(20, 90, L'┳');
			placechar(20, 95, L'┳');
			placechar(20, 110, L'┳');
			placechar(20, 120, L'┳');

			placechar(40, 20, L'┣');
			placechar(40, 30, L'┫');
			placechar(60, 20, L'┣');
			placechar(60, 30, L'┫');
			placechar(80, 20, L'┣');
			placechar(80, 30, L'┫');
			placechar(100, 20, L'┣');
			placechar(100, 30, L'┻');
			placechar(110, 20, L'┣');
			placechar(100, 55, L'┳');
			placechar(110, 55, L'┻');
			placechar(110, 90, L'┻');


			placedoor(120, 21, 20, 1);
			placedoor(110, 95, 20, 1);
		}
		default:
			return;
		}
		
	}
	friend std::wostream& operator<< (std::wostream& stream, const Map& map)
	{
		for (int i = 0; i <map.h; ++i)
		{
			for (int j = 0; j < map.w; ++j)
				stream << map.map[i][j];
			stream << std::endl;
			
		}
		return stream;
	}
	void placebox(int x, int y, int h, int w)
	{
		this->map[x][y] = L'┏';
		this->map[x][y+w] = L'┓';
		this->map[x+h][y] = L'┗';
		this->map[x+h][y+w] = L'┛';
		for (int i = 1; i < w; ++i) {
			this->map[x][y + i] = L'━';
			this->map[x+h][y + i] = L'━';
		}
		for (int i = 1; i < h; ++i) {
			this->map[x + i][y + w] = L'┃';
			this->map[x + i][y] = L'┃';
		}
	}
	void placebox(Box box)
	{
		int l1= box.label[0].length(), l2= box.label[1].length();
		this->placebox(box.x, box.y, box.h, box.w);
		if (l2 == 0 && l1 == 0)
			return;
		if (l2==0)
		{
			for (int i = 0; i < l1; ++i)
			{
				map[box.x + 1][box.y + (box.w - l1) / 2 + i] = box.label[0][i];
				map[box.x + box.h - 1][box.y + (box.w - l1) / 2 + i] = box.label[0][i];
			}
				
			return;
		}
		if (l1 == 0)
		{
			for (int i = 0; i < l2; ++i)
			{
				map[box.x + 1][box.y + (box.w - l2) / 2 + i] = box.label[1][i];
				map[box.x + box.h - 1][box.y + (box.w - l2) / 2 + i] = box.label[1][i];
			}
			return;
		}
		else
		{
			map[box.x + 1][box.y + (box.w - l1) / 2] = L'<';
			map[box.x + box.h - 2][box.y + (box.w - l1) / 2] = L'<';
			for (int i = 0; i < l1; ++i)
			{
				map[box.x + 1][box.y + (box.w - l1) / 2 + i+1] = box.label[0][i];
				map[box.x + box.h - 2][box.y + (box.w - l1) / 2 + i+1] = box.label[0][i];
			}
			for (int i = 0; i < l2; ++i)
			{
				map[box.x + 2][box.y + (box.w - l2) / 2 + i] = box.label[1][i];
				map[box.x + box.h - 1][box.y + (box.w - l2) / 2 + i] = box.label[1][i];
			}
			map[box.x + 2][box.y + (box.w - l2) / 2 + l2] = L'>';
			map[box.x + box.h - 1][box.y + (box.w - l2) / 2 + l2] = L'>';
		}
	}
	void placemarker(int _x, int _y, int orientation = 1)
	{
		wchar_t marker = L'\u2190';
		marker += orientation;
		map[_x][_y] = marker;
	}
	void placeitem(int _x, int _y,int _o=1)
	{
	switch(_o)
		{
	case(3):
			map[_x][_y-2] = L'\x2550';
			map[_x][_y-1] = L'\x2563';
			map[_x][_y ] = L'\u2588';
			return;
	case(1):
			map[_x][_y+2] = L'\x2550';
			map[_x][_y+1] = L'\x2560';
			map[_x][_y] = L'\u2588';
			return;
	case(2):
		map[_x+2][_y] = L'\x2551';
		map[_x+1][_y] = L'\x2566';
		map[_x][_y] = L'\u2588';
		return;
	case(4):
		map[_x-2][_y] = L'\x2551';
		map[_x-1][_y] = L'\x2569';
		map[_x][_y] = L'\u2588';
		return;
	default:
		return;
		}
	}
	void placeroute(int _x, int _y,int l, int o=0,wchar_t c= L'\u2588')
	{
		if(o)
			for (int i = 0; i<l; ++i)
				map[_x][_y + i] = c;
		else
			for (int i = 0; i<l; ++i)
				map[_x+i][_y] = c;
	}
	void calcroute(int _x1, int _y1, int _x2, int _y2)
	{
		if (_x1 > _x2)
			placeroute(_x2, _y1, (_x1 - _x2));
		else
			placeroute(_x1+1, _y1, (_x2 - _x1));
		if (_y1 != _y2)
			if (_y1 > _y2)
				placeroute(_x2, _y2, (_y1 - _y2), 1);
			else
				placeroute(_x2, _y1+1, (_y2 - _y1), 1);
	}
	void placedoor(int _x, int _y, int l, int o = 0)
	{
		switch (o)
		{
		case(0):
			map[_x][_y] = L'\u255B';
			map[_x+l][_y] = L'\u2555';
			for (int i = 1; i < l; ++i)
			{
				map[_x+i][_y] = L' ';
			}
			return;
		case(1):
			map[_x][_y] = L'\u255C';
			map[_x][_y + l] = L'\u2559';
			for (int i = 1; i < l; ++i)
			{
				map[_x][_y + i] = L' ';
			}
			return;
		case(2):
			map[_x][_y] = L'\u2558';
			map[_x + l][_y] = L'\u2552';
			for (int i = 1; i < l; ++i)
			{
				map[_x + i][_y] = L' ';
			}
			return;
		case(3):
			map[_x][_y] = L'\u2556';
			map[_x][_y + l] = L'\u2553';
			for (int i = 1; i < l; ++i)
			{
				map[_x][_y + i] = L' ';
			}
			return;


		default: return;
		}
	}
	friend void getscreen(int x, int y,const Map map, Map& res)
	{
		for (int i = 0; i < res.h; ++i)
			for (int j = 0; j < res.w; ++j)
				res.map[i][j] = map.map[x + i][y + j];

	}
	void printscreen(int x, int y,int h=30, int w=50)
	{
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j)
				std::wcout << this->map[x + i][y + j];
			std::wcout << std::endl;
		}
		//std::wcout << debug;
	}
	bool checkwall(int x, int y) 
	{
		return map[x][y] == L' '  || map[x][y] == L'\u2588';
	}
	void clearroute()
	{
		for (int i = 0; i < this->h; ++i)
			for (int j = 0; j < this->w; ++j)
				if (this->map[i][j] == L'\u2588')
					this->map[i][j] = L' ';
	}
	void placechar(int _x, int _y, wchar_t _c)
	{
		map[_x][_y] = _c;
	}
	void drawitem(int item, int x, int y, int h = 30, int w = 50)
	{
			std::wstring orange[] = {
				L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
				L"┃                                      ┃",
				L"┃   Would you also like to buy orange  ┃",
				L"┃               juice?                 ┃",
				L"┃                                      ┃",
				L"┃                     ┏━┓              ┃",
				L"┃              ┏━━━━━━┻━┻┓             ┃",
				L"┃              ┃         ┃             ┃",
				L"┃              ┣━━━━━━━━━┫             ┃",
				L"┃              ┃  Orange ┃             ┃",
				L"┃              ┣━━━━━━━━━┫             ┃",
				L"┃              ┃         ┃             ┃",
				L"┃              ┗━━━━━━━━━┛             ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃       ┏━━━━━┓           ┏━━━━━┓      ┃",
				L"┃       ┃ Yes ┃           ┃ No  ┃      ┃",
				L"┃       ┗━━━━━┛           ┗━━━━━┛      ┃",
				L"┃                                      ┃",
				L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
			};
			std::wstring beer[] = {
				L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
				L"┃                                      ┃",
				L"┃   Would you also like to buy beer?   ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃              /━━━━━━━━━\u005C             ┃",
				L"┃              ┃         ┃             ┃",
				L"┃              ┣━━━━━━━━━┫             ┃",
				L"┃              ┃  Ursus  ┃             ┃",
				L"┃              ┣━━━━━━━━━┫             ┃",
				L"┃              ┃         ┃             ┃",
				L"┃              ┃         ┃             ┃",
				L"┃              ┗━━━━━━━━━┛             ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃       ┏━━━━━┓           ┏━━━━━┓      ┃",
				L"┃       ┃ Yes ┃           ┃ No  ┃      ┃",
				L"┃       ┗━━━━━┛           ┗━━━━━┛      ┃",
				L"┃                                      ┃",
				L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
			};
			std::wstring wine[] = {
				L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
				L"┃                                      ┃",
				L"┃   Would you also like to buy wine?   ┃",
				L"┃                                      ┃",
				L"┃                 ┏━━━┓                ┃",
				L"┃                 ┣━━━┫                ┃",
				L"┃                 ┣━━━┫                ┃",
				L"┃                /     \u005C               ┃",
				L"┃               /       \u005C              ┃",
				L"┃              /         \u005C             ┃",
				L"┃              ┣━━━━━━━━━┫             ┃",
				L"┃              ┃ Jidvei  ┃             ┃",
				L"┃              ┣━━━━━━━━━┫             ┃",
				L"┃              ┗━━━━━━━━━┛             ┃",
				L"┃                                      ┃",
				L"┃       ┏━━━━━┓           ┏━━━━━┓      ┃",
				L"┃       ┃ Yes ┃           ┃ No  ┃      ┃",
				L"┃       ┗━━━━━┛           ┗━━━━━┛      ┃",
				L"┃                                      ┃",
				L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
			};
			std::wstring bread[] = {
				L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
				L"┃                                      ┃",
				L"┃   Would you also like to buy bread?  ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃        /━━━━━━━━━━━━━━━━━━━━\u005C        ┃",
				L"┃        ┃   /  /  /  /  /    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┗━━━━━━━━━━━━━━━━━━━━┛        ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃                                      ┃",
				L"┃       ┏━━━━━┓           ┏━━━━━┓      ┃",
				L"┃       ┃ Yes ┃           ┃ No  ┃      ┃",
				L"┃       ┗━━━━━┛           ┗━━━━━┛      ┃",
				L"┃                                      ┃",
				L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
			};
			std::wstring pizza[] = {
				L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓",
				L"┃                                      ┃",
				L"┃   Would you also like to buy pizza?  ┃",
				L"┃                                      ┃",
				L"┃        ┏━━━━━━━━━━━━━━━━━━━━┓        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┃    ┏━━━━━━━━━━┓    ┃        ┃",
				L"┃        ┃    ┃   Pizza  ┃    ┃        ┃",
				L"┃        ┃    ┗━━━━━━━━━━┛    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┃                    ┃        ┃",
				L"┃        ┗━━━━━━━━━━━━━━━━━━━━┛        ┃",
				L"┃                                      ┃",
				L"┃       ┏━━━━━┓           ┏━━━━━┓      ┃",
				L"┃       ┃ Yes ┃           ┃ No  ┃      ┃",
				L"┃       ┗━━━━━┛           ┗━━━━━┛      ┃",
				L"┃                                      ┃",
				L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"
			};
		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < w; ++j) {
				if (((i < 5 || i>24) || (j < 5 || j>45)))
					std::wcout << this->map[x + i][y + j];
				else
					if (j == 6) {
						switch (item)
						{
						case(1):
							std::wcout << orange[i - 5];
							continue;
						case(2):
							std::wcout << beer[i - 5];
							continue;
						case(3):
							std::wcout << wine[i - 5];
							continue;
						case(4):
							std::wcout << bread[i - 5];
							continue;
						case(5):
							std::wcout << pizza[i - 5];
							continue;
						}
					}
			}
			std::wcout << std::endl;
		}
		
	}
	void placelist(std::vector<std::tuple<std::wstring, int, int, int>> items)
	{
		items;
		bool empty = true;
		auto ci = items.begin();
		while (empty)
		{
			empty=(std::wstring)L"IP"==std::get<0>(*ci++);
		}
		if (!empty)
			for (auto i : items)
			{
				if (std::get<3>(i))
					this->placeitem(std::get<1>(i), std::get<2>(i), std::get<3>(i));

			}
	}
	void draw_route(std::vector<std::tuple<std::wstring, int, int, int>> items, int _x, int _y)
	{
		bool empty = true;
		auto ci = items.begin();
		while (empty && ci != items.end())
		{
			empty = (std::wstring)L"IP" == std::get<0>(*ci++);
		}
		if (empty)
			return;
		while(!empty){
			std::tuple<std::wstring, int, int, int> cx(L"placeholder", -1, -1, 0), cy(L"placeholder", 2000, 2000, 0), cp(L"pos", _x, _y, 0);
			if (!empty)
			{
				
				for (auto i : items)
				{
					if (std::get<1>(cx) == -1) {
						cx = i;
					}
					if (dist(i, _x, _y) < dist(cx, _x, _y) && std::get<0>(i) != (std::wstring)L"IP")
						cx = i;
				}

				if (check_route(cp, cx))
				{
					calcroute(std::get<1>(cp), std::get<2>(cp), std::get<1>(cx), std::get<2>(cx));
					goto end;
				}

				for (auto i : items)
				{
					if (dist(cy, cx) + dist(cy, _x, _y) > dist(i, cx) + dist(i, _x, _y) && check_route(cp, i) && check_route(i, cx))
						cy = i;
				}
				debug = (std::wstring)L"1:" + std::to_wstring(dist(cy, cx) + dist(cy, _x, _y)) + (std::wstring)L"\n 2:" + std::to_wstring(dist(cx, _x, _y)) + (std::wstring)L"\n 3:" + std::to_wstring(check_route(cp, cx));
				if (dist(cy, cx) + dist(cy, _x, _y) > dist(cx, _x, _y) && check_route(cp, cx)) {
					cy = cx;
				}
				if (cy != std::tuple<std::wstring, int, int, int>(L"placeholder", 2000, 2000, 0)) {
					calcroute(_x, _y, std::get<1>(cy), std::get<2>(cy));
					calcroute(std::get<1>(cy), std::get<2>(cy), std::get<1>(cx), std::get<2>(cx));
				}
			}
			end:
			_x = std::get<1>(cx);
			_y = std::get<2>(cx);
			items.erase(std::remove(items.begin(), items.end(),cx), items.end());
			empty = true;
			ci = items.begin();
			while (empty && ci< items.end())
			{
				empty = (std::wstring)L"IP" == std::get<0>(*ci++);
			}
		}
	}
	int dist(std::tuple<std::wstring, int, int, int> i, int x, int y)
	{
		return abs(std::get<1>(i) - x) + abs(std::get<2>(i) - y);
	}
	int dist(std::tuple<std::wstring, int, int, int> a, std::tuple<std::wstring, int, int, int> b)
	{
		return abs(std::get<1>(a) - std::get<1>(b)) + abs(std::get<2>(a) - std::get<2>(b));
	}
	bool check_route(std::tuple<std::wstring, int, int, int> a, std::tuple<std::wstring, int, int, int>b)
	{
		int _x1 = std::get<1>(a), _x2 = std::get<1>(b), _y1 = std::get<2>(a), _y2 = std::get<2>(b);
		bool halfclear=true;
		if (_x1 > _x2)
			halfclear = check_route_helper(_x2, _y1, (_x1 - _x2));
		else
			halfclear = check_route_helper(_x1, _y1, (_x2 - _x1));
		if (_y1 != _y2)
			if (_y1 > _y2)
				return halfclear && check_route_helper(_x2, _y2, (_y1 - _y2), 1);
			else
				return halfclear && check_route_helper(_x2, _y1, (_y2 - _y1), 1);
	}
	bool check_route_helper(int _x, int _y, int l, int o = 0)
	{
		bool clear = true;
		if (o) {
			if (_y + l > w)
				return false;
			for (int i = 0; i < l && clear; ++i)
				clear = map[_x][_y + i] == L' ' || map[_x][_y + i] == L'\u2190' || map[_x][_y + i] == L'\u2191' || map[_x][_y + i] == L'\u2192' || map[_x][_y + i] == L'\u2193' || map[_x][_y + i] == L'\u2588';
		}
		else
		{
			if (_x + l > h)
				return false;
			for (int i = 0; i < l && clear; ++i)
				clear = map[_x + i][_y] == L' ' || map[_x][_y + i] == L'\u2190' || map[_x][_y + i] == L'\u2191' || map[_x][_y + i] == L'\u2192' || map[_x][_y + i] == L'\u2193' || map[_x][_y + i] == L'\u2588';
		}
		return clear;
	}
	void clearroutes()
	{
		for (int i = 0; i < h; ++i)
			for (int j = 0; j < w; ++j)
				if (map[i][j] == L'\u2588')
					map[i][j] = L' ';
	}
};

