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

		void SetColliderDetectors()
		{
			BulletCollider[0].x = round(BulletLoc.x);
			BulletCollider[0].y = round(BulletLoc.y);
													
			BulletCollider[1].x = round(BulletLoc.x) + BulletRect.w;
			BulletCollider[1].y = round(BulletLoc.y);
													
			BulletCollider[2].x = round(BulletLoc.x);
			BulletCollider[2].y = round(BulletLoc.y) - BulletRect.h;
													
			BulletCollider[3].x = round(BulletLoc.x) + BulletRect.w;
			BulletCollider[3].y = round(BulletLoc.y) - BulletRect.h;
		}

	public:
		Bullet() {
			BulletRect.h = 36;
			BulletRect.w = 86;
			BulletLoc.x = 0;
			BulletLoc.y = 512 - 60;
		}
		Sprite bullet;

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
				if (BulletLoc.y < 0 || BulletLoc.y >= SCREEN_HEIGHT)
				{
					InvertDY();
				}
			}
			if (bulletFired) //in seperate if function because of despawning when out of bouds of the screen
			{
				// Draw bullet
				bullet.Draw(screen, BulletLoc.x, BulletLoc.y);
				SetColliderDetectors();
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
						if (bulletCenter.x < wallPoint.x)
						{
							cout << "Bullet hit the front of the wall." << endl;
							if (bulletDX > 0)
							{
								InvertDX(); // Invert the horizontal direction.
							}
						}
						else if (bulletCenter.x > wallPoint.x)
						{
							cout << "Bullet hit the back of the wall." << endl;
							if (bulletDX < 0)
							{
								InvertDX(); // Invert the horizontal direction.
							}
						}
						else if (bulletCenter.y > wallPoint.y)
						{
							cout << "Bullet hit the top of the wall." << endl;
							if (bulletDY > 0)
							{
								InvertDY(); // Invert the vertical direction.
							}
						}
						else if (bulletCenter.y < wallPoint.y)
						{
							cout << "Bullet hit the bottom of the wall." << endl;
							if (bulletDY < 0)
							{
								InvertDY(); // Invert the vertical direction.
							}
						}

						// You can add any other necessary actions here.

						// Do not set bulletFired to false.

						return; // Exit the function after detecting the collision.
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
	};
};