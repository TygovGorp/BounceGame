#pragma once
namespace Tmpl8 {
	struct Point
	{
		Point() { x = NULL; y = NULL; }
		int x;
		int y;
		Point(int x, int y) : x(x), y(y) {}
	};
}