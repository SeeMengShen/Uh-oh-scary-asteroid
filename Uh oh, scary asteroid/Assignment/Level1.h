#ifndef LEVEL1_H
#define LEVEL1_H

#pragma once
#include "Game.h"
#include "Timer.h"
#include <iostream>
#include <string>
using namespace std;

class Level1 : public Game
{
public:
	void init(GameManager* gameManager, AudioManager* audioManager);
	void update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager);

private:
	Timer* timer;
	int timeLeft;
	string timeString;
	int highScore;
	string highScoreString;
	D3DXVECTOR2 gravity;
	float friction;
	int fps;
};

#endif