#pragma once
#include <math.h>  
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

		int bulletX = 0;
		int bulletY = 512 - 60;
		int bulletDX = 0;
		int bulletDY = 0;
		bool bulletFired = false;

	public:
		Sprite bullet;
		
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
				//std::cout << "pang" << std::endl;
				bulletX += bulletDX;
				bulletY += bulletDY;

				// Check if the bullet is out of bounds
				if (bulletX < -128 || bulletX >= SCREEN_WIDTH || bulletY < -128 || bulletY >= SCREEN_HEIGHT)
				{
					//std::cout << "out" << std::endl;
					bulletX = 0;
					bulletY = 512 - 60;
					bulletFired = false;
				}
			}
			if (bulletFired)
			{
				// Draw bullet
				//std::cout << "draw" << std::endl;
				//std::cout << bulletX << "," << bulletY << std::endl;
				bullet.Draw(screen, bulletX, bulletY);
			}
		}
	};
};