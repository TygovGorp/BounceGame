#pragma once
#include "surface.h"
#include <string>
#include <iostream>
#include <math.h>

namespace Tmpl8
{
	class AnimationManager
	{
	private:
		int NumOfFrames;
		int frameLength = 12;
		int Xlocation, Ylocation;
		Surface* Screen;
		Sprite* Frames;
	public:
		~AnimationManager()
		{
			delete[] Frames;
		}

		void init(int NumFrames, char* filename, int Xloc, int Yloc, Surface* ScreenSurface)
		{
			Frames = new Sprite[NumFrames];
			Xlocation = Xloc;
			Ylocation = Yloc;
			Screen = ScreenSurface;
			NumOfFrames = NumFrames;
			for (int i = 0; i < NumOfFrames; i++)
			{
				Frames[i].Build(new Surface(StrToCharStar(filename, i)), 1);
			}
		}

		void update(int FrameCounter)
		{
			int currentFrame = FrameCounter / frameLength % NumOfFrames;
			Frames[currentFrame].DrawScaled(Xlocation, Ylocation, 64, 64, Screen);
		}

		char* StrToCharStar(char* filename, int i)
		{
			std::string FileNameString = (filename + std::to_string(i + 1) + ".png");
			char* charPtr = new char[FileNameString.length() + 1];
			std::strcpy(charPtr, FileNameString.c_str());
			return charPtr;
			delete[] charPtr;
		}
	};
}