#ifndef GAME_H
#define GAME_H

#pragma once
#include "GameManager.h"
#include "AnimatedObject.h"
#include "GameObject.h"
#include "Panel.h"
#include "Text.h"
#include <vector>
#include <iostream>
#include "AudioManager.h"

using namespace std;

class Game
{
public:
	virtual void init(GameManager* gameManager);
	void getInput(GameManager* gameManager);
	virtual void update(GameManager* gameManager, int framesToUpdate, AudioManager* audioManager);
	void render();
	void cleanup();
	bool collisionDetection(RECT a, RECT b);
	string checkButtonCollision(GameManager* gameManager, AudioManager* audioManager);
	void mouseCheckBoundary();

protected:
	vector<Texture*> textures;
	GameObject* mouseCursor;
	vector<GameObject*> gameObjects;
	vector<AnimatedObject*> animatedObjects;
	vector<D3DXVECTOR2> lineArr;
	vector<vector<D3DXVECTOR2>> lines;
	D3DXVECTOR2 tempLine[2];
	Panel* uiPanel;
	Texture* background;
	D3DXMATRIX mat;
	D3DXVECTOR2 scalingCentre;
	float scalingRotation;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 spriteCentre;
	float rotation;
	D3DXVECTOR2* trans;

	string btnString;
};

#endif
