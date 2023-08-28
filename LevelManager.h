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
		void init()
		{
			fstream newfile;
			newfile.open("Levels/Level_1.txt", ios::in);
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
						EnemyCoordinates.push_back(Point(stoi(tp), 0));
						EnemyCounter++;
					}
					if (tp.find("EnemyLocation") != std::string::npos)
					{
						NextEnemyLocation = true;
					}
					switch (pointofline)
					{
					case 0:
						WallPoints.push_back(Point(stoi(tp), 0));
						pointofline++;
						break;
					case 1:
						WallPoints.back().y = stoi(tp);
						pointofline++;
						break;
					case 2:
						WallPoints.back().x = stoi(tp);
						pointofline++;
						break;
					case 3:
						WallPoints.back().y = stoi(tp);
						loops++;
						pointofline = 0;
						break;
					}
				}
				newfile.close();
			}
			for (int i = 0; i < WallPoints.size(); i++)
			{
				cout << WallPoints[i].x << ", " << WallPoints[i].y << endl;
			}
		}

		vector<Point> ReturnEnemyCoordinates()
		{
			return EnemyCoordinates;
		}

		void update(Surface* ScreenSurface)
		{
			for (int i = 0; i < loops; i++)
			{
				ScreenSurface->Line(WallPoints[i].x, WallPoints[i].y, WallPoints[i + 1].x, WallPoints[i + 1].y, 0xffffff);
			}
		}

		void WallColissionInit()
		{
			for (const Point& wallPoint : WallPoints)
			{
				for (int j = 0; j <= wallPoint.y; j++)
				{
					WallCoordinates.push_back(Point(wallPoint.x, j));
				}
			}
		}

		vector<Point> ReturnWallCoordinates()
		{
			return WallCoordinates;
		}

	private:
		int EnemyCounter = 0;
		bool NextEnemyLocation = false;
		vector<Point> WallPoints;
		vector<Point> WallCoordinates;
		vector<Point> EnemyCoordinates;
		int loops = 0;
		int pointofline = 0;
	};
}
