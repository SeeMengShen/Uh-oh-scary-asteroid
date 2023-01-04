#ifndef PAUSE_MENU
#define PAUSE_MENU

#pragma once
#include "Game.h"
#include "Panel.h"
#include <iostream>
using namespace std;

class PauseMenu : public Game
{
public:
	void init(GameManager* gameManager);
	void update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager);
};

#endif
