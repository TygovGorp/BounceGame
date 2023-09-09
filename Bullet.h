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
		const int SCREEN_WIDTH = 700;
		const int SCREEN_HEIGHT = 512;

		float bulletDX = 0;
		float bulletDY = 0;
		bool bulletFired = false;

		Point BulletCollider[4]; // 0=TopLeft 1=TopRight 2=BottomLeft 3=BottomRight

		SDL_Rect BulletRect;

		Point BulletLoc;

	public:
		Bullet() {
			BulletRect.h = 20;
			BulletRect.w = 86;
			BulletLoc.x = 0;
			BulletLoc.y = 512 - 60;
		}
		Sprite bullet;

		void ResetLoc()
		{
			BulletLoc.x = 0;
			BulletLoc.y = 512 - 60;
		}

		void Schoot(int MouseX, int MouseY)
		{
			if (!bulletFired)
			{
				bullet.Build(new Surface("assets/magic_missile.png"), 1);

				bulletDX = MouseX - BulletLoc.x; // Calculate the direction vector components
				bulletDY = MouseY - BulletLoc.y;

				// Calculate the magnitude of the movement vector
				double magnitude = sqrt(bulletDX * bulletDX + bulletDY * bulletDY);

				// Check for magnitude close to zero
				if (magnitude < 1e-6) {
					// Set a minimum magnitude to avoid division by zero
					magnitude = 1.0;
				}

				bulletDX /= magnitude; // Normalize the direction vector
				bulletDY /= magnitude;

				// Fire the bullet
				bulletFired = true;
			}
		}
		void Update(Surface* screen)
		{
			if (bulletFired)
			{
				BulletLoc.x += bulletDX * 4;
				BulletLoc.y += bulletDY * 4;

				// Check if the bullet is out of bounds
				if (BulletLoc.x < 0 || BulletLoc.x >= SCREEN_WIDTH)
				{
					InvertDX();
				}
				if (BulletLoc.y < 0 || BulletLoc.y >= SCREEN_HEIGHT - 36)
				{
					InvertDY();
				}
			}
			if (bulletFired) //in seperate if function because of despawning when out of bouds of the screen
			{
				// Draw bullet
				bullet.Draw(screen, BulletLoc.x, BulletLoc.y);
			}
		}

		void WallCollision(vector<Point> WallCoordinates)
		{
			if (bulletFired)
			{
				// Calculate the half-width and half-height of the bullet.
				float bulletHalfWidth = BulletRect.w / 2;
				float bulletHalfHeight = BulletRect.h / 2;

				// Calculate the center and boundaries of the bullet's collision box.
				Point bulletCenter(BulletLoc.x + bulletHalfWidth, BulletLoc.y - bulletHalfHeight);

				Point bulletLeft(bulletCenter.x - bulletHalfWidth, bulletCenter.y);
				Point bulletRight(bulletCenter.x + bulletHalfWidth, bulletCenter.y);
				Point bulletTop(bulletCenter.x, bulletCenter.y + bulletHalfHeight);
				Point bulletBottom(bulletCenter.x, bulletCenter.y - bulletHalfHeight);

				for (const Point& wallPoint : WallCoordinates)
				{
					// Check if the bullet's collision box intersects with the wall point.
					if (bulletRight.x >= wallPoint.x && bulletLeft.x <= wallPoint.x &&
						bulletTop.y >= wallPoint.y && bulletBottom.y <= wallPoint.y)
					{
						// Determine the collision direction based on the relative positions.
						if (bulletCenter.x != wallPoint.x)
						{
							cout << "hit front or back" << endl;
							InvertDX();
						}
						if (bulletCenter.y != wallPoint.y)
						{
							cout << "top or bottom" << endl;
							InvertDY();
						}
					}
				}
			}
		}

		void InvertDY()
		{
			bulletDY = -bulletDY;
		}
		void InvertDX()
		{
			bulletDX = -bulletDX;
		}

		SDL_Rect GetBulletRect()
		{
			return BulletRect;
		}
		float GetBulletX()
		{
			return BulletLoc.x;
		}
		float GetBulletY()
		{
			return BulletLoc.y;
		}
		void Respawn()
		{
			bulletFired = false;
			ResetLoc();
		}
	};
};