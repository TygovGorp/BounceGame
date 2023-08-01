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
		void init(Surface* ScreenSurface)
		{
			vector<int> coordinates;
			//https://www.scaler.com/topics/cpp-read-file-line-by-line/
			fstream newfile;
			newfile.open("Levels/Level_1.txt", ios::in); //open a file to perform read operation using file object
			if (newfile.is_open()) { //checking whether the file is open
				string tp;
				int counter = 1;
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
						cout << coordinates[0] << "," << coordinates[1] << " "; //print the data of the coordinates
						cout << coordinates[2] << "," << coordinates[3] << "\n"; //print the data of the coordinates
						ScreenSurface->Line(coordinates[0], coordinates[1], coordinates[2], coordinates[3], 0xffffff);
						pointofline++;
						break;
					case 4:
						pointofline = 0;
						break;
					default:
						break;
					}
				}
				newfile.close(); //close the file object.
			}
		}

	private:
		
		int pointofline = 0;
	};
}