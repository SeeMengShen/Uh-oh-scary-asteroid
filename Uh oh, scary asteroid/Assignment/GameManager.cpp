#include "GameManager.h"
#include "GameObject.h"
#include "TransformationMatrix.h"
#include "FrameTimer.h"
#include "MainMenu.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <iostream>
#include <vector>
#define BUTTONDOWN(name, key) (name.rgbButtons[key] & 0x80)

void GameManager::init(AudioManager* audioManager)
{
	gameScene = new vector<Game*>();

	//Input
	leftKeyPressed = false;
	rightKeyPressed = false;
	upKeyPressed = false;
	downKeyPressed = false;
	spaceKeyPressed = false;
	prevMouse0Clicked = false;
	mouse0Clicked = false;
	mouse0Holding = false;

	landed = false;

	counter = 0;

	characterAnimation = 0;

	timer = new FrameTimer();
	timer->init(60);

	//Main Menu
	MainMenu* mm = new MainMenu();
	mm->init(this, audioManager);
	gameScene->push_back(mm);
}


void GameManager::cleanupGames()
{
	while (!gameScene->empty())
	{
		gameScene->back()->cleanup();
		delete gameScene->back();
		gameScene->pop_back();
	}
}