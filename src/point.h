#ifndef POINT_H
#define POINT_H

#pragma once

#include <vector>
using namespace std;

//Classe point (avec éventuellement une couleur associée)
class Point
{
public:
	Point(int u, int v, vector<unsigned char> col = vector<unsigned char>())
	{
		this->x = u;
		this->y = v;
		this->color = col;
	}

	Point (const Point &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->color = other.color;
	}

	Point() {};

	int x;
	int y;
	vector<unsigned char> color;
};

#endif
