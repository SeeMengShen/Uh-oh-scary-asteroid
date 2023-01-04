#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#pragma once
#include "Texture.h"
#include "SpriteSheet.h"
#include <d3dx9.h>
#include "TransformationMatrix.h"
using namespace std;

class GameObject
{

protected:
	string name;
	SpriteSheet* spriteSheet;
	TransformationMatrix* transformMatrix;
	RECT* spriteRect;
	RECT boxCollider;
	int red;
	int green;
	int blue;
	D3DXVECTOR2* position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	float force;
	float mass;
	int spriteWidth;
	int spriteHeight;
	float scaledSpriteWidth;
	float scaledSpriteHeight;
	D3DXVECTOR2 spriteCentre;

public:

	GameObject(string name,
		SpriteSheet* spriteSheet,
		TransformationMatrix* transformMatrix,
		int red,
		int green,
		int blue,
		D3DXVECTOR2* position,
		float force,
		float mass);

	GameObject(string name,
		SpriteSheet* spriteSheet,
		int spriteWidth,
		int spriteHeight,
		TransformationMatrix* transformMatrix,
		int red,
		int green,
		int blue,
		D3DXVECTOR2* position,
		float force,
		float mass);

	string getName();
	SpriteSheet* getSpriteSheet();
	TransformationMatrix* getTransformMatrix();
	RECT* getSpriteRect();
	RECT getBoxCollider();
	int getRed();
	int getGreen();
	int getBlue();
	D3DXVECTOR2* getPosition();
	D3DXVECTOR2 getVelocity();
	float getMass();
	float getForce();
	int getSpriteWidth();
	int getSpriteHeight();
	float getScaledSpriteWidth();
	float getScaledSpriteHeight();
	D3DXVECTOR2 getSpriteCentre();

	void updateBoxCollider();

	void addToPosition(D3DXVECTOR2 pos);
	void setVelocity(D3DXVECTOR2 vel);
	void addAcceleration(D3DXVECTOR2 accel);
	void resetAcceleration();

	void setPositionX(float posX);
	void setPositionY(float posY);
	void multiplyVelocityX(float factorX);
	void multiplyVelocityY(float factorY);
	void updatePosition(float frcition);
	
	void cleanup();
};
#endif