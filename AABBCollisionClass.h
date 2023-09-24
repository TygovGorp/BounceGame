#pragma once
#include <SDL.h>


namespace Tmpl8
{

	class AABBCollisionClass
	{
	public:
		bool AABB(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
		{
			if (
				Ax + Aw >= Bx &&
				Bx + Bw >= Ax &&
				Ay + Ah >= By &&
				By + Bh >= Ay
				)
			{
				return true;
			}
			return false;
		}

		bool AABB(int x, int y, const SDL_Rect& recB)
		{
			int w = 1;
			int h = 1;
			if (
				x + w >= recB.x &&
				recB.x + recB.w >= x &&
				y + h >= recB.y &&
				recB.y + recB.h >= y
				)
			{
				return true;
			}
			return false;
		}
	};
}
