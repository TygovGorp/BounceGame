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
			BulletRect.h = 104;
			BulletRect.w = 104;
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
				// Calculate the front, back, top, and bottom positions of the bullet.
				float bulletFront = BulletLoc.x;
				float bulletBack = BulletLoc.x + BulletRect.w;
				float bulletTop = BulletLoc.y;
				float bulletBottom = BulletLoc.y - BulletRect.h;

				for (const Point& wall : WallCoordinates)
				{
					// Check if the bullet collides with the wall.
					if (bulletFront <= wall.x && bulletBack >= wall.x &&
						bulletTop >= wall.y && bulletBottom <= wall.y)
					{
						// Bullet hit the wall; now, determine the collision direction.

						// Calculate the horizontal and vertical overlap with the wall.
						float horizontalOverlap = std::min(bulletBack, wall.x) - std::max(bulletFront, wall.x);
						float verticalOverlap = std::min(bulletTop, wall.y) - std::max(bulletBottom, wall.y);

						// Determine the collision direction based on overlap.
						if (horizontalOverlap > verticalOverlap)
						{
							// Horizontal collision, check if it's front or back.
							if (bulletFront < wall.x)
							{
								cout << "Bullet hit the front of the wall." << endl;
								InvertDX(); // Invert the horizontal direction.
							}
							else
							{
								cout << "Bullet hit the back of the wall." << endl;
								InvertDX(); // Invert the horizontal direction.
							}
						}
						else
						{
							// Vertical collision, check if it's top or bottom.
							if (bulletTop > wall.y)
							{
								cout << "Bullet hit the top of the wall." << endl;
								InvertDY(); // Invert the vertical direction.
							}
							else
							{
								cout << "Bullet hit the bottom of the wall." << endl;
								InvertDY(); // Invert the vertical direction.
							}
						}

						// You can add any other necessary actions here.

						break; // Exit the loop after detecting the first collision.
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