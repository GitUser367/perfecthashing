#ifndef POINT_H
#define POINT_H

#pragma once

//Classe point (avec éventuellement une couleur associée)
class Point
{
public:
	Point(int u, int v, unsigned char col=0)
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
	unsigned char color;
};

#endif
