#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	
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
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		screen->Clear(0);
	}

	Sprite bullet(new Surface("assets/magic_missile.png"), 1);

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		
		if (bulletFired) {
			std::cout << "pang" << std::endl;
			bulletX += bulletDX;
			bulletY += bulletDY;

			// Check if the bullet is out of bounds
			if (bulletX < 0 || bulletX >= SCREEN_WIDTH || bulletY < 0 || bulletY >= SCREEN_HEIGHT) {
				std::cout << "out" << std::endl;
				bulletX = SCREEN_WIDTH / 2;
				bulletY = SCREEN_HEIGHT / 2;
				bulletFired = false;
			}
		}

		// Draw bullet
		if (bulletFired) {
			std::cout << "draw" << std::endl;
			std::cout << bulletX  << "," << bulletY << std::endl;
			bullet.Draw(screen, bulletX, bulletY);
		}

		
		IdleAnimation();
		Update();
		Render();
	}

	void Game::Update() 
	{
		
		/*
		KeyboardUpd()
		MouseLocUpd()
		LevelUpd() //EnemyUpd() in here
		ProjectileUpd()
		ScoreUpd()
		*/
	}

	void Game::Render() 
	{
		/*
		LevelRen() //EnemyRen() in here
		PlayerRen()
		ProjectileRen()
		ScoreRen()
		*/
	}

	
	//animation
	Sprite Idle_frame_1(new Surface("assets/Wizard-Frames/Idle_frame_1.png"), 1);
	Sprite Idle_frame_2(new Surface("assets/Wizard-Frames/Idle_frame_2.png"), 1);
	Sprite Idle_frame_3(new Surface("assets/Wizard-Frames/Idle_frame_3.png"), 1);
	Sprite Idle_frame_4(new Surface("assets/Wizard-Frames/Idle_frame_4.png"), 1);
	Sprite Idle_frame_5(new Surface("assets/Wizard-Frames/Idle_frame_5.png"), 1);
	Sprite Idle_frame_6(new Surface("assets/Wizard-Frames/Idle_frame_6.png"), 1);
	Sprite Idle_frame_7(new Surface("assets/Wizard-Frames/Idle_frame_7.png"), 1);
	Sprite Idle_frame_8(new Surface("assets/Wizard-Frames/Idle_frame_8.png"), 1);
	int counter = 0;
	int frameLength = 12;
	int XlocPlayer = 0;
	int YlocPlayer = 512 - 60;

	void Game::IdleAnimation()
	{
		/*
		if (counter >= 0)
		{
			screen->Clear(0);
			Idle_frame_1.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 1)
		{
			screen->Clear(0);
			Idle_frame_2.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 2)
		{
			screen->Clear(0);
			Idle_frame_3.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 3)
		{
			screen->Clear(0);
			Idle_frame_4.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 4)
		{
			screen->Clear(0);
			Idle_frame_5.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 5)
		{
			screen->Clear(0);
			Idle_frame_6.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 6)
		{
			screen->Clear(0);
			Idle_frame_7.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 7)
		{
			screen->Clear(0);
			Idle_frame_8.DrawScaled(XlocPlayer, YlocPlayer, 104, 104, screen);
		}
		if (counter > frameLength * 8)
		{
			counter = 0;
		}
		counter++;
		*/
	}
};