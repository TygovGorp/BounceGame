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
};