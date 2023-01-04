#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#pragma once
#include "FrameTimer.h"
#include "GameObject.h"
#include "AudioManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <vector>
#include <iostream>
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

using namespace std;

class Game;

class GameManager
{
public:
	vector <Game*>* gameScene;

	//Input
	bool leftKeyPressed;
	bool rightKeyPressed;
	bool upKeyPressed;
	bool downKeyPressed;
	bool spaceKeyPressed;
	bool prevMouse0Clicked;
	bool mouse0Clicked;
	bool mouse0Holding;

	bool landed;

	int counter;

	int characterAnimation;

	enum characterAnimation { left, right };

	FrameTimer* timer;

	void init(AudioManager* audioManager);
	void cleanupGames();
};

#endif