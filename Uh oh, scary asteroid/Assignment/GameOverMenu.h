#ifndef GAME_OVER_MENU
#define GAME_OVER_MENU

#pragma once
#include "Game.h"
#include "Panel.h"
#include <iostream>
using namespace std;

class GameOverMenu: public Game
{
public:
	GameOverMenu(int highScore);
	void init(GameManager* gameManager);
	void update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager);

private:
	string highScoreString;
	int highScore;
};

#endif