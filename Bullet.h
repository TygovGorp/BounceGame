#pragma once
#include <iostream>
#include <math.h>  
#include <SDL.h>
#include "game.h"
#include "surface.h"
#include "Point.h"

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
		float BulletX;
		float BulletY;
	public:
		Sprite bullet;
		
		void init()
		{
			//BulletRect.h = 36;
			//BulletRect.w = 86;
			BulletRect.h = 1;
			BulletRect.w = 1;
			BulletX = 0;
			BulletY = 512 - 60;
		}

		void Schoot(int MouseX, int MouseY)
		{
			if (!bulletFired)
			{
				tempMouseX = MouseX;
				tempMouseY = MouseY;

				bullet.Build(new Surface("assets/magic_missile.png"), 1);

				bulletDX = MouseX - BulletX; // Calculate the direction vector components
				bulletDY = MouseY - BulletY;

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

				// Fire the bullet
				bulletFired = true;
			}
		}
		void Update(Surface* screen)
		{
			if (bulletFired)
			{
				BulletX += bulletDX * 2;
				BulletY += bulletDY * 2;

				// Check if the bullet is out of bounds
				if (BulletX < -128 || BulletX >= SCREEN_WIDTH || BulletY < -128 || BulletY >= SCREEN_HEIGHT)
				{
					BulletX = 0;
					BulletY = 512 - 60;
					bulletFired = false;
				}
			}
			if (bulletFired) //in seperate if function because of despawning out of bouds of the screen
			{
				// Draw bullet
				bullet.Draw(screen, BulletX, BulletY);
				//cout << BulletX << ", " << BulletY << endl;
			}
		}

		bool CheckCollision(const std::vector<Point>& wallCoordinates) {
			for (int i = 0; i < wallCoordinates.size(); i++)
			{
				if (BulletX == wallCoordinates[i].x && BulletY == wallCoordinates[i].y)
				{
					return true;
				}
			}
			return false;

			 

			/*double bulletMagnitude = sqrt(bullet.GetBulletX() * bullet.GetBulletX() + bullet.GetBulletY() * bullet.GetBulletY());


			if (bulletMagnitude < 1e-6) {
				for (int wallCoord : wallCoordinates) {
					if (abs(bullet.GetBulletY() - wallCoord) < 1e-6) {
						return true;
					}
				}
			}

			return false;*/
		}

		void InvertY()
		{
			bulletDY = -bulletDY;
		}
		void InvertX()
		{
			bulletDX = -bulletDX;
		}

		SDL_Rect GetBulletRect()
		{
			return BulletRect;
		}
		float GetBulletX()
		{
			return BulletX;
		}
		float GetBulletY()
		{
			return BulletY;
		}
		int GetBulletW()
		{
			return BulletRect.w;
		}
		int GetBulletH()
		{
			return BulletRect.h;
		}
	};
};