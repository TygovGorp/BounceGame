#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "surface.h"
#include "game.h"
#include "Point.h"
using namespace std;

namespace Tmpl8
{
	class LevelManager
	{
	public:
		void init(int LevelNum)
		{
			EnemyCoordinates.clear();
			WallPoints.clear();

			/*
			======
			if there is time left over also make a .json version instead of .txt
			======
			*/
			fstream newfile;
			newfile.open("Levels/Level_" + to_string(LevelNum) + ".txt", ios::in);
			if (newfile.is_open()) {
				string tp;
				while (getline(newfile, tp, ' ')) {
					if (EnemyCounter == 2)
					{
						EnemyCounter = 0;
						NextEnemyLocation = false;
					}
					if (NextEnemyLocation)
					{
						switch (EnemyCounter)
						{
						case 0:
							EnemyCoordinates.push_back(Point(stoi(tp), 0));
							break;
						case 1:
							EnemyCoordinates.back().y = stoi(tp);
							break;
						default:
							break;
						}

						EnemyCounter++;
					}
					else
					{
						switch (CubePoint)
						{
						case 0:
							WallPoints.push_back(Point(stoi(tp), 0));
							CubePoint++;
							break;
						case 1:
							WallPoints.back().y = stoi(tp);
							loops++;
							CubePoint = 0;
							break;
						}
					}
					if (tp.find("EnemyLocation") != std::string::npos)
					{
						NextEnemyLocation = true;
					}
				}
				newfile.close();
			}
		}

		vector<Point> ReturnEnemyCoordinates()
		{
			return EnemyCoordinates;
		}

		void update(Surface* ScreenSurface)
		{
			for (int i = 0; i < loops; i += 2)
			{
				ScreenSurface->Box(WallPoints[i].x, WallPoints[i].y, WallPoints[i + 1].x, WallPoints[i + 1].y, 0xffffff);
			}
		}

		vector<Point> ReturnWallPoints()
		{
			return WallPoints;
		}

	private:
		int EnemyCounter = 0;
		bool NextEnemyLocation = false;
		vector<Point> WallPoints;
		vector<Point> WallCoordinates;
		vector<Point> EnemyCoordinates;
		int loops = 0;
		int CubePoint = 0;
	};
}