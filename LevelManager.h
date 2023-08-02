#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "surface.h"
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
					switch (pointofline)
					{
					case 0:
						coordinates.push_back(stoi(tp));
						pointofline++;
						break;
					case 1:
						coordinates.push_back(stoi(tp));
						pointofline++;
						break;
					case 2:
						coordinates.push_back(stoi(tp));
						pointofline++;
						break;
					case 3:
						coordinates.push_back(stoi(tp));
						cout << coordinates[0 + 4 * loops] << "," << coordinates[1 + 4 * loops] << " "; //print the data of the coordinates
						cout << coordinates[2 + 4 * loops] << "," << coordinates[3 + 4 * loops] << "\n"; //print the data of the coordinates
						loops++;
						pointofline = 0;
						break;
					}
				}
				newfile.close(); //close the file object.
			}
		}
		void update(Surface* ScreenSurface)
		{
			for (int i = 0; i < loops; i++)
			{
				ScreenSurface->Line(coordinates[0 + 4 * i], coordinates[1 + 4 * i], coordinates[2 + 4 * i], coordinates[3 + 4 * i], 0xffffff);
			}
		}
	private:
		vector<int> coordinates;
		int loops = 0;
		int pointofline = 0;
	};
}