#include "GameObject.h"
#include "Texture.h"
using namespace std;

GameObject::GameObject(string name,
	SpriteSheet* spriteSheet,
	TransformationMatrix* transformMatrix,
	int red,
	int green,
	int blue,
	D3DXVECTOR2* position,
	float force,
	float mass)
{
	this->name = name;
	this->spriteSheet = spriteSheet;
	this->transformMatrix = transformMatrix;
	this->spriteRect = new RECT();
	this->boxCollider = RECT();
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->position = position;
	this->velocity = D3DXVECTOR2(0.0f, 0.0f);
	this->acceleration = D3DXVECTOR2(0.0f, 0.0f);
	this->force = force;
	this->mass = mass;

	spriteWidth = spriteSheet->getTextureWidth() / spriteSheet->getSpriteCol();
	spriteHeight = spriteSheet->getTextureHeight() / spriteSheet->getSpriteRow();

	scaledSpriteWidth = spriteWidth * this->transformMatrix->getScaling().x;
	scaledSpriteHeight = spriteHeight * this->transformMatrix->getScaling().y;

	spriteRect->top = 0;
	spriteRect->left = 0;
	spriteRect->right = spriteWidth;
	spriteRect->bottom = spriteHeight;

	spriteCentre = D3DXVECTOR2(scaledSpriteWidth / 2.0f, scaledSpriteHeight / 2.0f);
}

GameObject::GameObject(string name,
	SpriteSheet* spriteSheet,
	int spriteWidth,
	int spriteHeight,
	TransformationMatrix* transformMatrix,
	int red,
	int green,
	int blue,
	D3DXVECTOR2* position,
	float force,
	float mass)
{
	this->name = name;
	this->spriteSheet = spriteSheet;
	this->transformMatrix = transformMatrix;
	this->spriteRect = new RECT();
	this->boxCollider = RECT();
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->position = position;
	this->velocity = D3DXVECTOR2(0.0f, 0.0f);
	this->acceleration = D3DXVECTOR2(0.0f, 0.0f);
	this->force = force;
	this->mass = mass;

	this->spriteWidth = spriteWidth;
	this->spriteHeight = spriteHeight;

	scaledSpriteWidth = spriteWidth * this->transformMatrix->getScaling().x;
	scaledSpriteHeight = spriteHeight * this->transformMatrix->getScaling().y;

	spriteRect->top = 0;
	spriteRect->left = 0;
	spriteRect->right = spriteWidth;
	spriteRect->bottom = spriteHeight;

	spriteCentre = D3DXVECTOR2(scaledSpriteWidth / 2.0f, scaledSpriteHeight / 2.0f);
}

string GameObject::getName() { return name; }
SpriteSheet* GameObject::getSpriteSheet() { return spriteSheet; }
TransformationMatrix* GameObject::getTransformMatrix() { return transformMatrix; }
RECT* GameObject::getSpriteRect() { return spriteRect; }

RECT GameObject::getBoxCollider() { return boxCollider; }

int GameObject::getRed() { return red; }
int GameObject::getGreen() { return green; }
int GameObject::getBlue() { return blue; }
D3DXVECTOR2* GameObject::getPosition() { return position; }
D3DXVECTOR2 GameObject::getVelocity() { return velocity; }
float GameObject::getMass() { return mass; }
float GameObject::getForce() { return force; }
int GameObject::getSpriteWidth() { return spriteWidth; }
int GameObject::getSpriteHeight() { return spriteHeight; }
float GameObject::getScaledSpriteWidth() { return scaledSpriteWidth; }
float GameObject::getScaledSpriteHeight() { return scaledSpriteHeight; }
D3DXVECTOR2 GameObject::getSpriteCentre() { return spriteCentre; }

void GameObject::updateBoxCollider()
{
	boxCollider.top = position->y;
	boxCollider.left = position->x;
	boxCollider.right = boxCollider.left + 1;
	boxCollider.bottom = boxCollider.top + 1;
}

void GameObject::addToPosition(D3DXVECTOR2 pos)
{
	*position += pos;
}

void GameObject::setVelocity(D3DXVECTOR2 vel)
{
	velocity = vel;
}

void GameObject::addAcceleration(D3DXVECTOR2 accel)
{
	acceleration += accel;
}

void GameObject::resetAcceleration()
{
	acceleration = D3DXVECTOR2(0.0f, 0.0f);
}

void GameObject::setPositionX(float posX)
{
	position->x = posX;
}

void GameObject::setPositionY(float posY)
{
	position->y = posY;
}

void GameObject::multiplyVelocityX(float factorX)
{
	velocity.x *= factorX;
}

void GameObject::multiplyVelocityY(float factorY)
{
	velocity.y *= factorY;
}

void GameObject::updatePosition(float friction)
{
	velocity += acceleration;

	velocity.x *= (1 - friction);

	*position += velocity;
}

void GameObject::cleanup()
{
	spriteSheet = NULL;

	delete transformMatrix;
	transformMatrix = NULL;

	delete position;
	position = NULL;
}