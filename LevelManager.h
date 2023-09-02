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

			/*
			======
			if there is time left over also make a .json version instead of .txt
			======
			*/
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
						switch (pointofline)
						{
						case 0:
							WallPoints.push_back(Point(stoi(tp), 0));
							pointofline++;
							break;
						case 1:
							WallPoints.back().y = stoi(tp);
							loops++;
							pointofline = 0;
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
				ScreenSurface->Line(WallPoints[i].x, WallPoints[i].y, WallPoints[i + 1].x, WallPoints[i + 1].y, 0xffffff);
			}
		}

		void WallColissionInit()
		{
			
			for (int i = 0; i < WallPoints.size(); i += 2)
			{
				//cout << WallPoints[i].x << ", " << WallPoints[i].y << endl;
				//cout << WallPoints[i+1].x << ", " << WallPoints[i+1].y << endl;
				if (WallPoints[i].x == WallPoints[i + 1].x)
				{
					for (int j = 0; j <= WallPoints[i].y; j++)
					{
						WallCoordinates.push_back(Point(WallPoints[i].x, j));
					}
				}
				if (WallPoints[i].y == WallPoints[i + 1].y)
				{
					for (int j = 0; j <= WallPoints[i].x; j++)
					{
						WallCoordinates.push_back(Point(j, WallPoints[i].y));
					}
				}
				else
				{
					Point TempDif;
					
					TempDif.x = WallPoints[i].x - WallPoints[i + 1].x;
					TempDif.y = WallPoints[i].y - WallPoints[i + 1].y;

					Point Add;

					if (WallPoints[i].x < WallPoints[i + 1].x)
					{
						if (WallPoints[i].y < WallPoints[i + 1].y)
						{
							Add.x = 0;
							Add.y = 0;
						}
						else
						{
							Add.x = 0;
							Add.y = 1;
						}
					}
					else
					{
						if (WallPoints[i].y < WallPoints[i + 1].y)
						{
							Add.x = 1;
							Add.y = 0;
						}
						else
						{
							Add.x = 1;
							Add.y = 1;
						}
					}

					if (TempDif.x < 0)
					{
						TempDif.x = -TempDif.x;
					}
					if (TempDif.y < 0)
					{
						TempDif.y = -TempDif.y;
					}

					int j = 0;
					for (float i = 0; i < TempDif.x; i += (TempDif.x / TempDif.y))
					{
						WallCoordinates.push_back(Point(WallPoints[j + Add.x].x + i, WallPoints[j + Add.y].y + i));
						j++;
					}
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