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

		Point BulletCollider[4]; // 0=front 1=back 2=top 4=bottom

		SDL_Rect BulletRect;

		Point BulletLoc;

		void SetColliderDetectors()
		{
			BulletCollider[0].x = BulletLoc.x + BulletRect.w;
			BulletCollider[0].y = BulletLoc.y + (BulletRect.h / 2);

			BulletCollider[1].x = BulletLoc.x;
			BulletCollider[1].y = BulletLoc.y + (BulletRect.h / 2);

			BulletCollider[2].x = BulletLoc.x + (BulletRect.w / 2);
			BulletCollider[2].y = BulletLoc.y;

			BulletCollider[3].x = BulletLoc.x + (BulletRect.w / 2);
			BulletCollider[3].y = BulletLoc.y + BulletRect.h;
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
				if (BulletLoc.x < -128 || BulletLoc.x >= SCREEN_WIDTH || BulletLoc.y < -128 || BulletLoc.y >= SCREEN_HEIGHT)
				{
					BulletLoc.x = 0;
					BulletLoc.y = 512 - 60;
					bulletFired = false;
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
				for (int i = 0; i < WallCoordinates.size(); i++)
				{
					
					for (int j = 0; j < 3; j++)
					{
						if (WallCoordinates[i].x == BulletCollider[j].x && WallCoordinates[i].y == BulletCollider[j].y)
						{
							cout << "hit" << endl;
							switch (j)
							{
							case 1:
								InvertDX();
								break;
							case 2:
								InvertDX();
								break;
							case 3:
								InvertDY();
								break;
							case 4:
								InvertDY();
								break;
							default:
								break;
							}
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
	};
};