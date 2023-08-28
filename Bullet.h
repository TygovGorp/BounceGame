#pragma once
#include <iostream>
#include <math.h>  
#include <SDL.h>
#include "game.h"
#include "surface.h"

using namespace std;
namespace Tmpl8
{
	class Bullet
	{
	private:
		const int BULLET_SPEED = 5;
		const int SCREEN_WIDTH = 700;
		const int SCREEN_HEIGHT = 512;

		float bulletDX = 0;
		float bulletDY = 0;
		bool bulletFired = false;

		float tempMouseX;
		float tempMouseY;
		bool XorYEqualToOne; // x = true y = false

		SDL_Rect BulletRect;
		float BulletRectX;
		float BulletRectY;
	public:
		Sprite bullet;
		
		void init()
		{
			BulletRect.h = 128;
			BulletRect.w = 128;
			BulletRectX = 0;
			BulletRectY = 512 - 60;

		}

		void Schoot(int MouseX, int MouseY)
		{
			//if (bulletFired == false)
			//{
			//	tempMouseX = MouseX;
			//	tempMouseY = MouseY;

			//	bullet.Build(new Surface("assets/magic_missile.png"), 1);

			//	if (MouseX > MouseY)
			//	{
			//		bulletDY = tempMouseY / tempMouseX;
			//		bulletDX = 1;
			//		XorYEqualToOne = true;
			//	}
			//	else
			//	{
			//		bulletDX = tempMouseX / tempMouseY;
			//		bulletDY = 1;
			//		XorYEqualToOne = false;
			//	}

			//	cout << bulletDX << "," << bulletDY << endl;

			//	// Fire the bullet
			//	if (bulletFired != true)
			//	{
			//		bulletFired = true;
			//	}
			//}
			if (!bulletFired)
			{
				tempMouseX = MouseX;
				tempMouseY = MouseY;

				bullet.Build(new Surface("assets/magic_missile.png"), 1);

				bulletDX = MouseX - BulletRectX; // Calculate the direction vector components
				bulletDY = MouseY - BulletRectY;

				// Calculate the magnitude of the movement vector
				double magnitude = sqrt(bulletDX * bulletDX + bulletDY * bulletDY);

				// Check for magnitude close to zero
				if (magnitude < 1e-6) {
					// Set a minimum magnitude to avoid division by zero
					magnitude = 1.0;
				}

				bulletDX /= magnitude; // Normalize the direction vector
				bulletDY /= magnitude;

				XorYEqualToOne = abs(bulletDX) > abs(bulletDY);

				cout << bulletDX << "," << bulletDY << endl;

				// Fire the bullet
				bulletFired = true;
			}
		}
		void Update(Surface* screen)
		{
			if (bulletFired)
			{
				BulletRectX += bulletDX * 2;
				BulletRectY += bulletDY * 2;

				// Check if the bullet is out of bounds
				if (BulletRectX < -128 || BulletRectX >= SCREEN_WIDTH || BulletRectY < -128 || BulletRectY >= SCREEN_HEIGHT)
				{
					BulletRectX = 0;
					BulletRectY = 512 - 60;
					bulletFired = false;
				}
			}
			if (bulletFired) //in seperate if function because of despawning out of bouds of the screen
			{
				// Draw bullet
				bullet.Draw(screen, BulletRectX, BulletRectY);
				//cout << BulletRectX << ", " << BulletRectY << endl;
			}
		}
		SDL_Rect GetBulletRect()
		{
			return BulletRect;
		}

		float GetBulletX()
		{
			return BulletRectX;
		}
		float GetBulletY()
		{
			return BulletRectY;
		}
	};
};