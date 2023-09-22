#include "game.h"
#include "surface.h"


namespace Tmpl8
{
	AnimationManager IdleAnim;
	LevelManager LM;
	vector<Point> EnemyCoordinates;
	vector<Point> WallPoints;
	


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

		LM.init();
		LM.WallCollisionInit();

		EnemyCoordinates = LM.ReturnEnemyCoordinates();
		WallPoints = LM.ReturnWallPoints();


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

		AABBCollisionClass AABBColClass;
		for (int i = 0; i < EnemyCoordinates.size(); i++)
		{
			EnemyVec[i].Update();
			EnemyVec[i].GotShot(AABBColClass.AABB(BulletObject.GetBulletX(), BulletObject.GetBulletY(), EnemyVec[i].GetEnemyRect()));
		}
		
		BulletObject.CheckWallCollision(WallPoints);

	}
};