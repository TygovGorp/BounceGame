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

		void CalculatePointsOnLine(const Point& startPoint, const Point& endPoint) {
			if (startPoint.x == endPoint.x) {
				// Vertical line
				float minY = std::min(startPoint.y, endPoint.y);
				float maxY = std::max(startPoint.y, endPoint.y);
				for (float y = minY; y <= maxY; y++) {
					WallCoordinates.push_back(Point(startPoint.x, y));
				}
			}
			else if (startPoint.y == endPoint.y) {
				// Horizontal line
				float minX = std::min(startPoint.x, endPoint.x);
				float maxX = std::max(startPoint.x, endPoint.x);
				for (float x = minX; x <= maxX; x++) {
					WallCoordinates.push_back(Point(x, startPoint.y));
				}
			}
			else {
				// Calculate the slope (m) of the line
				float m = (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x);

				// Calculate the y-intercept (b) of the line
				float b = startPoint.y - m * startPoint.x;

				// Determine the range of x-values
				float minX = std::min(startPoint.x, endPoint.x);
				float maxX = std::max(startPoint.x, endPoint.x);

				// Iterate through x-values and calculate corresponding y-values
				for (float x = minX; x <= maxX; x++) {
					float y = m * x + b;
					WallCoordinates.push_back({ x, y });
				}
			}
		}


		void WallCollisionInit() {
			WallCoordinates.clear(); // Clear existing coordinates
			for (size_t i = 0; i < WallPoints.size(); i += 2) {
				CalculatePointsOnLine(WallPoints[i], WallPoints[i + 1]);
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