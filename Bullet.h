#pragma once
#include <math.h>  
#include <SDL.h>
#include "game.h"
#include "surface.h"

namespace Tmpl8
{
	class Bullet
	{
	private:
		const int BULLET_SPEED = 5;
		const int SCREEN_WIDTH = 700;
		const int SCREEN_HEIGHT = 512;

		int bulletDX = 0;
		int bulletDY = 0;
		bool bulletFired = false;

		SDL_Rect BulletRect;

	public:
		Sprite bullet;
		
		void init()
		{
			BulletRect.h = 128;
			BulletRect.w = 128;
			BulletRect.x = 0;
			BulletRect.y = 512 - 60;
		}

		void Schoot(int MouseX, int MouseY)
		{
			bullet.Build(new Surface("assets/magic_missile.png"), 1);
			int dx = MouseX - (0 / 2);
			int dy = MouseY - (512 - 60 / 2);
			double length = sqrt(dx * dx + dy * dy);
			int normalizedDX = static_cast<int>(BULLET_SPEED * dx / length);
			int normalizedDY = static_cast<int>(BULLET_SPEED * dy / length);

			// Fire the bullet
			if (bulletFired != true)
			{
				bulletFired = true;
				bulletDX = normalizedDX;
				bulletDY = normalizedDY;
			}

		}
		void Update(Surface* screen)
		{
			if (bulletFired)
			{
				BulletRect.x += bulletDX;
				BulletRect.y += bulletDY;

				// Check if the bullet is out of bounds
				if (BulletRect.x < -128 || BulletRect.x >= SCREEN_WIDTH || BulletRect.y < -128 || BulletRect.y >= SCREEN_HEIGHT)
				{
					//std::cout << "out" << std::endl;
					BulletRect.x = 0;
					BulletRect.y = 512 - 60;
					bulletFired = false;
				}
			}
			if (bulletFired)
			{
				// Draw bullet
				bullet.Draw(screen, BulletRect.x, BulletRect.y);
			}
		}
		SDL_Rect GetBulletRect()
		{
			return BulletRect;
		}
	};
};