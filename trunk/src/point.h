#pragma once

//Classe point (avec �ventuellement une couleur associ�e)
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