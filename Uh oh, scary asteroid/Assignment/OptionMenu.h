#ifndef OPTION_MENU
#define OPTION_MENU

#pragma once
#include "Game.h"
#include "Panel.h"
#include "AudioManager.h"
#include <iostream>
using namespace std;

class OptionMenu : public Game
{
public:
	void init(GameManager* gameManager);
	void update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager);

	void updateVolumeString();

private:
	int volumeInt;
	string volumeString;
};

#endif