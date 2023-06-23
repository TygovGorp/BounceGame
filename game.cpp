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

	void Game::Tick(float deltaTime)
	{
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

	void Game::CheckScreenBounds()
	{
		// Add logic to check and handle boundaries
	}
};