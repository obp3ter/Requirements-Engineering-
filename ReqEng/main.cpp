#include <iostream>
#include "Map.h"
#include <conio.h>
#include <locale>
#include "Box.h"
#include <vector>
#include <tuple>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <random>
#include <stdlib.h> 
#include <time.h>
using namespace std;

#include <io.h>    
#include <fcntl.h>
void test()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 800, 800, TRUE);
	int storeh = 30, storew = 50;
	_setmode(_fileno(stdout), _O_U16TEXT);
	Map map(storeh, storew);
	map.init(2);
	Box b1(2, 2, 15, 15, L"fruit", L"vegetables");
	Box b2(2, 22, 15, 15, L"snacks");
	Box b3(0, 0, storeh - 1, storew - 1);
	map.placebox(b1);
	map.placebox(b2);
	map.placebox(b3);
	map.placemarker(10, 19);
	map.placeroute(3, 19, 7);
	map.placeroute(4, 18, 2, 1);
	map.placeitem(4, 17);
	map.calcroute(10, 10, 0, 0);
	map.placedoor(storeh - 1, 2, 5, 1);
	wcout << map;
	Map res(20, 20);
	map.clearroute();
	wcout << map;
	getscreen(5, 5, map, res);
	wcout << res;
}

int tr(wstring s)
{
	if (s == L"Orange")
		return 1;
	if (s == L"Ursus")
		return 2;
	if (s == L"Jidvei")
		return 3;
	if (s == L"bread")
		return 4;
	if (s == L"pizza")
		return 5;
}

int main()
{
	srand(time(NULL));
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 450, 550, TRUE);
	int storeh = 180, storew = 180;
	_setmode(_fileno(stdout), _O_U16TEXT);
	Map map(storeh, storew);
	map.init(3);



	vector<tuple<wstring,int, int, int>> shopping_list, promo_list,s_list;

	promo_list.push_back(tuple<wstring,int, int, int>(L"Orange",90,71,3));
	promo_list.push_back(tuple<wstring,int, int, int>(L"Ursus", 25, 31, 3));
	promo_list.push_back(tuple<wstring,int, int, int>(L"Jidvei",30, 34,1));
	promo_list.push_back(tuple<wstring,int, int, int>(L"bread",82,54,1));
	promo_list.push_back(tuple<wstring,int, int, int>(L"pizza",99,39,2));


	s_list.push_back(tuple<wstring, int, int, int>(L"Lettuce", 90, 91, 3));
	s_list.push_back(tuple<wstring, int, int, int>(L"Milk", 70, 31, 3));
	s_list.push_back(tuple<wstring, int, int, int>(L"Shower gel", 30, 54, 1));
	s_list.push_back(tuple<wstring, int, int, int>(L"Dog food", 25, 71, 3));
	s_list.push_back(tuple<wstring, int, int, int>(L"Ibuprofen", 27, 111, 3));

	


	sample(s_list.begin(), s_list.end(), back_inserter(shopping_list), rand() % s_list.size() + 1, std::mt19937{ std::random_device{}() });



	for(int i=37;i<111;i+=20)
		for(int j=32;j<120;j+=20)
			shopping_list.push_back(tuple<wstring, int, int, int>(L"IP", i, j, 0));

	map.placelist(shopping_list);

	bool ec = true, mod = true;
	int popup = 0;
	int pos1 = 96, pos2 = 75, size1 = 30, size2 = 50;
	wstring added = L"";
	vector<tuple<wstring, int, int, int>> temp_list;
	while (ec)
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			ec = false;
		}
		if (!popup){
			if (GetAsyncKeyState(0x57) || GetAsyncKeyState(VK_UP))//W
			{
				if (map.checkwall(pos1 + (size1) / 2 - 1, pos2 + (size2) / 2))
				{
					if (pos1 == 0)
					{
						continue;
					}
					map.placeroute(pos1 + (size1) / 2, pos2 + (size2) / 2, 1, 0, L' ');
					--pos1;
					mod = true;
					map.placemarker(pos1 + (size1) / 2, pos2 + (size2) / 2);
				}
			}
			if (GetAsyncKeyState(0x41) || GetAsyncKeyState(VK_LEFT))//A
		{
			if (map.checkwall(pos1 + (size1) / 2, pos2 + (size2) / 2 - 1))
			{
				if (pos2 == 0)
				{
					continue;
				}
				map.placeroute(pos1 + (size1) / 2, pos2 + (size2) / 2, 1, 0, L' ');
				--pos2;
				mod = true;
				map.placemarker(pos1 + (size1) / 2, pos2 + (size2) / 2, 0);
			}
		}
			if (GetAsyncKeyState(0x53) || GetAsyncKeyState(VK_DOWN))//S
		{
			if (map.checkwall(pos1 + (size1) / 2 + 1, pos2 + (size2) / 2))
			{
				if (pos1 == storeh - size1)
				{
					continue;
				}
				map.placeroute(pos1 + (size1) / 2, pos2 + (size2) / 2, 1, 0, L' ');
				++pos1;
				mod = true;
				map.placemarker(pos1 + (size1) / 2, pos2 + (size2) / 2, 3);
			}
		}
			if (GetAsyncKeyState(0x44) || GetAsyncKeyState(VK_RIGHT))//D
		{
			if (pos2 == storew - size2)
			{
				continue;
			}
			if (map.checkwall(pos1 + (size1) / 2, pos2 + (size2) / 2 + 1))
			{
				map.placeroute(pos1 + (size1) / 2, pos2 + (size2) / 2, 1, 0, L' ');
				++pos2;
				mod = true;
				map.placemarker(pos1 + (size1) / 2, pos2 + (size2) / 2, 2);
			}
		}
			if (mod) {
				int mp = -1;
				added = L"";
				for (int i = 0; i < shopping_list.size(); ++i)
				{
					if (get<1>(shopping_list[i]) == pos1 + (size1) / 2 && get<2>(shopping_list[i]) == pos2 + (size2)/2 && get<0>(shopping_list[i]) != (wstring)L"IP")
						mp = i;
					if (get<1>(shopping_list[i]) == pos1 + (size1) / 2 && get<2>(shopping_list[i]) == pos2 + (size2) / 2 && get<0>(shopping_list[i]) == (wstring)L"CR")
						ec = false;
				}
				if (mp != -1 && shopping_list.size() != 0) {
					added = get<0>(shopping_list[mp]);
					shopping_list.erase(shopping_list.begin() + mp);
				}
				map.clearroute();
				if (shopping_list.size() != 0) {
					map.draw_route(shopping_list, pos1 + (size1) / 2, pos2 + (size2) / 2);
				}
				if(shopping_list.size() == 20 )
					for (int i = 0; i<31; i += 3)
						shopping_list.push_back(tuple<wstring, int, int, int>(L"CR", 32 + i, 120, 0));
			system("CLS");
			map.printscreen(pos1, pos2, size1, size2);
			for (int i = 0; i < shopping_list.size(); ++i)
			{
				if (abs(get<1>(shopping_list[i]) - (pos1 + (size1) / 2)) + abs(get<2>(shopping_list[i]) - (pos2 + (size2) / 2)) < 10 && get<0>(shopping_list[i]) != (wstring)L"IP"&& get<0>(shopping_list[i]) != (wstring)L"CR")
					wcout << L"You are near " << get<0>(shopping_list[i]) << L" !";
			}
			temp_list.clear();
			for (int i = 0; i < promo_list.size(); ++i)
			{
				if (abs(get<1>(promo_list[i]) - (pos1 + (size1) / 2)) + abs(get<2>(promo_list[i]) - (pos2 + (size2) / 2)) < 10 && get<0>(promo_list[i]) != (wstring)L"IP")
					temp_list.push_back(promo_list[i]);
			}
			int r=rand() % 20;
			if (r == 1 && temp_list.size() != 0) {
				popup = tr(get<0>(temp_list[0]));
				continue;
			}
			mod = false;
		}
	}
		else
		{

			if (GetAsyncKeyState(0x59))
			{
				popup = 0;
				mod = true;
				continue;
			}
			if (GetAsyncKeyState(0x4E))
			{
				popup = 0;
				mod = true;
				continue;
			}
			if (mod) {
			system("CLS");
			map.drawitem(popup, pos1, pos2);
			if (added != L"")
				wcout << L"You added " << added << L" !";
			mod = false;
			}
		}
	}
	return 0;
}