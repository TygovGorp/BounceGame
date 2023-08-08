#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "surface.h"
#include "game.h"
using namespace std;

namespace Tmpl8
{
	class LevelManager
	{
	public:
		 void init()
		{
			//https://www.scaler.com/topics/cpp-read-file-line-by-line/
			fstream newfile;
			newfile.open("Levels/Level_1.txt", ios::in); //open a file to perform read operation using file object
			if (newfile.is_open()) { //checking whether the file is open
				string tp;
				while (getline(newfile, tp, ' ')) { //read data from file object and put it into string.
					if (EnemyCounter == 2)
					{
						EnemyCounter = 0;
						NextEnemyLocation = false;
					}
					if (NextEnemyLocation)
					{
						EnemyCoordinates.push_back(stoi(tp));
						EnemyCounter++;
					}
					if (tp.find("EnemyLocation") != std::string::npos)
					{
						NextEnemyLocation = true;
					}
					switch (pointofline)
					{
					case 0:
						WallPoints.push_back(stoi(tp));
						pointofline++;
						break;
					case 1:
						WallPoints.push_back(stoi(tp));
						pointofline++;
						break;
					case 2:
						WallPoints.push_back(stoi(tp));
						pointofline++;
						break;
					case 3:
						WallPoints.push_back(stoi(tp));
						loops++;
						pointofline = 0;
						break;
					}
				}
				newfile.close(); //close the file object.
			}
		}

		 vector<int> ReturnEnemyCoordinates()
		 {
			 return EnemyCoordinates;
		 }


		void update(Surface* ScreenSurface)
		{
			for (int i = 0; i < loops; i++)
			{
				ScreenSurface->Line(WallPoints[0 + 4 * i], WallPoints[1 + 4 * i], WallPoints[2 + 4 * i], WallPoints[3 + 4 * i], 0xffffff);
			}
		}

		void WallColissionInit()
		{
			for (int i = 0; i < WallPoints.size(); i++)
			{
				for (int j = 0; j <= WallPoints[i]; j++)
				{
					WallCoordinates.push_back(j);
				}
			}
		}

		vector<int> ReturnWallCoordinates()
		{
			return WallCoordinates;
		}

	private:
		int EnemyCounter = 0;
		bool NextEnemyLocation = false;
		vector<int> WallPoints;
		vector<int> WallCoordinates;
		vector<int> EnemyCoordinates;
		int loops = 0;
		int pointofline = 0;

	};
}