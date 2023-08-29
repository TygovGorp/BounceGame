#pragma once
#include <SDL.h>
#include <vector>
#include "Bullet.h"
#include "AnimationManager.h"
#include "Enemy.h"
#include "LevelManager.h"
#include "Point.h"

//using namespace std;

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:

		const int SCREEN_WIDTH = 700;
		const int SCREEN_HEIGHT = 512;
		Bullet BulletObject;
		vector<Enemy> EnemyVec;

		Game()
		{
			BulletObject;
		}

		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(float x, float y)
		{
			MouseX = x;
			MouseY = y;
		}
		void MouseDown(int button)
		{
			BulletObject.Schoot(MouseX, MouseY);
		}

		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key)
		{
			/*	debug code for figuring out what the number was for each key
			std::string str = std::to_string(key);
			const char* test = str.c_str();
			printf(test);
			*/
			// (main)menu navigation inputs
			switch (key)
			{
			case 43: //tab
				break;
			case 82: //arrow up
				break;
			case 80: //arrow left
				break;
			case 81: //arrow down
				break;
			case 79: //arrow right
				break;
			default:
				break;
			}
		}
		bool AABB(const SDL_Rect& recA, const SDL_Rect& recB)
		{
			if (
				recA.x + recA.w >= recB.x &&
				recB.x + recB.w >= recA.x &&
				recA.y + recA.h >= recB.y &&
				recB.y + recB.h >= recA.y
				)
			{
				return true;
			}
			return false;
		}
		bool AABB(int x, int y, const SDL_Rect& recB)
		{
			int w = 1;
			int h = 1;
			if (
				x + w >= recB.x &&
				recB.x + recB.w >= x &&
				y + h >= recB.y &&
				recB.y + recB.h >= y
				)
			{
				return true;
			}
			return false;
		}
		bool AABB(int Ax, int Ay, int Bx, int By)
		{
			int w = 1;
			int h = 1;
			if (
				Ax + w >= Bx &&
				Bx + w >= Ax &&
				Ay + h >= By &&
				By + h >= Ay
				)
			{
				return true;
			}
			return false;
		}
		bool AABB(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
		{
			if (
				Ax + Aw >= Bx &&
				Bx + Bw >= Ax &&
				Ay + Ah >= By &&
				By + Bh >= Ay
				)
			{
				return true;
			}
			return false;
		}

		static SDL_Renderer* renderer;
		int MouseX;
		int MouseY;
	private:
		Surface* screen;
	};
}; // namespace Tmpl8