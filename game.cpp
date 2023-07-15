#include "game.h"
#include "surface.h"
#include <cstdio> //printf


namespace Tmpl8
{
	
	const int IdleAnimNumFrames = 8;
	Sprite idleFrames[IdleAnimNumFrames];
	int frameLength = 12;
	int XlocPlayer = 0;
	int YlocPlayer = 512 - 60;

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
		for (int i = 0; i < IdleAnimNumFrames; i++)
		{
			idleFrames[i].Build(new Surface(StrToCharStar("assets/Wizard-Frames/Idle_frame_", i)), 1);
		}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		screen->Clear(0);
	}

	

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		Bullet1.Update(screen);
		IdleAnimation();
	}

	// Animation
	int Framecounter = 0;
	void Game::IdleAnimation()
	{
		int currentFrame = Framecounter / frameLength % IdleAnimNumFrames;
		idleFrames[currentFrame].DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);

		Framecounter++;
	}
};