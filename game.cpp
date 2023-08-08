#include "game.h"
#include "surface.h"
#include <cstdio> //printf


namespace Tmpl8
{
	AnimationManager IdleAnim;
	LevelManager LM;
	vector<int> EnemyCoordinates;
	vector<int> WallCoordinates;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{	
		/*
		ScoreInit();
		*/

		//setup IdleAnimation frames for animation in a array
		IdleAnim.init(8, "assets/Wizard-Frames/idle_frame_", 0, 512 - 104, screen);
		Bullet1.init();

		LM.init();
		LM.WallColissionInit();
		EnemyCoordinates = LM.ReturnEnemyCoordinates();
		WallCoordinates = LM.ReturnWallCoordinates();



		NumberOfEnemys = EnemyCoordinates.size() / 2;
		for (int i = 0; i < NumberOfEnemys; i++)
		{
			EnemyVec.push_back(Enemy{});
			EnemyVec[i].Init(screen, EnemyCoordinates[0], EnemyCoordinates[1]);
		}
		
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
		IdleAnim.update(Framecounter);
		Bullet1.Update(screen);

		for (int i = 0; i < NumberOfEnemys; i++)
		{
			EnemyVec[i].Update();
			EnemyVec[i].GotShot(AABB(Bullet1.GetBulletRect(), EnemyVec[i].GetEnemyRect()));
		}
		for (int i = 0; i < WallCoordinates.size(); i = i + 2)
		{
			if (i + 1 < WallCoordinates.size())
			{
				if (AABB(WallCoordinates[i], WallCoordinates[i + 1], Bullet1.GetBulletRect()))
				{
					cout << "bounce" << endl;
				}
			}

			
		}
		
		
		Framecounter++;
	}
};