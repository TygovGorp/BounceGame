#include "game.h"
#include "surface.h"
#include <cstdio> //printf


namespace Tmpl8
{
	AnimationManager IdleAnim;
	LevelManager LM;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{	
		/*
		LoadLevel();
		ScoreInit();
		*/
		//setup IdleAnimation frames for animation in a array
		IdleAnim.init(8, "assets/Wizard-Frames/idle_frame_", 0, 512 - 60, screen);
		Enemy1.Init(screen);
		Bullet1.init();
		LM.init();
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		screen->Clear(0);
	}

	
	int Framecounter = 0;
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		LM.update(screen);
		Bullet1.Update(screen);
		IdleAnim.update(Framecounter);
		Enemy1.Update(screen);
		Enemy1.GotShot(AABB(Bullet1.GetBulletRect(), Enemy1.GetEnemyRect()));
		
		Framecounter++;
	}
};