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
	struct Rectangle {
		float x, y; // Position of the top-left corner of the rectangle
		float width, height; // Width and height of the rectangle
	};

	class Bullet
	{
	private:
		const int SCREEN_WIDTH = 700;
		const int SCREEN_HEIGHT = 512;

		float bulletDX = 0;
		float bulletDY = 0;
		bool bulletFired = false;

		Point BulletCollider[4]; // 0=TopLeft 1=TopRight 2=BottomLeft 3=BottomRight

		Rectangle BulletRect;

	public:
		Bullet() {
			BulletRect.height = 32;
			BulletRect.width = 86;
			BulletRect.x = 0;
			BulletRect.y = 512 - 60;
		}
		Sprite bullet;

		void ResetLoc()
		{
			BulletRect.x = 0;
			BulletRect.y = 512 - 60;
		}

		void Schoot(int MouseX, int MouseY)
		{
			if (!bulletFired)
			{
				bullet.Build(new Surface("assets/magic_missile.png"), 1);

				bulletDX = MouseX - BulletRect.x; // Calculate the direction vector components
				bulletDY = MouseY - BulletRect.y;

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
				BulletRect.x += bulletDX * 4;
				BulletRect.y += bulletDY * 4;

				// Check if the bullet is out of bounds
				if (BulletRect.x < 0 || BulletRect.x >= SCREEN_WIDTH)
				{
					InvertDX();
				}
				if (BulletRect.y < 0 || BulletRect.y >= SCREEN_HEIGHT - 36)
				{
					InvertDY();
				}
			}
			if (bulletFired) //in seperate if function because of despawning when out of bouds of the screen
			{
				// Draw bullet
				bullet.Draw(screen, BulletRect.x, BulletRect.y);
			}
		}

		// Function to check collision with a one-pixel thick wall and determine collision side
		void CheckWallCollision( std::vector<Point> WallCoordinates) {
			for (const Point& wallPoint : WallCoordinates) {
				if (BulletRect.x < wallPoint.x && BulletRect.x + BulletRect.width > wallPoint.x &&
					BulletRect.y < wallPoint.y && BulletRect.y + BulletRect.height > wallPoint.y) {
					// Collision detected with a wall point
					Point bulletCenter(BulletRect.x + (BulletRect.width / 2), BulletRect.y + (BulletRect.height / 2));
					if (bulletCenter.x < wallPoint.x)
						InvertDX();
					else if (bulletCenter.x > wallPoint.x)
						InvertDX();
					if (bulletCenter.y < wallPoint.y)
						InvertDY();
					else if (bulletCenter.y > wallPoint.y)
						InvertDY();
				}
			}
			return; // No collision detected
		}

		void InvertDY()
		{
			bulletDY = -bulletDY;
		}
		void InvertDX()
		{
			bulletDX = -bulletDX;
		}

		Rectangle GetBulletRect()
		{
			return BulletRect;
		}
		float GetBulletX()
		{
			return BulletRect.x;
		}
		float GetBulletY()
		{
			return BulletRect.y;
		}
		void Respawn()
		{
			bulletFired = false;
			ResetLoc();
		}
	};
};