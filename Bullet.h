#pragma once
#include <iostream>
#include <math.h>  
#include <SDL.h>
#include "game.h"
#include "surface.h"
#include "AABBCollisionClass.h"
#include "Point.h"

using namespace std;
namespace Tmpl8
{
	struct Rectangle 
	{
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

		void CheckWallCollision(std::vector<Point>& WallCoordinates)
		{
			AABBCollisionClass collision;
			for (int i = 0; i < WallCoordinates.size(); i += 2)
			{
				bool TopLeftHit = false;
				bool TopRightHit = false;
				bool BottomLeftHit = false;
				bool BottomRightHit = false;
				bool TwoSpotHit = false;

				Rectangle Wall;
				Wall.x = WallCoordinates[i].x;
				Wall.y = WallCoordinates[i].y;
				Wall.width = WallCoordinates[i + 1].x - WallCoordinates[i].x;
				Wall.height = WallCoordinates[i + 1].y - WallCoordinates[i].y;
				// 1: topleft
				// 2: topright
				// 3: bottomleft
				// 4: bottom right

				if (collision.AABB(BulletRect.x, BulletRect.y, BulletRect.width / 2, BulletRect.height / 2, Wall.x, Wall.y, Wall.width, Wall.height))
				{
					TopLeftHit = true;
					cout << "top left ";
				}
				if (collision.AABB(BulletRect.x + BulletRect.width / 2, BulletRect.y, BulletRect.width / 2, BulletRect.height / 2, Wall.x, Wall.y, Wall.width, Wall.height))
				{
					TopRightHit = true;
					cout << "top right ";
				}
				if (collision.AABB(BulletRect.x, BulletRect.y + BulletRect.height / 2, BulletRect.width / 2, BulletRect.height / 2, Wall.x, Wall.y, Wall.width, Wall.height))
				{
					BottomLeftHit = true;
					cout << "bottom left ";
				}
				if (collision.AABB(BulletRect.x + BulletRect.width / 2, BulletRect.y + BulletRect.height / 2, BulletRect.width / 2, BulletRect.height / 2, Wall.x, Wall.y, Wall.width, Wall.height))
				{
					BottomRightHit = true;
					cout << "bottom right";
				}


				if (TopRightHit && BottomRightHit)
				{
					cout << "front hit" << endl;
					TwoSpotHit = true;
					InvertDX();
				}
				else if (TopLeftHit && BottomLeftHit)
				{
					cout << "back hit" << endl;
					TwoSpotHit = true;
					InvertDX();
				}

				else if (TopLeftHit && TopRightHit)
				{
					cout << "top hit" << endl;
					TwoSpotHit = true;
					InvertDY();
				}
				else if (BottomLeftHit && BottomRightHit)
				{
					cout << "bottom hit" << endl;
					TwoSpotHit = true;
					InvertDY();
				}

				if ((TopLeftHit || TopRightHit || BottomLeftHit || BottomRightHit) && !TwoSpotHit)
				{
					cout << "corner shot" << endl;
					InvertDX();
					InvertDY();
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