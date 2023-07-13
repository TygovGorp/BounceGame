#pragma once

namespace Tmpl8 {

class LevelManager
{
public:
	void LoadLevel();
	int ReturnWalls()
	{

	}
private:
	const int SCREEN_WIDTH = 700;
	const int SCREEN_HEIGHT = 512;
	bool Level1Tiles[700][512] = {};
	int Level1Collision[700][512] = {};
};

}; // namespace Tmpl8