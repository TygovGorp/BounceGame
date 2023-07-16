#include "game.h"
#include "surface.h"
#include <cstdio> //printf


namespace Tmpl8
{
	AnimationManager IdleAnim;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{	
		//Game::MouseX = 0;
		//Game::MouseY = 0;
		/*
		LoadLevel();
		PlayerInit();
		ScoreInit();
		*/
		//setup IdleAnimation frames for animation in a array
		IdleAnim.init(8, "assets/Wizard-Frames/Idle_frame_", 0, 512 - 60, screen);
		

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

		Bullet1.Update(screen);
		IdleAnim.update(Framecounter);
		Framecounter++;
	}
};