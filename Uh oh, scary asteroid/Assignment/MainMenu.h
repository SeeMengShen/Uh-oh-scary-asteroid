#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#pragma once
#include "Game.h"
#include "Panel.h"
#include <iostream>
using namespace std;

class MainMenu: public Game
{
public:
	void init(GameManager* gameManager, AudioManager* audioManager);
	void update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager);
};

#endif