#include "game.h"
#include "surface.h"


namespace Tmpl8
{
	AnimationManager IdleAnim;
	LevelManager LM;
	vector<Point> EnemyCoordinates;
	vector<Point> WallCoordinates;



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
		BulletObject.init();

		LM.init();
		LM.WallColissionInit();
		EnemyCoordinates = LM.ReturnEnemyCoordinates();
		WallCoordinates = LM.ReturnWallCoordinates();


		for (int i = 0; i < EnemyCoordinates.size(); i++)
		{
			EnemyVec.push_back(Enemy{});
			EnemyVec[i].Init(screen, EnemyCoordinates[i]);
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
		BulletObject.Update(screen);

		for (int i = 0; i < NumberOfEnemys; i++)
		{
			EnemyVec[i].Update();
			EnemyVec[i].GotShot(AABB(BulletObject.GetBulletX(), BulletObject.GetBulletY(), EnemyVec[i].GetEnemyRect()));
		}
		for (int i = 0; i < WallCoordinates.size(); i++)
		{
			for (int j = 0; j < BulletObject.GetBulletH() - 2 ; j++)
			{
				BulletObject.WallCollision(AABB(BulletObject.GetBulletX(), BulletObject.GetBulletY() + j, WallCoordinates[i].x, WallCoordinates[i].y));
			}

			for (int j = 0; j < BulletObject.GetBulletW() - 2; j++)
			{
				BulletObject.WallCollision(AABB(BulletObject.GetBulletX() + j, BulletObject.GetBulletY(), WallCoordinates[i].x, WallCoordinates[i].y));
			}
			
		}
		
	}
};