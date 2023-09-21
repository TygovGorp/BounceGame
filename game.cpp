#include "game.h"
#include "surface.h"


namespace Tmpl8
{
	AnimationManager IdleAnim;
	LevelManager LM;
	vector<Point> EnemyCoordinates;
	vector<Point> WallCoordinates;

	bool AABB(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
	{
		if (
			Ax + Aw >= Bx &&
			Bx + Bw >= Ax &&
			Ay + Ah >= By &&
			By + Bh >= Ay
			)
		{
			return true;
		}
		return false;
	}

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

		for (int i = 0; i < EnemyCoordinates.size(); i++)
		{
			EnemyVec[i].Update();
			EnemyVec[i].GotShot(AABB(BulletObject.GetBulletX(), BulletObject.GetBulletY(), EnemyVec[i].GetEnemyRect()));
		}
		
		BulletObject.CheckWallCollision(WallCoordinates);

	}
};