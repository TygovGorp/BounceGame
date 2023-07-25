#pragma once
#include<iostream>
#include "AnimationManager.h"
#include "surface.h"

namespace Tmpl8
{
	class Enemy
	{
	public:
		void Init(Surface* ScreenSurface)
		{
			IdleAnimationManager.init(4, "assets/Enemy-Frames/Idle_frame_", xloc, yloc, ScreenSurface);
			DeathAnimationManager.init(4, "assets/Enemy-Frames/Death_frame_", xloc, yloc, ScreenSurface);
		}
		void Update(Surface* ScreenSurface)
		{
			std::cout << counter << std::endl;
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
	private:
		AnimationManager IdleAnimationManager;
		AnimationManager DeathAnimationManager;
		int xloc, yloc = 0;
		int counter;
		int deadCounter;
		bool hit = false;
		bool dead = false;
	};
}