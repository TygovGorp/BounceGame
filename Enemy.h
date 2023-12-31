#pragma once
#include<iostream>
#include "AnimationManager.h"
#include "surface.h"
#include "Point.h"

namespace Tmpl8
{
	class Enemy
	{
	public:
		void Init(Surface* ScreenSurface, Point EnemyLoc)
		{
			EnemyRect.h = 104;
			EnemyRect.w = 104;
			EnemyRect.x = EnemyLoc.x;
			EnemyRect.y = EnemyLoc.y;
			IdleAnimationManager.init(4, "assets/Enemy-Frames/Idle_frame_", EnemyRect.x, EnemyRect.y, ScreenSurface);
			DeathAnimationManager.init(4, "assets/Enemy-Frames/Death_frame_", EnemyRect.x, EnemyRect.y, ScreenSurface);
		}
		void Update()
		{
			if (hit == false && dead == false)
			{
				IdleAnimationManager.update(counter);
			}
			else if (dead == false && hit == true)
			{
				DeathAnimationManager.update(counter);
				deadCounter++;
				if (deadCounter == 4 * 12)
				{
					dead = true;
				}
			}
			counter++;
		}
		SDL_Rect GetEnemyRect()
		{
			return EnemyRect;
		}
		void GotShot(bool Shot)
		{
			if (Shot)
			{
				hit = true;
			}
		}
		bool ReturnLifeState()
		{
			return hit;
		}
		bool ReturnHitState()
		{
			return dead;
		}
		
		void Reset()
		{
			counter = 0;
			deadCounter = 0;
			hit = false;
			// 1 = dead, 0 = alive
			dead = 0;
		}
	private:
		SDL_Rect EnemyRect;
		AnimationManager IdleAnimationManager;
		AnimationManager DeathAnimationManager;
		int counter;
		int deadCounter;
		bool hit = false;
		bool dead = false;
	};
}