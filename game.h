#pragma once
#include <SDL.h>
#include <iostream>
#include <string> 
#include <math.h>  

namespace Tmpl8 {

class Surface;
class Game
{
public:
	struct Vector2D {
		int x;
		int y;
	};
	Vector2D mousePos = { MouseX, MouseY };
	Vector2D bulletPos = { 700 / 2, 512 / 2 };
	const int BULLET_SPEED = 5;
	const int SCREEN_WIDTH = 700;
	const int SCREEN_HEIGHT = 512;

	int bulletX = SCREEN_WIDTH / 2;
	int bulletY = SCREEN_HEIGHT / 2;
	int bulletDX = 0;
	int bulletDY = 0;
	bool bulletFired = false;


	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void Update();
	void Render();
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(float x, float y)
	{
		MouseX = x;
		MouseY = y;
	}
	void MouseDown( int button ) 
	{
		int dx = MouseX - (SCREEN_WIDTH / 2);
		int dy = MouseY - (SCREEN_HEIGHT / 2);
		double length = std::sqrt(dx * dx + dy * dy);
		int normalizedDX = static_cast<int>(BULLET_SPEED * dx / length);
		int normalizedDY = static_cast<int>(BULLET_SPEED * dy / length);

		// Fire the bullet
		if (bulletFired != true)
		{
			bulletFired = true;
			bulletDX = normalizedDX;
			bulletDY = normalizedDY;
		}

	}




	void shootBullet(const Vector2D& mousePos, Vector2D& bulletPos, Vector2D& bulletVelocity) {
		bulletVelocity.x = mousePos.x - bulletPos.x;
		bulletVelocity.y = mousePos.y - bulletPos.y;

		double length = std::sqrt(bulletVelocity.x * bulletVelocity.x + bulletVelocity.y * bulletVelocity.y);
		bulletVelocity.x = static_cast<int>(BULLET_SPEED * bulletVelocity.x / length);
		bulletVelocity.y = static_cast<int>(BULLET_SPEED * bulletVelocity.y / length);
	}

	//void DrawLineToMouse();

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

	void IdleAnimation();

	static SDL_Renderer* renderer;
	int MouseX;
	int MouseY;
private:
	Surface* screen;
};
}; // namespace Tmpl8