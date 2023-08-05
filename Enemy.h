#pragma once
#include<iostream>
#include "AnimationManager.h"
#include "surface.h"

namespace Tmpl8
{
	class Enemy
	{
	public:
		void Init(Surface* ScreenSurface, int x, int y)
		{
			EnemyRect.h = 104;
			EnemyRect.w = 104;
			EnemyRect.x = x;
			EnemyRect.y = y;
			IdleAnimationManager.init(4, "assets/Enemy-Frames/Idle_frame_", EnemyRect.x, EnemyRect.y, ScreenSurface);
			DeathAnimationManager.init(4, "assets/Enemy-Frames/Death_frame_", EnemyRect.x, EnemyRect.y, ScreenSurface);
		}
		void Update()
		{
			if (hit == false && dead == false)
			{
				IdleAnimationManager.update(counter);
			}
			else if(dead == false && hit == true)
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