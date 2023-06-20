#pragma once
#include <SDL.h>

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick(float deltaTime);
	void Update();
	void Render();
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }


	static SDL_Renderer* renderer;
	static SDL_Event event;
	static const int ScreenSize = 768;
private:
	Surface* screen;
};
class Entity
{
public:
	Entity() {}
	~Entity() {}
	void Init(int height, int width, int scale, int x, int y, const char* path)
	{

	}
	void Update()
	{

	}
	void Render()
	{

	}
private:

};
}; // namespace Tmpl8