#include "game.h"
#include "surface.h"
#include <algorithm>


namespace Tmpl8
{
	AnimationManager IdleAnim;
	LevelManager LM;
	vector<Point> EnemyCoordinates;
	vector<Point> WallPoints;
	Sprite GameWinScreen;
	


	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		EnemyVec.clear();
		EnemyCoordinates.clear();
		WallPoints.clear();

		//setup IdleAnimation frames for animation in a array
		IdleAnim.init(8, "assets/Wizard-Frames/idle_frame_", 0, 512 - 104, screen);
		GameWinScreen.Build(new Surface("assets/GAME_WIN.png"), 1);

		LM.init(LevelNumber);

		EnemyCoordinates = LM.ReturnEnemyCoordinates();
		WallPoints = LM.ReturnWallPoints();


		for (int i = 0; i <= EnemyCoordinates.size() - 1; i++)
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

		for (int i = 0; i <= EnemyCoordinates.size() - 1; i++)
		{
			EnemyVec[i].Update();
			EnemyVec[i].GotShot(AABBColClass.AABB(BulletObject.GetBulletX(), BulletObject.GetBulletY(), EnemyVec[i].GetEnemyRect()));
		}


		int DeathCounter = 0;
		for (int i = 0; i < EnemyCoordinates.size(); i++)
		{
			if (EnemyVec[i].ReturnLifeState())
			{
				DeathCounter++;
			}
		}
		if (DeathCounter == EnemyCoordinates.size() && LevelNumber < MAX_Level)
		{
			LevelNumber++;
			LM.init(LevelNumber);
			BulletObject.Respawn();
			Init();
		}
		if (DeathCounter == EnemyCoordinates.size() && LevelNumber == MAX_Level)
		{
			GameWinScreen.Draw(screen, 0, 0);
		}
		
		BulletObject.CheckWallCollision(WallPoints);

	}
};