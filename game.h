#pragma once
#include <SDL.h>
#include "Bullet.h"
#include "AnimationManager.h"
#include "Enemy.h"

//using namespace std;

namespace Tmpl8 {

class Surface;
class Game
{
public:

	const int SCREEN_WIDTH = 700;
	const int SCREEN_HEIGHT = 512;
	Bullet Bullet1;
	Enemy Enemy1;


	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(float x, float y)
	{
		MouseX = x;
		MouseY = y;
	}
	void MouseDown( int button ) 
	{
		Bullet1.Schoot(MouseX, MouseY);
	}

	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key) 
	{
		/*	debug code for figuring out what the number was for each key
		std::string str = std::to_string(key);
		const char* test = str.c_str();
		printf(test);
		*/
		// (main)menu navigation inputs
		switch (key)
		{
		case 43: //tab
			break;
		case 82: //arrow up
			break;
		case 80: //arrow left
			break;
		case 81: //arrow down
			break;
		case 79: //arrow right
			break;
		default:
			break;
		}
	}

	static SDL_Renderer* renderer;
	int MouseX;
	int MouseY;
private:
	Surface* screen;
};
}; // namespace Tmpl8